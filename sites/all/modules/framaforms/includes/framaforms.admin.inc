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
    $content .= sprintf("<h3>Nombre total de formulaires : %s </h3>", $totalNumberOfForms);

    // Append tatistics about the forms created last weeks / months / year
    $intervals = array("1 week" => t("1 semaine"), "1 month" => t("1 mois"), "6 months" => t("6 mois"), "1 year" => t("1 an"));
    foreach($intervals as $interval => $translation){
        $query = sprintf("select *
        from node where type ='form1'
        and to_timestamp(created) > date_trunc('day', NOW() - interval'%s')",
        $interval);
        $results = db_query($query, array())->rowCount();
        $content .= sprintf("<h4>Dont créé depuis %s : %s </h4>", $translation, $results);
    }
    $content .="</li>";

    $content .="<li>";
    // Total number of submissions
    $query = db_select('webform_submissions');
    $results = $query->execute()-> rowCount();
    $averageSubmissions = floor($results / $totalNumberOfForms * 100) / 100;
    $content .=  sprintf("<h3>Nombre total de réponses : %s </h3>", $results);
    $content .= sprintf("<h4>(soit en moyenne %s réponses / formulaire) </h4>", $averageSubmissions);
    $content .="</li>";

    $content .="<li>";
    // Total number of users
    $query = db_select('users');
    $results = $query->execute();
    $content .=  sprintf("<h3>Nombre total d'utilisateurs : %s </h3>", $results->rowCount());

    // Users created since a week / month / year
    $query="SELECT uid FROM users WHERE to_timestamp(created) >= date_trunc('day', NOW() - interval'%s')";
    foreach($intervals as $interval => $translation){
        $results = db_query(sprintf($query, $interval), array())
        ->rowCount();
        $content .=  sprintf("<h4>Dont créé depuis %s : %s </h4>", $translation, $results);
    }
    $content .="</li>";

    $content .="<li>";
    // "Critical forms" (with most submissions)
    $content .= "<h3>Formulaires avec le plus de réponses :  </h3>";
    $content .="<ul>";
    $query = "SELECT count(webform_submissions.nid) as NB, webform_submissions.nid as NID, node.title as TITLE
        from webform_submissions
        inner join node on node.nid = webform_submissions.nid
        group by webform_submissions.nid, node.title
        order by NB DESC
        limit 10";
    $results = db_query($query, array());
    foreach($results as $result){
    $content .= sprintf("<li>%s (#%s)  :  %s réponses </li>", $result->title, $result->nid, $result->nb);
    $content .= sprintf("<a href='/node/%s'>Visiter</a>", $result->nid);
    }
    $content .= "</ul>";

    $content .= "<li>";
    $query = "SELECT pg_size_pretty(pg_database_size(current_database())) as dbsize";
    $sizeOfDatabase = db_query($query, array())->fetchAssoc()['dbsize'];
    $content .= sprintf("<h3>Taille totale de la base de données :  %s </h3>", $sizeOfDatabase);
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
    return system_settings_form($form);
  }

  /**
   * Inplements hook_form_validate : checks the values for the Framaofrms module configuration form
   * @return void
   */
  function framaforms_config_form_validate ($form, &$form_state) {
    //assert that time interval values are numeric
    $expiration_interval = $form_state['values']['framaforms_expiration_default_value'];
    if(!is_numeric($expiration_interval)){
      form_set_error(t('Les valeurs de temps doivent être exprimées en chiffres.'));
    }
    $deletion_interval = $form_state['values']['framaforms_deletion_period_value'];
    if(!is_numeric($deletion_interval)){
      form_set_error(t('Les valeurs de temps doivent être exprimées en chiffres.'));
    }
  }