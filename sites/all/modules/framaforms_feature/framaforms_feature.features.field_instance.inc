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
      'example_node_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
      'example_node_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
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
      'example_node_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
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
      'example_node_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
      'example_node_list' => array(
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
