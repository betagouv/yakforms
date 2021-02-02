<?php

/**
 * @file
 * yakforms_feature.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function yakforms_feature_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: devel.
  $menus['devel'] = array(
    'menu_name' => 'devel',
    'title' => 'Développement',
    'description' => 'Development link',
  );
  // Exported menu: features.
  $menus['features'] = array(
    'menu_name' => 'features',
    'title' => 'Fonctionnalités',
    'description' => 'Eléments de menu pour toutes les fonctionnalités (features) activées.',
  );
  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Menu principal',
    'description' => 'Le <em>menu Principal</em> est fréquemment utilisé pour afficher les sections importantes du site, souvent dans la barre de navigation de haut de page.',
  );
  // Exported menu: management.
  $menus['management'] = array(
    'menu_name' => 'management',
    'title' => 'Management',
    'description' => 'Le menu <em>Gestion</em> contient les liens des tâches administratives',
  );
  // Exported menu: navigation.
  $menus['navigation'] = array(
    'menu_name' => 'navigation',
    'title' => 'Navigation',
    'description' => 'Le <em>menu Navigation</em> contient les liens destinés aux visiteurs du site. Des liens sont automatiquement ajoutés à ce menu par certains modules.',
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'Le menu <em>Utilisateur</em> contient les liens du compte utilisateur, comme le lien "Déconnexion"',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Development link');
  t('Développement');
  t('Eléments de menu pour toutes les fonctionnalités (features) activées.');
  t('Fonctionnalités');
  t('Le <em>menu Navigation</em> contient les liens destinés aux visiteurs du site. Des liens sont automatiquement ajoutés à ce menu par certains modules.');
  t('Le <em>menu Principal</em> est fréquemment utilisé pour afficher les sections importantes du site, souvent dans la barre de navigation de haut de page.');
  t('Le menu <em>Gestion</em> contient les liens des tâches administratives');
  t('Le menu <em>Utilisateur</em> contient les liens du compte utilisateur, comme le lien "Déconnexion"');
  t('Management');
  t('Menu principal');
  t('Navigation');
  t('User menu');

  return $menus;
}
