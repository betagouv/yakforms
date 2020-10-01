<?php

/**
 * Contains Framaforms custom function related to admin menus
 */

 /**
 * Returns the dashboard page statistics.
 * Accessible at /admin/framaforms/dashboard
 *
 * @return void
 */
function get_dashboard_content () {
    $content .="<ul>";
    $content .="<li>";
    // Append otal number of forms
    $query = db_select('node')->condition('type', 'form1');
    $totalNumberOfForms = $query->execute()->rowCount();
    $content .= "<h3>" . t('Total number of forms') ." : {$totalNumberOfForms} </h3>";

    // Append tatistics about the forms created last weeks / months / year
    $intervals = ["1 week", "1 month", "6 months", "1 year"];
    foreach($intervals as $interval){
        $query = "SELECT *
          FROM node
          WHERE type ='form1'
          AND to_timestamp(created) > NOW() - interval'{$interval}'";
        $results = db_query($query, array())->rowCount();
        $content .= "<h4>". t("Last {$interval} : {$results}") ."</h4>";
    }
    $content .="</li>";

    $content .="<li>";
    // Total number of submissions
    $query = db_select('webform_submissions');
    $results = $query->execute()-> rowCount();
    $averageSubmissions = floor($results / $totalNumberOfForms * 100) / 100;
    $content .=  "<h3>". t("Total number of submissions : "). "{$results} </h3>";
    $content .= "<h4>" . t("For an average of ") . $averageSubmissions . t(" submissions / form)") ." </h4>";
    $content .="</li>";

    $content .="<li>";
    // Total number of users
    $query = db_select('users');
    $results = $query->execute();
    $content .=  "<h3>" .t("Total number of users") . ": {$results->rowCount} </h3>";

    // Users created since a week / month / year
    $query="SELECT uid
      FROM users
      WHERE to_timestamp(created) >= NOW() - interval'%s'";

    foreach($intervals as $interval){
        $results = db_query(sprintf($query, $interval), array())
        ->rowCount();
        $content .=  "<h4>" .t("Registered since {$interval}") . ": {$results} </h4>";
    }
    $content .="</li>";

    $content .="<li>";
    // "Critical forms" (with most submissions)
    $content .= "<h3>". t('Forms with the most submissions') . ": </h3>";
    $content .="<ul>";
    $query = "SELECT count(webform_submissions.nid) as NB, webform_submissions.nid as NID, node.title as TITLE
        from webform_submissions
        inner join node on node.nid = webform_submissions.nid
        group by webform_submissions.nid, node.title
        order by NB DESC
        limit 10";
    $results = db_query($query, array());
    foreach($results as $result){
      $content .= "<li>" . $result->title . " (#{$result->nid}) :  {$result->nb} ". t("submissions"). "</li>";
      $content .= "<a href='/node/{$result->nid}'>" . t("Visit") ."</a>";
    }
    $content .= "</ul>";

    // "Critical" users (authors of the most forms)
    // Excluding Anonymous user (uid = 0) as it can be used by moderation for reattributi abusive forms.
    $content .= "<h3>". t('Users with the most forms') . ": </h3>";
    $content .="<ul>";
    $query = "SELECT users.uid as uid, users.name as name, COUNT(node.nid) as c
      FROM node
      INNER JOIN users ON users.uid = node.uid
      WHERE node.type='form1'
      AND users.uid != 0
      GROUP BY users.uid
      ORDER BY c DESC
      LIMIT 10;";
    $results = db_query($query, array());
    foreach($results as $result){
      $content .= "<li> <a href='/user/{$result->uid}'> {$result->name} </a> (#{$result->uid})
        - <a href='/form-search?status=1&nid=&title=&uid={$result->name}&mail='>{$result->c} forms</a> </li>";
    }
    $content .= "</ul>";

    $content .= "<li>";
    $query = "SELECT pg_size_pretty(pg_database_size(current_database())) AS dbsize";
    $sizeOfDatabase = db_query($query, array())->fetchAssoc()['dbsize'];
    $content .= sprintf("<h3>Size of database :  %s </h3>", $sizeOfDatabase);
    $content .="</li>";
    $content .="</ul>";

    return $content;
}

