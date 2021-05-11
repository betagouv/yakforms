<?php

/**
 * @file
 * Contain custom function related to automatic expiration of forms.
 */

/**
 * Treat forms a bout to expire.
 *
 * Get all webforms that will expired between now and a period in the future,
 * and insert them into yakforms_expired table.
 */
function make_forms_expire() {
  $expiration_period = variable_get('yakforms_notification_period_value', 0);
  // If the user set the expiration period to 0, don't make the nodes expire.
  if ($expiration_period == 0) {
    return;
  }
  $max_expiration_time = new DateTime();
  $max_expiration_time->modify("+ {$expiration_period} weeks");

  watchdog(
    'yakforms',
    'Inserting forms that will expire between now and @time in yakforms_expired',
    array('@time' => $max_expiration_time->format('Y-m-d')),
    WATCHDOG_NOTICE
  );

  $transaction = db_transaction();
  try {
    // Select nodes expiring within the two next weeks.
    // Limit query to batch of 1000 rows in order to avoid errors.
    db_query("
        INSERT INTO yakforms_expired (nid)
        (SELECT n.nid
        FROM node n
        INNER JOIN field_data_field_form1_expiration fex
        ON fex.entity_id = n.nid
        AND fex.field_form1_expiration_value <= to_timestamp(:max_timestamp)
        AND fex.entity_id NOT IN
          (SELECT nid FROM yakforms_expired)
        LIMIT :limit)
        ON CONFLICT DO NOTHING;
        ",
        array(
          ':max_timestamp' => $max_expiration_time->getTimestamp(),
          ':limit' => variable_get('yakforms_cron_limit', 1000),
        )
      );
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('yakforms', "There was an error inserting expired forms into yakforms_expired : %error", array('%error' => $e), WATCHDOG_WARNING);
  }

  /* Get all the webforms that are about to expire and whose owner wasn't yet notified */
  try {
    $results = db_query("
        SELECT fex.nid, u.mail, u.uid, n.title
        FROM yakforms_expired fex
        INNER JOIN node n
        ON fex.nid = n.nid
        INNER JOIN users u
        ON u.uid = n.uid
        WHERE fex.notified = 0
        LIMIT :limit;
        ",
      array(':limit' => variable_get('yakforms_cron_limit', 1000))
    );

    // Notify the users of their forms expiration.
    watchdog('yakforms', "Notifying users of their expired forms.", array(), WATCHDOG_NOTICE);
    foreach ($results as $record) {
      $user_notified = notify_user_of_expiration($record);
      // Update the database with the notification date and set notified to 1.
      if ($user_notified) {
        db_update('yakforms_expired')
          ->fields(array(
            'notified' => 1,
            'date_notified' => time(),
          ))
          ->condition('nid', $record->nid, '=')
          ->execute();
        continue;
      }
      watchdog('yakforms', "Error while trying to notify the user : the user's email could be badly configured.", array(), WATCHDOG_WARNING);
    }
    watchdog('yakforms', "Notified all users of their expired forms.", array(), WATCHDOG_NOTICE);
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('yakforms', "There was an error notifying users : %error", array('%error' => $e), WATCHDOG_WARNING);
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
    watchdog('yakforms', "Invalid email for user %uid", array('%uid' => $record->uid), WATCHDOG_WARNING);
    return FALSE;
  }

  $mail_body = variable_get('yakforms_mail_user_notification_body');
  $mail_subject = variable_get('yakforms_mail_user_notification_subject');

  if (!isset($mail_body) || !isset($mail_subject)) {
    watchdog(
      'yakforms',
      'Error sending notification email : mail body or subject is not set. Go to the Yakforms admin pannel to set them.',
      array(),
      WATCHDOG_ERROR
    );
    return FALSE;
  }

  // Replace placeholders from within the mail body and subject.
  $node = node_load($record->nid);
  $mail_body = token_replace($mail_body, array('node' => $node));
  $mail_subject = token_replace($mail_subject, array('node' => $node));

  $mail_params = array(
    'body' => $mail_body,
    'subject' => $mail_subject,
    'headers' => array(),
  );

  // Get Yakforms-specific mail address.
  $from_mail = variable_get('yakforms_mail_from_address');
  if (!isset($from_mail)) {
    // Fallback to global site mail if not set.
    $from_mail = variable_get('site_mail');
  }

  $message = drupal_mail('yakforms', 'expired_webform', (string) $record->mail, language_default(), $mail_params, $from_mail, TRUE);
  return TRUE;
}

