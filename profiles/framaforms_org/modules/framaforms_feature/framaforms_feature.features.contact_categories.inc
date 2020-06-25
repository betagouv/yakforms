<?php

/**
 * @file
 * framaforms_feature.features.contact_categories.inc
 */

/**
 * Implements hook_contact_categories_defaults().
 */
function framaforms_feature_contact_categories_defaults() {
  return array(
    'Contact Framaforms' => array(
      'category' => 'Contact Framaforms',
      'recipients' => 'rt+framaforms@framasoft.org',
      'reply' => '',
      'weight' => 0,
      'selected' => 1,
    ),
  );
}
