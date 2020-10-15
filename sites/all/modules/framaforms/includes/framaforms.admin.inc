<?php

/**
 * @file
 * Contains Framaforms custom function related to admin menus.
 */

/**
 * Returns the dashboard page statistics.
 * Accessible at /admin/framaforms/dashboard.
 *
 * @return void
 */
function get_dashboard_content() {
  $content .= "<ul>";
  $content .= "<li>";
  // Append otal number of forms.
  $query = db_select('node')->condition('type', 'form1');
  $totalNumberOfForms = $query->execute()->rowCount();
  $content .= "<h3>" . t('Total number of forms : @number', array('@number' => $totalNumberOfForms)) . "</h3>";

  // Append tatistics about the forms created last weeks / months / year.
  $intervals = ["1 week", "1 month", "6 months", "1 year"];
  foreach ($intervals as $interval) {
    $query = "SELECT *
          FROM node
          WHERE type ='form1'
          AND to_timestamp(created) > NOW() - interval'{$interval}'";
    $results = db_query($query, array())->rowCount();
    $content .= "<h4>" . t("Last @interval : @results", array('@interval' => $interval, '@results' => $results)) . "</h4>";
  }
  $content .= "</li>";

  $content .= "<li>";
  // Total number of submissions.
  $query = db_select('webform_submissions');
  $results = $query->execute()->rowCount();
  $averageSubmissions = floor($results / $totalNumberOfForms * 100) / 100;
  $content .= "<h3>" . t("Total number of submissions : @number", array('@number' => $results)) . " </h3>";
  $content .= "<h4>" . t("(For an average of @number submissions / form)", array('@number' => $averageSubmissions)) . " </h4>";
  $content .= "</li>";

  $content .= "<li>";
  // Total number of users.
  $query = db_select('users');
  $results = $query->execute();
  $content .= "<h3>" . t("Total number of users : @number", array('@number' => $results->rowCount())) . "</h3>";

  // Users created since a week / month / year.
  $query = "SELECT uid
      FROM users
      WHERE to_timestamp(created) >= NOW() - interval'%s'";

  foreach ($intervals as $interval) {
    $results = db_query(sprintf($query, $interval), array())
      ->rowCount();
    $content .= "<h4>" . t("Registered since @interval : @number", array('@interval' => $interval, '@number' => $results)) . "</h4>";
  }
  $content .= "</li>";

  $content .= "<li>";
  // "Critical forms" (with most submissions)
  $content .= "<h3>" . t("Forms with the most submissions :") . "</h3>";
  $content .= "<ul>";
  $query = "SELECT count(webform_submissions.nid) as NB,
        webform_submissions.nid as NID,
        node.title as TITLE
        from webform_submissions
        inner join node on node.nid = webform_submissions.nid
        group by webform_submissions.nid, node.title
        order by NB DESC
        limit 10";
  $results = db_query($query, array());
  foreach ($results as $result) {
    $content .= "<li>" . $result->title . " (#{$result->nid}) :  {$result->nb} " . t("submissions") . "</li>";
    $content .= "<a href='/node/{$result->nid}'>" . t("Visit") . "</a>";
  }
  $content .= "</ul>";

  // "Critical" users (authors of the most forms)
  // Excluding Anonymous user (uid = 0) as it can be used by moderation for reattributi abusive forms.
  $content .= "<h3>" . t('Users with the most forms') . ": </h3>";
  $content .= "<ul>";
  $query = "SELECT users.uid as uid, users.name as name, COUNT(node.nid) as c
      FROM node
      INNER JOIN users ON users.uid = node.uid
      WHERE node.type='form1'
      AND users.uid != 0
      GROUP BY users.uid
      ORDER BY c DESC
      LIMIT 10;";
  $results = db_query($query, array());
  foreach ($results as $result) {
    $content .= "<li> <a href='/user/{$result->uid}'> {$result->name} </a> (#{$result->uid})
      - <a href='/form-search?status=1&nid=&title=&uid={$result->name}&mail='>{$result->c} forms</a> </li>";
  }
  $content .= "</ul>";

  $content .= "<li>";
  $query = "SELECT pg_size_pretty(pg_database_size(current_database()))
    AS dbsize";
  $sizeOfDatabase = db_query($query, array())->fetchAssoc()['dbsize'];
  $content .= "<h3>" . t("Size of database :  @size", array('@size' => $sizeOfDatabase)) . "</h3>";
  $content .= "</li>";
  $content .= "</ul>";

  return $content;
}

/**
 * Implements hook_form.
 * Describes the adminstration form, accessible at /admin/config/system/framaforms.
 *
 * @return the configuration form.
 */
