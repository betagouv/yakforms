<?php

/**
 * @file
 * framaforms_feature.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function framaforms_feature_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: traducteur.
  $roles['traducteur'] = array(
    'name' => 'traducteur',
    'weight' => 3,
  );

  return $roles;
}
