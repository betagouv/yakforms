<?php
/**
 * @file
 */

include_once 'webform_confirm_email.inc';

module_load_include('inc', 'webform', 'includes/webform.report');
module_load_include('inc', 'webform', 'includes/webform.submissions');

/**
 * Helper function to propvide a form for filtering for (un)confirmed submissions
 */
function webform_confirm_email_confirmed_filter_form($form, &$form_state) {
  $options = array(
    WEBFORM_CONFIRM_EMAIL_FILTER_NONE        => t('All submissions'),
    WEBFORM_CONFIRM_EMAIL_FILTER_CONFIRMED   => t('Only confirmed submissions'),
    WEBFORM_CONFIRM_EMAIL_FILTER_UNCONFIRMED => t('Only unconfirmed submissions'),
  );
  $query = drupal_get_query_parameters();
  $confirmed = isset($query['confirmed']) ? $query['confirmed'] : WEBFORM_CONFIRM_EMAIL_FILTER_NONE;
  // Set the confirmed filter for queries in the same request.
  _webform_confirm_email_range_confirmed($confirmed);
  $form['confirmed']= array(
    '#type'          => 'radios',
    '#title'         => t('Filter for (un)confirmed submissions'),
    '#default_value' => $confirmed,
    '#options'       => $options,
    '#access'        => TRUE,
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Filter submissions'),
  );

  $form['#submit'] = array('webform_confirm_email_confirmed_filter_form_submit');

  return $form;
}

/**
 * Submit handler for filter form for filtering for (un)confirmed submissions
 */
function webform_confirm_email_confirmed_filter_form_submit($form, &$form_state) {
  $path = current_path();
  $query_parameters = drupal_get_query_parameters();
  if (   isset($form_state['values']['confirmed']) == TRUE
      && $form_state['values']['confirmed'] != WEBFORM_CONFIRM_EMAIL_FILTER_NONE) {
    $query_parameters['confirmed'] = $form_state['values']['confirmed'];
  }
  else {
    unset($query_parameters['confirmed']);
  }

  drupal_goto($path, array('absolute' => TRUE, 'query' => $query_parameters));
}

function webform_confirm_email_results_submissions($node, $user_filter, $pager_count) {
  global $user;

  // Load this early on so that the filter is set before executing the queries.
  $element['confirmed_form'] = drupal_get_form('webform_confirm_email_confirmed_filter_form');

  if (isset($_GET['results']) && is_numeric($_GET['results'])) {
    $pager_count = $_GET['results'];
  }

  $header = theme('webform_results_submissions_header', array('node' => $node));
  if ($user_filter) {
    if ($user->uid) {
      drupal_set_title(t('Submissions for %user', array('%user' => $user->name)), PASS_THROUGH);
    }
    else {
      drupal_set_title(t('Your submissions'));
      webform_disable_page_cache();
    }
    $submissions = webform_get_submissions(array('nid' => $node->nid, 'uid' => $user->uid), $header, $pager_count);
    $count = webform_get_submission_count($node->nid, $user->uid, NULL);
  }
  else {
    $submissions = webform_get_submissions($node->nid, $header, $pager_count);
    $count = webform_get_submission_count($node->nid, NULL, NULL);
  }

  $operation_column = end($header);
  $operation_total = $operation_column['colspan'];

  $rows = array();
  foreach ($submissions as $sid => $submission) {
    $row = array(
      $submission->is_draft ? t('@serial (draft)', array('@serial' => $submission->serial)) : $submission->serial,
      format_date($submission->submitted, 'short'),
    );
    if (webform_results_access($node, $user)) {
      $row[] = theme('username', array('account' => $submission));
      $row[] = $submission->remote_addr;
    }
    $row[] = l(t('View'), "node/$node->nid/submission/$sid");
    $operation_count = 1;
    // No need to call this multiple times, just reference this in a variable.
    $destination = drupal_get_destination();
    if (webform_submission_access($node, $submission, 'edit', $user)) {
      $row[] = l(t('Edit'), "node/$node->nid/submission/$sid/edit", array('query' => $destination));
      $operation_count++;
    }
    if (webform_submission_access($node, $submission, 'delete', $user)) {
      $row[] = l(t('Delete'), "node/$node->nid/submission/$sid/delete", array('query' => $destination));
      $operation_count++;
    }
    if ($operation_count < $operation_total) {
      $row[count($row) - 1] = array('data' => $row[count($row) - 1], 'colspan' => $operation_total - $operation_count + 1);
    }
    $rows[] = $row;
  }

  $element['#theme'] = 'webform_confirm_email_results_submissions';
  $element['#node'] = $node;
  $element['#submissions'] = $submissions;
  $element['#total_count'] = $count;
  $element['#pager_count'] = $pager_count;
  $element['#attached']['library'][] = array('webform', 'admin');

  $element['table']['#theme'] = 'table';
  $element['table']['#header'] = $header;
  $element['table']['#rows'] = $rows;
  $element['table']['#operation_total'] = $operation_total;

  return $element;
}

/**
 * Preprocess function for webform-confirm-email-results-submissions.tpl.php
 */
function template_preprocess_webform_confirm_email_results_submissions(&$vars) {
  $vars['node'] = $vars['element']['#node'];
  $vars['submissions'] = $vars['element']['#submissions'];
  $vars['confirmed_form'] = $vars['element']['confirmed_form'];
  $vars['table'] = $vars['element']['table'];
  $vars['total_count'] = $vars['element']['#total_count'];
  $vars['pager_count'] = $vars['element']['#pager_count'];
  $vars['is_submissions'] = (arg(2) == 'submissions')? 1 : 0;

  unset($vars['element']);
}

/**
 * Create a table containing all submitted values for a webform node.
 */
function webform_confirm_email_results_table($node, $pager_count = 0) {
  if (isset($_GET['results']) && is_numeric($_GET['results'])) {
    $pager_count = $_GET['results'];
  }

  // Load this early on so that the filter is set before executing the queries.
  $confirmed_form = drupal_get_form('webform_confirm_email_confirmed_filter_form');

  // Get all the submissions for the node.
  $header = theme('webform_results_table_header', array('node' => $node));
  $submissions = webform_get_submissions($node->nid, $header, $pager_count);
  $total_count = webform_get_submission_count($node->nid);

  $output = theme(
    'webform_confirm_email_results_table',
    array(
      'confirmed_form' => $confirmed_form,
      'node'           => $node,
      'components'     => $node->webform['components'],
      'submissions'    => $submissions,
      'total_count'    => $total_count,
      'pager_count'    => $pager_count
    )
  );
  if ($pager_count) {
    $output .= theme('pager');
  }
  return $output;
}

function theme_webform_confirm_email_results_table($variables) {
  $output = drupal_render($variables['confirmed_form']);
  $output .= theme_webform_results_table($variables);

  return $output;
}