/**
 * Implements hook_form.
 * Describes the adminstration form, accessible at /admin/config/system/framaforms
 *
 * @return void
 */
function framaforms_config_form ($form, &$form_state) {
    $form['general_intertitle'] = array(
      '#type' => 'item',
      '#markup' => t('<h3>Informations générales du site</h3>'),
    );
    $form['info_intertitle'] = array(
      '#type' => 'item',
      '#markup' => t('<i>Note : ces valeurs peuvent être changées dans d\'autres modules de Drupal, et sont simplement rassemblées ici, par simplicité.</i>'),
    );
    $form['site_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Titre du site'),
      '#default_value' => variable_get('site_name'),
      '#description' => t('Le titre général du site. Il sera affiché notamment sur la page d\'accueil et dans les onglets.'),
      '#required' => TRUE,
    );
    $form['site_slogan'] = array(
      '#type' => 'textfield',
      '#title' => t('Slogan du site'),
      '#default_value' => variable_get('site_slogan'),
      '#description' => t('Une petite phrase ajoutée en sous-titre du site. Ex : "Créer des formulaires facilement".'),
      '#required' => TRUE,
    );
    $form['site_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Mail de contact général'),
      '#default_value' => variable_get('site_mail'),
      '#description' => t('Le mail général du site. Il sera indiqué dans le formulaire de contact par défaut du site, et sera utilisé pour vous avertir d\'éventuelles mises à jour nécessaires.'),
      '#required' => TRUE,
    );
    $form['site_contact_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Lien vers le support'),
      '#default_value' => variable_get('site_contact_url'),
      '#description' => t('Lien vers une éventuelle page de support pour vos utilisateurs. Cette URL sera reprise dans les messages d\'aide à la création des formulaires.'),
      '#required' => TRUE,
    );
    $form['limitations_intertitle'] = array(
      '#type' => 'item',
      '#markup' => t('<h3>Limitations</h3>'),
    );
    $form['framaforms_forms_per_user_limit'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum number of form per user'),
      '#default_value' => variable_get('framaforms_forms_per_user_limit'),
      '#size' => 11,
      '#maxlength' => 11,
      '#required' => TRUE,
    );
    $form['expiration_intertitle'] = array(
      '#type' => 'item',
      '#markup' => t('<h3>Expiration des formulaires</h3>'),
    );
    $form['framaforms_expiration_period_default_value'] = array(
      '#type' => 'textfield',
      '#title' => t('Période d\'expiration (en semaines)'),
      '#default_value' => variable_get('framaforms_expiration_period_default_value'),
      '#size' => 11,
      '#maxlength' => 11,
      '#description' => t('Lorsque l\'utilisateur crée un formulaire, la date d\'expiration du formulaire sera définie par défaut à cette valeur dans le futur. Par exemple : si l\'utilisateur crée un formulaire le 01/01/2020 et que la période est définie à « 5 », le formulaire expirera par défaut le 05/02/2020. Insérer « 0 » si vous ne souhaitez pas que les formulaires n\'expirent jamais.'),
      '#required' => TRUE,
    );
    $form['framaforms_deletion_period_value'] = array(
      '#type' => 'textfield',
      '#title' => t('Période de suppression (en semaines)'),
      '#default_value' => variable_get('framaforms_deletion_period_value'),
      '#size' => 11,
      '#maxlength' => 11,
      '#description' => t('Interval de temps entre l\'expiration d\'un formulaire et sa suppression. Insérer « 0 » si vous ne souhaitez jamais supprimer les formulaires.'),
      '#required' => TRUE,
    );
    $form['framaforms_mail_user_notification_body'] = array(
        '#type' => 'textarea',
        '#title' => t('Mail de notification'),
        '#description' => t('Vous pouvez ici changer le corps du mail qui sera envoyé à l\'utilisateur pour l\'avertir de l\'expiration de son formulaire. </br> <i>Jetons disponibles, que vous pouvez utiliser dans le texte et qui seront remplacés : <strong>[form_url]</strong> (URL du formulaire), <strong>[form_expires_on]</strong> (date d\'expiration du formulaire), <strong>[form_title]</strong> (titre du formulaire).</i>'),
        '#default_value' => variable_get('framaforms_mail_user_notification_body'),
        '#required' => TRUE,
    );
    $form['framaforms_expiration_page_content'] = array(
      '#type' => 'textarea',
      '#title' => t('Page d\'expiration des formulaires'),
      '#description' => t("Vous pouvez ici configurer le contenu de la page d'expiration des formulaires : il s'agit de la page sur laquelle seront redirigé⋅e⋅s les utilisateurices se rendant sur un formulaire dont la date d'expiration est passée. Vous pouvez utiliser les jetons suivants : <strong>[my_forms_url]</strong> (lien vers la page « Mes formulaires »)"),
      '#default_value' => variable_get('framaforms_expiration_page_content'),
      '#required' => TRUE,
    );
    $form['create-default-pages'] = array(
      '#type' => 'button',
      '#value' => t('Générer les pages par défaut'),
      '#description' => t("En cliquant sur ce bouton, vous créerez des pages par défaut pour votre site : page d'accueil, pages d'erreur 404/403, etc. Vous pourrez les modifier ou les supprimer par la suite."),
      '#submit' => array('admin_menu_create_pages_callback'),
      '#executes_submit_callback' => TRUE,
    );
    $form['reset-variables'] = array(
      '#type' => 'button',
      '#value' => t('Reset all'),
      '#description' => t("Reset all global variables to their initial value."),
      '#submit' => array('framaforms_admin_menu_reset_variables_callback'),
      '#executes_submit_callback' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#submit' => array('system_settings_form_submit'),
    );
    return $form;
}