function framaforms_config_form($form, &$form_state) {
  $form['general_intertitle'] = array(
    '#type' => 'item',
    '#markup' => "<h3>" . t("General website information"). "<h3>"
  );
  $form['info_intertitle'] = array(
    '#type' => 'item',
    '#markup' => "<i>" . t("Note : some of these values can be changed elsewhere on the website, they are simply centralized here.") . "</i>"
  );
  $form['site_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Website title"),
    '#default_value' => variable_get('site_name'),
    '#description' => t("The title of this website. It will be displayed in the top header."),
    '#required' => true,
  );
  $form['site_slogan'] = array(
    '#type' => 'textfield',
    '#title' => t("Website slogan"),
    '#default_value' => variable_get('site_slogan'),
    '#description' => t("Small phrase displayed under the title. Ex : 'Create forms easily'"),
    '#required' => true,
  );
  $form['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t("General contact email"),
    '#default_value' => variable_get('site_mail'),
    '#description' => t("It will be used in the general contact form of the website, and used to warn you of pending updates."),
    '#required' => true,
  );
  $form['site_contact_url'] = array(
    '#type' => 'textfield',
    '#title' => t("Link to support"),
    '#default_value' => variable_get('site_contact_url'),
    '#description' => t("Link to a support page for your users. This will be displayed when if your users encounter problems creating forms."),
    '#required' => true,
  );
  $form['limitations_intertitle'] = array(
    '#type' => 'item',
    '#markup' => "<h3>" . t("Limitations") . "</h3>",
  );
  $form['framaforms_forms_per_user_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of form per user'),
    '#default_value' => variable_get('framaforms_forms_per_user_limit'),
    '#size' => 11,
    '#maxlength' => 11,
    '#required' => true,
  );
  $form['expiration_intertitle'] = array(
    '#type' => 'item',
    '#markup' => "<h3>" . t("Forms expiration") . "<h3>",
  );
  $form['framaforms_expiration_period_default_value'] = array(
    '#type' => 'textfield',
    '#title' => t("Expiration period (in weeks)"),
    '#default_value' => variable_get('framaforms_expiration_period_default_value'),
    '#size' => 11,
    '#maxlength' => 11,
    '#description' => t("When a user creates a form, its expiration date will be set by default at this interval in the futur. Ex : if a user creates a form on 01/01/2020 and the expiration value is set to '5', the form will expire by default on 02/05/2020. Insert '0' if you don't want forms to expire."),
    '#required' => true,
  );
  $form['framaforms_deletion_period_value'] = array(
    '#type' => 'textfield',
    '#title' => t("Deletion period (in weeks)"),
    '#default_value' => variable_get('framaforms_deletion_period_value'),
    '#size' => 11,
    '#maxlength' => 11,
    '#description' => t("Interval of time between the form expiration and its deletion from the database. Insert '0' if you don't want forms to be deleted."),
    '#required' => true,
  );
  $form['framaforms_export_form_submissions_before_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t("Save form submissions before deleting"),
    '#default_value' => variable_get('framaforms_export_form_submissions_before_delete', false),
    '#description' => t("Check this box if you want all form submissions to be saved before deletion. This can be useful for user support."),
    '#required' => false,
  );
  $form['framaforms_mail_user_notification_body'] = array(
    '#type' => 'textarea',
    '#title' => t("Notification email"),
    '#description' => t("Here you can change the content of the email that will be sent to the user warning them of expired forms. <i>You can use the following tokens that will be replaced : <strong>[form_url]</strong> (the form URL), <strong>[form_expires_on]</strong> (the form's expiration date), <strong>[form_title]</strong> (the form's title).</i>"),
    '#default_value' => variable_get('framaforms_mail_user_notification_body'),
    '#required' => true,
  );
  $form['create-default-pages'] = array(
    '#type' => 'button',
    '#value' => t("Generate default pages"),
    '#description' => t("By clicking this button, you will create default pages for your website : homepage, 404/403 error pages, etc. You can modify them afterwards."),
    '#submit' => array('admin_menu_create_pages_callback'),
    '#executes_submit_callback' => true,
  );
  $form['reset-variables'] = array(
    '#type' => 'button',
    '#value' => t("Reset all"),
    '#description' => t("Reset all global variables to their initial value."),
    '#submit' => array('framaforms_admin_menu_reset_variables_callback'),
    '#executes_submit_callback' => true,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Submit"),
    '#submit' => array('system_settings_form_submit'),
  );
  return $form;
}

/**
 * Secondary callback for the "Generate pages" button.
 *
 * @return void
 */
function admin_menu_create_pages_callback() {
  module_load_include('inc', 'framaforms', 'includes/framaforms.pages');
  create_all_pages();
  drupal_set_message(t("The default pages were created."));
}

/**
 * Inplements hook_form_validate : checks the values of expiration and deletion period
 *  and checks they are numeric.
 *
 * @return void
 */
function framaforms_config_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!is_numeric($values['framaforms_deletion_period_value'])) {
    drupal_set_message(t("There was an error in the form values."));
    form_set_error('framaforms_deletion_period_value', t("The deletion period must be a number."));
  }
  if (!is_numeric($values['framaforms_expiration_period_default_value'])) {
    drupal_set_message(t("There was an error in the form values."));
    form_set_error('framaforms_expiration_period_default_value', t("The expiration period must be a number."));
  }
  if (!is_numeric($values['framaforms_forms_per_user_limit'])) {
    drupal_set_message(t("There was an error in the form values."));
    form_set_error('framaforms_forms_per_user_limit', t("The number of form per user must be a number."));
  }

  // Create the backup directory for form submissions if necessary.
  $backup_dir_path = variable_get('file_private_path') ."/framaforms_submissions_backup/";
  $backup_dir_writable = file_prepare_directory($backup_dir_path, FILE_CREATE_DIRECTORY);
  if($values['framaforms_export_form_submissions_before_delete'] && !$backup_dir_writable) {
    drupal_set_message(
      t("The following directory doesn't exist or is not writable : !path.", array('!path' => $backup_dir_path)),
      'error',
      false
  );
  }
}

/**
 * Implements hook_form_submit.
 *
 * @return void
 */
function framaforms_config_form_submit($form, &$form_state) {
  drupal_set_message(t("The form was submitted !"));
  // Create private backup subfolder if it doesn't yet exist.

}

/**
 * Callback calling.
 *
 * @return void
 */
function framaforms_admin_menu_reset_variables_callback() {
  module_load_include('install', 'framaforms', 'framaforms');
  framaforms_set_default_variables();
  drupal_set_message(t("All global variables for Framaforms were reset."), 'status', FALSE);
}
