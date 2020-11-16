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

    // Format array from objects
    foreach ($query as $form){
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