/**
 * Secondary callback for the "Generate pages" button
 *
 * @return void
 */
function admin_menu_create_pages_callback () {
  module_load_include('inc', 'framaforms', 'includes/framaforms.pages');
  create_all_pages();
  drupal_set_message("Les pages ont bien été créées.");
}

/**
 * Inplements hook_form_validate : checks the values of expiration and deletion period
 *  and checks they are numeric.
 * @return void
 */
function framaforms_config_form_validate ($form, &$form_state) {
  $values = $form_state['values'];
  if(!is_numeric($values['framaforms_deletion_period_value'])){
    drupal_set_message(t("Erreur dans les valeurs administratives de Framaforms."));
    form_set_error('framaforms_deletion_period_value', t("a période de suppression doit être numérique."));
  }
  if(!is_numeric($values['framaforms_expiration_period_default_value'])){
    drupal_set_message(t("Erreur dans les valeurs administratives de Framaforms."));
    form_set_error('framaforms_expiration_period_default_value', t("La période d'expiration doit être numérique."));
  }
  if(!is_numeric($values['framaforms_forms_per_user_limit'])){
    drupal_set_message(t("Erreur dans les valeurs administratives de Framaforms."));
    form_set_error('framaforms_forms_per_user_limit', t("The number of form per user must be numeric."));
  }

}

/**
 * Implements hook_form_submit
 * @return void
 */
function framaforms_config_form_submit ($form, &$form_state) {
  drupal_set_message('form submitted !');
}

/**
 * Callback calling
 *
 * @return void
 */
function framaforms_admin_menu_reset_variables_callback () {
  module_load_include('install', 'framaforms', 'framaforms');
  framaforms_set_default_variables();
  drupal_set_message(t("All global variables for Framaforms were reset."),'status', FALSE);
}