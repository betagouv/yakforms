<?php

/**
 * @file
 * framaforms_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function framaforms_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'comment-comment_node_article-comment_body'.
  $field_instances['comment-comment_node_article-comment_body'] = array(
    'bundle' => 'comment_node_article',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'comment-comment_node_form1-comment_body'.
  $field_instances['comment-comment_node_form1-comment_body'] = array(
    'bundle' => 'comment_node_form1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'comment-comment_node_page-comment_body'.
  $field_instances['comment-comment_node_page-comment_body'] = array(
    'bundle' => 'comment_node_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'comment-comment_node_webform_report-comment_body'.
  $field_instances['comment-comment_node_webform_report-comment_body'] = array(
    'bundle' => 'comment_node_webform_report',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'node-article-body'.
  $field_instances['node-article-body'] = array(
    'bundle' => 'article',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'node-article-field_image'.
  $field_instances['node-article-field_image'] = array(
    'bundle' => 'article',
    'deleted' => 0,
    'description' => 'Transférer une image pour accompagner cet article.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'large',
        ),
        'type' => 'image',
        'weight' => -1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'medium',
        ),
        'type' => 'image',
        'weight' => -1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_image',
    'label' => 'Image',
    'required' => FALSE,
    'settings' => array(
      'alt_field' => TRUE,
      'default_image' => 0,
      'file_directory' => 'field/image',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => -1,
    ),
  );

  // Exported field_instance: 'node-article-field_tags'.
  $field_instances['node-article-field_tags'] = array(
    'bundle' => 'article',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Saisissez une liste de mots séparés par des virgules pour décrire votre contenu.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => 'Tags',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'node-form1-body'.
  $field_instances['node-form1-body'] = array(
    'bundle' => 'form1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Décrivez l\'objectif de votre formulaire, ce texte apparaîtra en en-tête<br/>
Si vous souhaitez intégrer des images, nous vous conseillons d\'utiliser un service d\'hébergement externe, comme <a href="https://framapic.org" target="_blank">https://framapic.org</a> par exemple.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Description',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'ds_code' => 0,
          'filtered_html' => 0,
          'full_html' => 0,
          'php_code' => 0,
          'plain_text' => 0,
          'wysiwyg_admin' => 0,
          'wysiwyg_form' => 0,
          'wysiwyg_user' => 'wysiwyg_user',
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'ds_code' => array(
              'weight' => 12,
            ),
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => -5,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
            'wysiwyg_admin' => array(
              'weight' => 0,
            ),
            'wysiwyg_form' => array(
              'weight' => -9,
            ),
            'wysiwyg_user' => array(
              'weight' => 0,
            ),
          ),
        ),
      ),
      'display_summary' => 0,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_expiration'.
  $field_instances['node-form1-field_form1_expiration'] = array(
    'bundle' => 'form1',
    'deleted' => 0,
    'description' => 'Les Framaforms deviennent inaccessibles au bout de 6 mois, et sont détruits au début du 8e mois (ce qui couvre 90% des usages, et nous évite de surcharger notre base de données).

A la date indiquée, votre formulaire ci-dessus ne sera plus accessible publiquement.
Cependant, pendant encore 60 jours, vous et vous seul pourrez y accéder - ainsi qu\'aux résultats - depuis votre compte. Pour le prolonger à nouveau de 6 mois, il vous suffit de le mettre à jour en l\'éditant et en modifiant la date d\'expiration.<br/>
Si ce fonctionnement ne vous convient pas ou que vous souhaitez avoir plus d\'informations, merci de lire la page <a href="/limitations">limitations</a>.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_expiration',
    'label' => 'Date d\'expiration',
    'required' => 1,
    'settings' => array(
      'default_value' => 'strtotime',
      'default_value2' => 'same',
      'default_value_code' => '+6 months',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'Y-m-d H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-0:+1',
      ),
      'type' => 'date_popup',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_file'.
  $field_instances['node-form1-field_form1_file'] = array(
    'bundle' => 'form1',
    'deleted' => 0,
    'description' => 'Vous pouvez joindre jusqu\'à 5 fichiers à votre formulaire.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_file',
    'label' => 'Fichiers attachés',
    'required' => 0,
    'settings' => array(
      'description_field' => 1,
      'file_directory' => 'forms/files',
      'file_extensions' => 'txt pdf doc odt png jpg gif rtf xls ods ppt pptx docx xlsx odp',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_image'.
  $field_instances['node-form1-field_form1_image'] = array(
    'bundle' => 'form1',
    'deleted' => 0,
    'description' => 'Image optionnelle qui sera affichée en haut de votre formulaire (logo ou bandeau d\'illustration, par exemple).<br/>
Après l\'avoir choisie en cliquant sur "Parcourir", n\'oubliez pas de cliquer sur "Transférer" pour qu\'elle soit transférée sur Framaforms.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_image',
    'label' => 'Image d\'illustration optionnelle',
    'required' => 0,
    'settings' => array(
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => 'forms/img',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'medium',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_results_access'.
  $field_instances['node-form1-field_form1_results_access'] = array(
    'bundle' => 'form1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Vous pouvez autoriser d\'autres utilisateurs Framaforms à accéder aux <u>résultats du formulaire</u> : cela implique qu\'ils aient déjà créé leur compte Framaforms.<br>
Pour cela, ajoutez dans le champs ci dessus le « nom d\'utilisateur Framaforms » des personnes concernées (séparés par une virgule s\'il vous autorisez plusieurs comptes).<br>
Une fois connectées à leur compte, ces personnes pourront alors accéder aux résultats en se rendant sur la page du formulaire, puis en cliquant sur l\'onglet Résultats. Elles auront aussi l\'autorisation d\'éditer et de supprimer ces résultats. <strong>En revanche, elles n\'auront PAS la possibilité de modifier le formulaire lui-même</strong> (ajout / suppression de champ, modification du titre, etc).<br>
Pour plus d\'informations, voir <a href=https://docs.framasoft.org/fr/framaforms/fonctionnalites.html#partage-des-r%C3%A9sultats>notre documentation</a>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 7,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_results_access',
    'label' => 'Utilisateurs ayant accès aux résultats',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_results_public'.
  $field_instances['node-form1-field_form1_results_public'] = array(
    'bundle' => 'form1',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '<p>En choisissant "Oui", l\'ensemble des résultats de votre formulaire sera accessible <strong>à tout le monde</strong>. Même si les personnes ne peuvent pas modifier les résultats, cela n\'est <strong>PAS RECOMMANDÉ</strong> car vous pouvez rendre public des informations personnelles (type : nom, prénom, email, adresses ou n° de téléphone) de personnes qui ne souhaitaient pas les rendre publiques.</p>
<p><strong>En choisissant "Oui", vous vous engagez à respecter l\'anonymat des participant⋅e⋅s et vous prenez l\'entière responsabilité des informations qui seront divulguées.</strong></p>
<p>Notez qu\'il existe une option "Utilisateurs ayant accès aux résultats" juste en dessous qui permet de donner l\'accès aux résultats (en visualisation/modification/suppression) à une liste d\'utilisateurs de Framaforms de votre choix.<p>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_results_public',
    'label' => 'Accès public aux résultats',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_template'.
  $field_instances['node-form1-field_form1_template'] = array(
    'bundle' => 'form1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Si vous cochez cette case, votre formulaire sera affiché parmi la <a href="/templates">liste publique des modèles</a>, autorisant n\'importe qui à le dupliquer et à l\'utiliser comme modèle de formulaire (par exemple pour en faire une adaptation).
<strong>Attention : s\'il est affiché dans la liste des modèles, tout visiteur pourra le remplir. Si vous souhaitez proposer votre formulaire comme modèle mais sans permettre à chacun de pouvoir le remplir, voici <a href="/docs/creer-un-modele">la procédure à suivre</a>.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_template',
    'label' => 'Lister comme modèle',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-form1-field_form1_template_desc'.
  $field_instances['node-form1-field_form1_template_desc'] = array(
    'bundle' => 'form1',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Saisissez ici une description pour votre modèle de formulaire (par exemple "Formulaire d\'enregistrement pour un événement".',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'token' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_form1_template_desc',
    'label' => 'Description du modèle',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          'ds_code' => 'ds_code',
          'filtered_html' => 'filtered_html',
          'full_html' => 'full_html',
          'php_code' => 'php_code',
          'plain_text' => 'plain_text',
          'wysiwyg_user' => 'wysiwyg_user',
        ),
        'allowed_formats_toggle' => 0,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            'ds_code' => array(
              'weight' => 12,
            ),
            'filtered_html' => array(
              'weight' => 0,
            ),
            'full_html' => array(
              'weight' => 1,
            ),
            'php_code' => array(
              'weight' => 11,
            ),
            'plain_text' => array(
              'weight' => 10,
            ),
            'wysiwyg_user' => array(
              'weight' => 0,
            ),
          ),
        ),
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-page-body'.
  $field_instances['node-page-body'] = array(
    'bundle' => 'page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'node-page-field_page_files'.
  $field_instances['node-page-field_page_files'] = array(
    'bundle' => 'page',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_page_files',
    'label' => 'fichier(s)',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'pages',
      'file_extensions' => 'txt pdf doc odt png jpg gif rtf xls ods ppt pptx docx xlsx odp svg mp4',
      'max_filesize' => '5 MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<p>En choisissant "Oui", l\'ensemble des résultats de votre formulaire sera accessible <strong>à tout le monde</strong>. Même si les personnes ne peuvent pas modifier les résultats, cela n\'est <strong>PAS RECOMMANDÉ</strong> car vous pouvez rendre public des informations personnelles (type : nom, prénom, email, adresses ou n° de téléphone) de personnes qui ne souhaitaient pas les rendre publiques.</p>
<p><strong>En choisissant "Oui", vous vous engagez à respecter l\'anonymat des participant⋅e⋅s et vous prenez l\'entière responsabilité des informations qui seront divulguées.</strong></p>
<p>Notez qu\'il existe une option "Utilisateurs ayant accès aux résultats" juste en dessous qui permet de donner l\'accès aux résultats (en visualisation/modification/suppression) à une liste d\'utilisateurs de Framaforms de votre choix.<p>');
  t('Accès public aux résultats');
  t('Body');
  t('Comment');
  t('Date d\'expiration');
  t('Description');
  t('Description du modèle');
  t('Décrivez l\'objectif de votre formulaire, ce texte apparaîtra en en-tête<br/>
Si vous souhaitez intégrer des images, nous vous conseillons d\'utiliser un service d\'hébergement externe, comme <a href="https://framapic.org" target="_blank">https://framapic.org</a> par exemple.');
  t('Fichiers attachés');
  t('Image');
  t('Image d\'illustration optionnelle');
  t('Image optionnelle qui sera affichée en haut de votre formulaire (logo ou bandeau d\'illustration, par exemple).<br/>
Après l\'avoir choisie en cliquant sur "Parcourir", n\'oubliez pas de cliquer sur "Transférer" pour qu\'elle soit transférée sur Framaforms.');
  t('Les Framaforms deviennent inaccessibles au bout de 6 mois, et sont détruits au début du 8e mois (ce qui couvre 90% des usages, et nous évite de surcharger notre base de données).

A la date indiquée, votre formulaire ci-dessus ne sera plus accessible publiquement.
Cependant, pendant encore 60 jours, vous et vous seul pourrez y accéder - ainsi qu\'aux résultats - depuis votre compte. Pour le prolonger à nouveau de 6 mois, il vous suffit de le mettre à jour en l\'éditant et en modifiant la date d\'expiration.<br/>
Si ce fonctionnement ne vous convient pas ou que vous souhaitez avoir plus d\'informations, merci de lire la page <a href="/limitations">limitations</a>.');
  t('Lister comme modèle');
  t('Saisissez ici une description pour votre modèle de formulaire (par exemple "Formulaire d\'enregistrement pour un événement".');
  t('Saisissez une liste de mots séparés par des virgules pour décrire votre contenu.');
  t('Si vous cochez cette case, votre formulaire sera affiché parmi la <a href="/templates">liste publique des modèles</a>, autorisant n\'importe qui à le dupliquer et à l\'utiliser comme modèle de formulaire (par exemple pour en faire une adaptation).
<strong>Attention : s\'il est affiché dans la liste des modèles, tout visiteur pourra le remplir. Si vous souhaitez proposer votre formulaire comme modèle mais sans permettre à chacun de pouvoir le remplir, voici <a href="/docs/creer-un-modele">la procédure à suivre</a>.');
  t('Tags');
  t('Transférer une image pour accompagner cet article.');
  t('Utilisateurs ayant accès aux résultats');
  t('Vous pouvez autoriser d\'autres utilisateurs Framaforms à accéder aux <u>résultats du formulaire</u> : cela implique qu\'ils aient déjà créé leur compte Framaforms.<br>
Pour cela, ajoutez dans le champs ci dessus le « nom d\'utilisateur Framaforms » des personnes concernées (séparés par une virgule s\'il vous autorisez plusieurs comptes).<br>
Une fois connectées à leur compte, ces personnes pourront alors accéder aux résultats en se rendant sur la page du formulaire, puis en cliquant sur l\'onglet Résultats. Elles auront aussi l\'autorisation d\'éditer et de supprimer ces résultats. <strong>En revanche, elles n\'auront PAS la possibilité de modifier le formulaire lui-même</strong> (ajout / suppression de champ, modification du titre, etc).<br>
Pour plus d\'informations, voir <a href=https://docs.framasoft.org/fr/framaforms/fonctionnalites.html#partage-des-r%C3%A9sultats>notre documentation</a>');
  t('Vous pouvez joindre jusqu\'à 5 fichiers à votre formulaire.');
  t('fichier(s)');

  return $field_instances;
}
