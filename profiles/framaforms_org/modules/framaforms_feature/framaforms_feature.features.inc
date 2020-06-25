<?php

/**
 * @file
 * framaforms_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function framaforms_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "captcha" && $api == "captcha") {
    return array("version" => "1");
  }
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function framaforms_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function framaforms_feature_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Utilisez les <em>articles</em> pour des contenus possédant une temporalité tels que des actualités, des communiqués de presse ou des billets de blog.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'form1' => array(
      'name' => t('Formulaire'),
      'base' => 'node_content',
      'description' => t('Vous allez créer ou modifier un formulaire framaforms.
Commencez par remplir les champs ci-dessous, puis cliquez sur "Enregistrer".
NB : le titre est important, car il sera partiellement repris dans le titre. '),
      'has_title' => '1',
      'title_label' => t('Titre du formulaire'),
      'help' => t('Vous allez créer ou modifier un formulaire framaforms.
Commencez par remplir les champs ci-dessous, puis cliquez sur "Enregistrer".
NB : le titre est important, car il sera partiellement repris dans le titre. '),
    ),
    'page' => array(
      'name' => t('Page de base'),
      'base' => 'node_content',
      'description' => t('Utilisez les <em>pages de base</em> pour votre contenu statique, tel que la page \'Qui sommes-nous\'.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