/**
 * Deletes expired webform nodes after a period of inactivity.
 *
 * If an expired node was not treated by the user in the given time,
 * this function will delete them from the database.
 */
function delete_expired_nodes() {
  global $conf;
  module_load_include('inc', 'yakforms', 'includes/yakforms.util');
  $deletion_period = variable_get('yakforms_deletion_period_value', 0);
  $notification_period = variable_get('yakforms_notification_period_value', 0);
  $log_file = $conf['yakforms_external_log_file'];

  // Create Datetime object for logging purposes.
  $current_date = new Datetime();
  $current_date = $current_date->format('D d/m/Y - H:i:s');

  $oldest_timestamp = new Datetime();
  $oldest_timestamp->modify("-{$deletion_period} weeks");
  $oldest_timestamp->modify("-{$notification_period} weeks");

  // If the user set the deletion period to 0, don't delete the forms.
  if ($deletion_period == 0 || $notification_period == 0) {
    return;
  }


  $deleted_nodes = array();
  watchdog('yakforms', 'Fetching expired forms older than @date for deletion.',
    array('@date' => $oldest_timestamp->format('Y-m-d')),
    WATCHDOG_NOTICE
  );

  $transaction = db_transaction();
  try {
    $query = db_query("
            SELECT fex.nid, to_timestamp(fex.date_notified) dn
            FROM yakforms_expired fex
            WHERE fex.notified = 1
            AND fex.date_notified <= :timestamp
            ",
          array(':timestamp' => $oldest_timestamp->getTimestamp())
        );
    $expired_nodes = $query->fetchAll();
    foreach ($expired_nodes as $record) {
      yakforms_export_node_submissions($record->nid);
      node_delete($record->nid);
      // Also delete it from the yakforms_expired table.
      db_delete('yakforms_expired')
        ->condition('nid', $record->nid)
        ->execute();
      yakforms_custom_log("Deleted expired node", "Form #{$record->nid} - user notified on {$record->dn} - was deleted.", $log_file);
      array_push($deleted_nodes, $record->nid);
    }

    if (!empty($deleted_nodes)) {
      watchdog("yakforms", "The following forms were deleted : %nodes", array('%nodes' => explode($deleted_nodes)), WATCHDOG_NOTICE);
      return;
    }
    watchdog("yakforms", "There is no form to delete.", array(), WATCHDOG_NOTICE);
  }
  catch (Exception $e) {
    $transaction->rollback();
    watchdog('yakforms', 'Error deleting expired nodes : %error', array('%error' => $e), WATCHDOG_WARNING);
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
function yakforms_export_node_submissions(int $nid) {
  // Before anything, check if the export option is activated by admin.
  if (!variable_get('yakforms_export_form_submissions_before_delete', 0)) {
    return;
  }
  $node = node_load($nid);
  if (!$node | $node->type != 'form1') {
    watchdog('yakforms', 'Node !nid was not found or could not be exported.', array('!nid' => $nid), WATCHDOG_WARNING);
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
  $options['file_name'] = variable_get('file_private_path') . "/yakforms_submissions_backup/{$file_title}.csv";

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

  watchdog("yakforms", "Submissions for node !nid exported.",
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
    watchdog('yakforms', "Unable to clean IPs for node %id : Error in _clean_submissions_ips. %error",
        array('%id' => $node->nid, '%error' => $e),
        WATCHDOG_ERROR
    );
  }
}
