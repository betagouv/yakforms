<?php

/**
 * @file
 * Contains Framaforms custom function related to block contents.
 */

/**
 * Returns the content for the personal contact form block.
 *
 * @param int $nid
 *   The current page nid.
 *
 * @return string
 *   The markup content to be rendered.
 */
function get_contact_form_content($nid) {
  $content = "";
  try {
    if (isset($nid)) {
      $query_str = sprintf("SELECT users.name, users.uid FROM node INNER JOIN users ON node.uid = users.uid WHERE node.nid=%s;", $nid);
      $results = db_query($query_str)->fetchAssoc();
      $name = $results ? $results['name'] : NULL;
      $uid = $results ? $results['uid'] : NULL;

      $query_str = sprintf("SELECT users.data FROM node INNER JOIN users ON node.uid = users.uid WHERE node.nid=%s;", $nid);
      $results = db_query($query_str)->fetchAssoc();
      $contact = unserialize($results['data'])['contact'];
    }
    if ($nid && isset($name) && isset($uid) && $contact == 1) {
      $url_contact = '/' . drupal_get_path_alias('user/' . $uid) . '/contact';
      $content .= "<h3>" . t("Contact the author of this form") . "</h3>";
      $content .= "<p>" . t("To contact the author of this form, <a href='@link'> click here</a>", array('@link' => $url_contact)) . "<p>";
      $content .= "<br>";
    }
  }
  catch (Exception $e) {
    watchdog('framaforms', 'Error in the contact form block (modules/framaforms/includes/framaforms.block.inc) : %error', array('%error' => $e), WATCHDOG_WARNING);
  }
  return $content;
}

/**
 * Returns true if the node whose NID is passed is of type form1.
 *
 * @param int $nid
 *   : the NID of the node.
 *
 * @return bool
 *   TRUE if the node is a form1 node
 */
function node_is_form1($nid) {
  if (!isset($nid)) {
    return FALSE;
  }
  $node = node_load($nid);
  if (isset($node->type) && $node->type == 'form1') {
    return TRUE;
  }
  return FALSE;
}
