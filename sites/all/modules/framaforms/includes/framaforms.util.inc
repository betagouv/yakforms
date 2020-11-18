<?php

/**
 * Returns an Array of the user's form.
 *
 * @param int $uid
 *   The user's uid.
 *
 * @return array
 *   HTML ul element of the user's forms
 */
function _get_user_forms($uid) {
  $users_forms = array();
  try {
    $query = db_select('node', 'n')
      ->fields('n', array('title'))
      ->condition('type', 'form1')
      ->condition('uid', $uid)
      ->range(0, 10)
      ->execute()
      ->fetchAll();

    // Format array from objects.
    foreach ($query as $form) {
      $users_forms[] = $form->title;
    }
  }
  catch (PDOException $e) {
    watchdog('framaforms', "Error getting user's forms : !error", array('!error' => $e));
  }
  return $users_forms;
}


/**
 * Returns HTML-formatted list of the user's forms from an array.
 *
 * @param array $forms
 *   Array containing the forms.
 *
 * @return string
 *   The HTML content.
 */
function _get_html_form_list(array $forms = array()) {
  $list = "<i><ul>";
  foreach ($forms as $form) {
    $list .= "<li>" . $form . "</li>";
  }
  $list .= "<li>...</li>";
  $list .= "</ul></i>";
  return $list;
}

/**
 * Returns expiration timestamp for passed node object.
 *
 * @param object $node
 *   The concerned node.
 *
 * @return int
 *   timestamp for the form's expiration date.
 */
function _get_form_expiration_date(stdClass $node) {
  try {
    $query = db_select('field_data_field_form1_expiration', 'fex')
      ->fields('fex', array('field_form1_expiration_value'))
      ->condition('entity_id', $node->nid)
      ->condition('entity_type', 'node')
      ->condition('bundle', 'form1')
      ->execute()
      ->fetchField();
    $timestamp = strtotime($query);
    if ($timestamp == NULL){
      watchdog('framaforms',
        "Warning : node !nid doesn't seem to have an expiration date, but it was demanded.",
        array('!nid' => $node->nid),
        WATCHDOG_WARNING
      );
    }
    return $timestamp;
  }
  catch (PDOException $e) {
    watchdog('framaforms', "Error getting form's expiration date : !error", array('!error' => $e));
  }
}

/**
 * Returns TRUE if a given form1 node has submissions.
 *
 * @param object $node
 *   An object for the node.
 *
 * @return bool
 *   TRUE if the node has registered submissions.
 */
function _form_has_submission ($node) {
  try {
    $count = db_select('webform_submissions', 'w')
      ->fields('w', array('sid'))
      ->condition('nid', $node->nid)
      ->execute()
      ->rowCount();
    if ($count > 0) {
      return TRUE;
    }
  }
  catch (PDOException $e) {
    watchdog('framaforms', "Error getting form's submissions : !error", array('!error' => $e));
  }
  return FALSE;
}
