<?php

/**
 * @file
 * Contain Framaforms custom function related to automatic expiration of user
 * webforms.
 */

/**
 * Get all webforms that will expired between now and 2 weeks in the future,
 * and insert them into framaforms_expired table.
 *
 * @return void
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
 * Sends an email by calling drupal_mail to a user,
 * notifying them of the upcoming webform expiration.
 *
 * @param DatabaseStatementInterface $record
 *   : Single database statement containing node and user information.
 * @param string $expiration_period
 *   : notification-expiration time interval.
 * @param string $deletion_period
 *   : expiration-deletion time interval.
 *
 * @return void
 */
function notify_user_of_expiration($record) {
  // Use the global variable of Drupal for the site's URL.
  global $base_url;

  // First check if the user has a correct email.
  if (!filter_var($record->mail, FILTER_VALIDATE_EMAIL)) {
    watchdog('framaforms', "Invalid email for user %uid", array('%uid' => $record->uid), WATCHDOG_WARNING);
    return FALSE;
  }

  $expiration_period = variable_get('framaforms_notification_period_value') . ' weeks';
  $deletion_period = variable_get('framaforms_deletion_period_value') . ' weeks';

  $expiration_date = new DateTime();
  $expiration_date->modify("+" . $expiration_period);
  $delete_date = clone $expiration_date;
  $delete_date->modify($deletion_period);
  $delete_date = date("d/m/Y", $delete_date->getTimestamp());
  $expiration_date = date("d/m/Y", $expiration_date->getTimestamp());

  $node_url = $base_url . url('node/' . $record->nid);
  $mail_body = variable_get('framaforms_mail_user_notification_body');
  $mail_subject = variable_get('framaforms_mail_user_notification_subject');
  // Replace placeholders in the body and subject.
  $placeholders = ['[form_title]', '[form_expires_on]', '[form_delete_on]', '[form_url]'];
  $replacers = [$record->title, $expiration_date, $delete_date, $node_url];
  $mail_subject = str_replace($placeholders, $replacers, $mail_subject);
  $mail_body = str_replace($placeholders, $replacers, $mail_body);

  $mail_params = array(
    'body' => $mail_body,
    'subject' => $mail_subject,
    'headers' => array(),
  );

  $message = drupal_mail('framaforms', 'expired_webform', (string) $record->mail, user_preferred_language($user), $mail_params);
  return TRUE;
}

/**
 * Looks up webform nodes in the database that were marked as
 * "expired" but whose expiration date * got changed by the user.
 *
 * @return void
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
    // Delete nodes from the framaforms_notified table if their expiration date was pushed back by the user.
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
 * Deletes all expired webform nodes after a period of inactivity (defined in $deletion_period).
 * If the webform's expiration date is modified by the user, the update_modified_node()
 * function will delete them from the framaforms_expired table and the rows won't be affected
 * by this function.
 *
 * @param string $deletion_period
 *   : form expiration-deletion time interval.
 *
 * @return void
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
