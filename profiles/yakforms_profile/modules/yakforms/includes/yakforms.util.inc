<?php

/**
 * @file
 * Contain general-purpose function related to Yakforms.
 */

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
    watchdog('yakforms', "Error getting user's forms : !error", array('!error' => $e));
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
    if ($timestamp == NULL) {
      watchdog('yakforms',
        "Warning : node !nid doesn't seem to have an expiration date, but it was demanded.",
        array('!nid' => $node->nid),
        WATCHDOG_WARNING
      );
    }
    return $timestamp;
  }
  catch (PDOException $e) {
    watchdog('yakforms', "Error getting form's expiration date : !error", array('!error' => $e));
  }
}

/**
 * Returns TRUE if a given form1 node has submissions.
 *
 * @param object $node
 *   An object for the node.
 *
 * @return int
 *   The number of registered submissions.
 */
function _form_has_submissions($node) {
  if (!isset($node->nid)) {
    return FALSE;
  }
  try {
    $count = db_select('webform_submissions', 'w')
      ->fields('w', array('sid'))
      ->condition('nid', $node->nid)
      ->execute()
      ->rowCount();
  }
  catch (PDOException $e) {
    watchdog('yakforms', "Error getting form's submissions : !error", array('!error' => $e));
    $count = 0;
  }
  return $count;
}

/**
 * Get the maximum number of submission allowed for a given form.
 *
 * If the user has set a limit, then this is the one that will be returned. If
 * not, the site-wide limitation will be returned.
 *
 * @return int
 *   The maximum number of submissions.
 */
function _get_form_submission_limit($node) {
  $user_limit = intval($node->webform['total_submit_limit']);
  // Limit can be 0 or -1 if it hasn't been set.
  if ($user_limit < 0) {
    $user_limit = 0;
  }
  $sitewide_limit = variable_get('yakforms_submissions_per_form_limit', 0);
  // If one of the limits is not set, return the one that is set.
  if ($sitewide_limit === 0 || $user_limit === 0) {
    return max($sitewide_limit, $user_limit);
  }
  // If both limits are set, return the user-defined limit.
  return $user_limit;
}

/**
 * Get messages to display on form display.
 *
 * @param object $node
 *   The node accessed by the user.
 *
 * @return array
 *   An array of messages to display.
 */
function _get_client_messages($node) {
  $messages = array();
  $max_submissions = _get_form_submission_limit($node);
  // If the submission limit is almost reached, warn the current user.
  $form_submissions = _form_has_submissions($node);
  if ($form_submissions > $max_submissions - 10
    && $form_submissions < $max_submissions
    && $max_submissions > 0) {
    $messages[] = array(
      'message' => t("The maximum number of submissions is almost reached for this form (less than 10 submissions left)."),
      'level' => 'warning',
    );
  }
  return $messages;
}

/**
 * Returns translatables that aren't automatically extracted via POTX.
 *
 * This function is never actually used, it just exposes strings to potx.
 *
 * @return array
 *   Strings that should be translated.
 */
function yakforms_translatables() {
  return array(
    t("You form already has submissions. You might loose your data by editing or removing form fields."),
    t("Changing this form's title will also change its URL. If you have already transmitted a link to your users, it will return an error."),
  );
}

/**
 * Returns TRUE if the form is in the yakforms_expired table.
 *
 * @param object $node
 *   The node object.
 *
 * @return bool
 *   TRUE if the form is in yakforms_expired.
 */
function _form_is_almost_expired($node) {
  try {
    $expired_node = db_select('yakforms_expired', 'fex')
      ->fields('fex', array('nid'))
      ->condition('nid', $node->nid)
      ->execute()
      ->rowCount();
  }
  catch (PDOException $e) {
    watchdog(
      'yakforms',
      'Error updating node !nid : %error',
      array(
        '%error' => $e,
        '!nid' => $node->nid,
      ),
      WATCHDOG_WARNING);
  }

  if ($expired_node > 0) {
    return TRUE;
  }
  return FALSE;
}
