<?php

/**
 * @file
 * Contain custom function related to automatic expiration of forms.
 */

/**
 * Treat forms a bout to expire.
 *
 * Get all webforms that will expired between now and a period in the future,
 * and insert them into framaforms_expired table.
 */
function make_forms_expire() {
  $expiration_period = variable_get('framaforms_notification_period_value');
  // If the user set the expiration period to 0, don't make the nodes expire.
  if ($expiration_period == 0) {
    return;
  }
  $expiration_period .= ' weeks';

  $transaction = db_transaction();
  try {
    // Select nodes expiring within the two next weeks.
    // Limit query to batch of 1000 rows in order to avoid errors.
    db_query(sprintf("
        INSERT INTO framaforms_expired (nid)
        (SELECT n.nid
        FROM node n
        INNER JOIN field_data_field_form1_expiration fex
        ON fex.entity_id = n.nid
        AND fex.field_form1_expiration_value <= date_trunc('day', NOW() + interval'{$expiration_period}')
        AND fex.entity_id NOT IN
          (SELECT nid FROM framaforms_expired)
        LIMIT 1000)
        ON CONFLICT DO NOTHING;
        ", $expiration_period));
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('framaforms', "There was an error inserting expired forms into framaforms_expired : %error", array('%error' => $e), WATCHDOG_WARNING);
  }

  /* Get all the webforms that are about to expire and whose owner wasn't yet notified */
  try {
    $results = db_query("
        SELECT fex.nid, u.mail, u.uid, n.title
        FROM framaforms_expired fex
        INNER JOIN node n
        ON fex.nid = n.nid
        INNER JOIN users u
        ON u.uid = n.uid
        WHERE fex.notified = 0
        LIMIT 1000;
        ");

    // Notify the users of their forms expiration.
    watchdog('framaforms', "Notifying users of their expired forms.", array(), WATCHDOG_NOTICE);
    foreach ($results as $record) {
      $user_notified = notify_user_of_expiration($record);
      // Update the database with the notification date and set notified to 1.
      if ($user_notified) {
        db_update('framaforms_expired')
          ->fields(array(
            'notified' => 1,
            'date_notified' => time(),
          ))
          ->condition('nid', $record->nid, '=')
          ->execute();
        continue;
      }
      watchdog('framaforms', "Error while trying to notify the user : the user's email could be badly configured.", array(), WATCHDOG_WARNING);
    }
    watchdog('framaforms', "Notified all users of their expired forms.", array(), WATCHDOG_NOTICE);
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('framaforms', "There was an error notifying users : %error", array('%error' => $e), WATCHDOG_WARNING);
  }
}

/**
 * Notifies user of their upcoming form expiration.
 *
 * Sends an email by calling drupal_mail to a user,
 * notifying them of the upcoming webform expiration.
 *
 * @param object $record
 *   The expired node.
 *
 * @return bool
 *   TRUE if drupal_mail was called. This doesn't necessarily mean the mail was
 *   sent : https://api.drupal.org/api/drupal/includes%21mail.inc/function/drupal_mail/7.x
 */
function notify_user_of_expiration(stdClass $record) {
  // Use the global variable of Drupal for the site's URL.
  global $base_url;

  // First check if the user has a correct email.
  if (!filter_var($record->mail, FILTER_VALIDATE_EMAIL)) {
    watchdog('framaforms', "Invalid email for user %uid", array('%uid' => $record->uid), WATCHDOG_WARNING);
    return FALSE;
  }

  $mail_body = variable_get('framaforms_mail_user_notification_body');
  $mail_subject = variable_get('framaforms_mail_user_notification_subject');
  // Replace placeholders from within the mail body and subject.
  $node = node_load($record->nid);
  $mail_body = token_replace($mail_body, array('node' => $node));
  $mail_subject = token_replace($mail_subject, array('node' => $node));

  $mail_params = array(
    'body' => $mail_body,
    'subject' => $mail_subject,
    'headers' => array(),
  );

  $from_mail = variable_get('framaforms_mail_from_address');

  $message = drupal_mail('framaforms', 'expired_webform', (string) $record->mail, language_default(), $mail_params, $from_mail, TRUE);
  return TRUE;
}

/**
 * Treat expired nodes that were modified.
 *
 * Looks up webform nodes in the database that were marked as
 * "expired" but whose expiration date * got changed by the user.
 */
function update_modified_nodes() {
  $expiration_period = variable_get('framaforms_notification_period_value');
  if ($expiration_period == 0) {
    return;
  }
  $expiration_period .= ' weeks';
  $transaction = db_transaction();
  watchdog('framaforms', "Removing forms from the framaforms_expired table after their expiration date was pushed back.", array(), WATCHDOG_NOTICE);
  try {
    // Delete modified from the framaforms_notified table.
    $modified_nodes = db_query(sprintf("
            SELECT n.nid
            FROM node n
            INNER JOIN field_data_field_form1_expiration f_exdate
            ON f_exdate.entity_id = n.nid
            INNER JOIN framaforms_expired fex
            ON n.nid = fex.nid
            WHERE f_exdate.field_form1_expiration_value
              > to_timestamp(fex.date_notified) + interval'{$expiration_period}'
            AND n.nid NOT IN (SELECT nid from framaforms_expired)
        ", $expiration_period));
    $nid_changed = 0;

    foreach ($modified_nodes as $node) {
      $nid_changed = $node->nid;
      db_delete('framaforms_expired')
        ->condition('nid', (int) $nid_changed)
        ->execute();
    }
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('framaforms', "Error updating modified nodes : %error", array('%error' => $e), WATCHDOG_WARNING);
  }
}

/**
 * Deletes expired webform nodes after a period of inactivity.
 *
 * If an expired node was not treated by the user in the given time,
 * this function will delete them from the database.
 */
function delete_expired_nodes() {
  $deletion_period = variable_get('framaforms_deletion_period_value');
  $notification_period = variable_get('framaforms_notification_period_value');
  $external_log_file = variable_get('framaforms_external_log_file', '/var/log/framaforms_logfile.log');

  // Create Datetime object for logging purposes.
  $current_date = new Datetime();
  $current_date = date("D d/m/Y - H:i:s", $current_date->getTimestamp());

  // If the user set the deletion period to 0, don't delete the forms.
  if ($deletion_period == 0) {
    return;
  }

  $deletion_period .= ' weeks';
  $deleted_nodes = array();
  watchdog('framaforms', "Deleting forms after notification.", array(), WATCHDOG_NOTICE);

  $transaction = db_transaction();
  try {
    $query = db_query("
            SELECT fex.nid, to_timestamp(fex.date_notified) dn
            FROM framaforms_expired fex
            WHERE fex.notified = 1
            AND to_timestamp(fex.date_notified) <= NOW() - interval'{$deletion_period}' - interval'{$notification_period}'
            ");
    $expired_nodes = $query->fetchAll();
    foreach ($expired_nodes as $record) {
      framaforms_export_node_submissions($record->nid);
      node_delete($record->nid);
      // Also delete it from the framaforms_expired table.
      db_delete('framaforms_expired')
        ->condition('nid', $record->nid)
        ->execute();
      error_log("{$current_date} : Form #{$record->nid} - user notified on {$record->dn} - was deleted.\n", 3, $external_log_file);
      array_push($deleted_nodes, $record->nid);
    }

    if (!empty($deleted_nodes)) {
      watchdog("framaforms", "The following forms were deleted : %nodes", array('%nodes' => explode($deleted_nodes)), WATCHDOG_NOTICE);
      return;
    }
    watchdog("framaforms", "There is no form to delete.", array(), WATCHDOG_NOTICE);
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('framaforms', 'Error deleting expired nodes : %error', array('%error' => $e), WATCHDOG_WARNING);
  }
}

/**
 * Exports a webform submission as CSV file.
 *
 * Adapted from drush_webform_export() function of Webform module :
 * https://drushcommands.com/drush-7x/webform/webform-export/
 *
 * @param int $nid
 *   The form's identifier.
 */
function framaforms_export_node_submissions(int $nid) {
  // Before anything, check if the export option is activated by admin.
  if (!variable_get('framaforms_export_form_submissions_before_delete', 0)) {
    return;
  }
  $node = node_load($nid);
  if (!$node | $node->type != 'form1') {
    watchdog('framaforms', 'Node !nid was not found or could not be exported.', array('!nid' => $nid), WATCHDOG_WARNING);
    return;
  }
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  module_load_include('inc', 'webform', 'includes/webform.export');
  module_load_include('inc', 'webform', 'includes/webform.components');
  module_load_include('inc', 'webform', 'includes/webform.report');
  module_load_include('inc', 'pathauto');

  $format = 'delimited';
  $options = webform_results_download_default_options($node, $format);

  // Set the export options.
  $options['range']['batch_size'] = 10000;
  $file_title = pathauto_cleanstring($node->title) . "-" . time() . '-' . $node->uid;
  $options['file_name'] = variable_get('file_private_path') . "/framaforms_submissions_backup/{$file_title}.csv";

  // Map form keys to components IDs.
  $form_keys = array();
  foreach ($node->webform['components'] as $cid => $component) {
    $form_keys[$component['form_key']] = $cid;
  }
  foreach ($options['components'] as $key => &$component) {
    if (isset($form_keys[$component])) {
      $component = $form_keys[$component];
    }
  }
  // Drop PHP reference.
  unset($component);

  // Clean up IPs in database before export.
  _clean_submissions_ips($node);

  // Calls to webform module to create a clean CSV file.
  webform_results_batch_bof($node, $format, $options);
  webform_results_batch_headers($node, $format, $options);
  webform_results_batch_rows($node, $format, $options);
  webform_results_batch_eof($node, $format, $options);
  webform_results_batch_post_process($node, $format, $options);

  watchdog("framaforms", "Submissions for node !nid exported.",
    array('!nid' => $nid),
    WATCHDOG_INFO
  );
}

/**
 * Cleans submission IPs from database before export, as this is private data.
 *
 * @param object $node
 *   The node whose submissions should be cleaned out.
 */
function _clean_submissions_ips($node) {
  try {
    db_update('webform_submissions')
      ->fields(array(
        'remote_addr' => '0.0.0.0',
      ))
      ->condition('nid', $node->nid)
      ->execute();
  }
  catch (PDOException $e) {
    watchdog('framaforms', "Unable to clean IPs for node %id : Error in _clean_submissions_ips. %error",
        array('%id' => $node->nid, '%error' => $e),
        WATCHDOG_ERROR
    );
  }
}
