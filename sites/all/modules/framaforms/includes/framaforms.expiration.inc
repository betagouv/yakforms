<?php

/**
 * Contain Framaforms custom function related to automatic expiration of user
 * webforms.
 */

/**
* Get all webforms that will expired between now and 2 weeks in the future,
* and insert them into framaforms_expired table.
* @return void
*/
 function make_forms_expire(){
    $expiration_period = variable_get('framaforms_expiration_period_default_value');
    // If the user set the expiration period to 0, don't make the nodes expire.
    if($expiration_period == 0){
      return;
    }
    $expiration_period .= ' weeks';

    $transaction = db_transaction();
    try{
      // Look for nodes expiring in a interval of time set in the global varialbe 'framaforms_expiration_period_default_value'
      db_query(sprintf("
        insert into framaforms_expired (nid)
        select node.nid
        from node
        inner join field_data_field_form1_expiration
        on field_data_field_form1_expiration.entity_id = node.nid
        where node.type='form1'
        and field_data_field_form1_expiration.field_form1_expiration_value <= date_trunc('day', NOW() + interval'%s')
        and field_data_field_form1_expiration.field_form1_expiration_value > date_trunc('day', NOW())
        on conflict do nothing;
        ",$expiration_period));
    }
    catch(Exception $e){
      $transaction->rollback();
      watchdog('framaforms', $e);
    }

    /* Get all the webforms that are about to expire and whose owner wasn't yet notified */
    try{
      $results = db_query("
        select framaforms_expired.nid, users.mail, node.title
        from framaforms_expired
        inner join node
        on framaforms_expired.nid = node.nid
        inner join users
        on users.uid = node.uid
        where framaforms_expired.notified = 0"
        ) ;

      // Notify the users of their forms expiration
      foreach ($results as $record){
        watchdog('framaforms', "Sending email to " . (string)$record->mail .
            " because of expired webform node (nid = " . (string)$record->nid . ")"
        );
        $user_notified = notify_user_of_expiration($record);
        // Update the database with the notification date and set notified to 1
        if($user_notified){
          db_update('framaforms_expired')
            ->fields(array(
              'notified' => 1,
              'date_notified' => time()
            ))
            ->condition('nid', $record->nid, '=')
            ->execute();
        }
      }
    }
    catch(Exception $e){
      $transaction->rollback();
      watchdog('framaforms', $e);
    }
 }

 /**
  * Sends an email by calling drupal_mail to a user,
  * notifying them of the upcoming webform expiration.
  *
  * @param DatabaseStatementInterface $record : Single database statement containing node and user information
  * @param string $expiration_period : notification-expiration time interval
  * @param string $deletion_period : expiration-deletion time interval
  * @return void
  */
function notify_user_of_expiration ($record) {
    global $base_url;  //use the global variable of Drupal for the site's URL
    $expiration_period = variable_get('framaforms_notification_period_value') .' weeks';
    $deletion_period = variable_get('framaforms_deletion_period_value') .' weeks';

    $expiration_date = new DateTime();
    $expiration_date->modify("+".$expiration_period);
    $delete_date = clone $expiration_date;
    $delete_date->modify($deletion_period);
    $delete_date = $delete_date->getTimestamp();
    $expiration_date = $expiration_date->getTimestamp();
  
    $node_url = $base_url . url('node/'.$record->nid);
    $mail_body = variable_get('framaforms_mail_user_notification_body');
    $mail_subject = variable_get('framaforms_mail_user_notification_subject');
    // replace placeholders in the body and subject.
    $placeholders = ['[form_title]', '[form_expires_on]', '[form_delete_on]', '[form_url]'];
    $replacers = [$record->title, $expiration_date, $delete_date, $node_url];
    $mail_subject = str_replace($placeholders, $replacers, $mail_subject);
    $mail_body = str_replace($placeholders, $replacers, $mail_body);

    $mail_params = array(
        'body' => $mail_body,
        'subject' => $mail_subject,
        'headers' => array(),
    );

    watchdog('framaforms', "Sending following email to " . (string)$record->mail . " : " . $body);
    $message = drupal_mail('framaforms', 'expired_webform', (string)$record->mail, user_preferred_language($user), $mail_params);
    return $message['send'];
}

/**
 * Looksup webform nodes in the database that were marked as
 * "expired" but whose expiration date * got changed by the user.
 *
 * @return void
 */
function update_modified_nodes () {
    $expiration_period = variable_get('framaforms_notification_period_value');
    if($expiration_period == 0){
      return;
    }
    $expiration_period .= ' weeks';
    $transaction = db_transaction();
    try{
        //Delete nodes from the framaforms_notified table if their expiration date was pushed back by the user
        $modified_nodes = db_query(sprintf("
            select node.nid
            from node
            inner join field_data_field_form1_expiration
            on field_data_field_form1_expiration.entity_id = node.nid
            inner join framaforms_expired
            on node.nid=framaforms_expired.nid
            where field_data_field_form1_expiration.field_form1_expiration_value
            > to_timestamp(framaforms_expired.date_notified) + interval'%s'
            and node.nid not in (select nid from framaforms_expired)
        ", $expiration_period));
        $nid_changed= 0 ;

        foreach($modified_nodes as $node){
        $nid_changed = $node->nid;
        watchdog('framaforms', "Updating framaforms_expired, deleting the modified webform " .
                (string)$node->nid . " from the framaforms_expired table.");
        db_delete('framaforms_expired')
            ->condition('nid', (int)$nid_changed)
            ->execute() ;
        }
    }
    catch(Exception $e){
        $transaction->rollback();
        watchdog('framaforms', $e);
    }
}

/**
 * Deletes all expired webform nodes after a period of inactivity (defined in $deletion_period).
 * If the webform's expiration date is modified by the user, the update_modified_node()
 * function will delete them from the framaforms_expired table and the rows won't be affected
 * by this function.
 *
 * @param string $deletion_period : form expiration-deletion time interval.
 * @return void
 */
function delete_expired_nodes () {
    // if the user set the deletion period to 0, don't delete the forms
    $deletion_period = variable_get('framaforms_deletion_period_value');
    if($deletion_period == 0){
        return;
    }
    $deletion_period .= ' weeks';
    $deleted_nodes = [];
    $transaction = db_transaction();
    try{
        $query = db_query(sprintf("
            select framaforms_expired.nid
            from framaforms_expired
            where notified=1
            and to_timestamp(framaforms_expired.date_notified) < date_trunc('day', NOW() - interval'%s') ;
            ", $deletion_period));
        $expired_nodes= $query->fetchAll();
        foreach($expired_nodes as $record){
            node_delete($record->nid);
            // also delete it from the framaforms_expired table
            db_delete('framaforms_expired')
            ->condition('nid', $record->nid)
            ->execute();

            $deleted_nodes[] = $record->nid;
        }

        if(!empty($deleted_nodes)){
            watchdog("framaforms", "Deleted following expired webforms : " . explode($deleted_nodes));
            return;
        }
        watchdog("framaforms", "No expired webform to delete.");
    }
    catch(Exception $e){
        $transaction->rollback();
        watchdog('framaforms', $e);
    }
}