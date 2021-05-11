<?php

/**
 * @file
 * yakforms_feature.features.contact_categories.inc
 */

/**
 * Implements hook_contact_categories_defaults().
 */
function yakforms_feature_contact_categories_defaults() {
  return array(
    'Contact Framaforms' => array(
      'category' => 'Contact Framaforms',
      'recipients' => 'contact@yourdomain.org',
      'reply' => '',
      'weight' => 0,
      'selected' => 1,
    ),
  );
}
