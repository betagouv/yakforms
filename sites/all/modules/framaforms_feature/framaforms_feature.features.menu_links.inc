<?php

/**
 * @file
 * framaforms_feature.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function framaforms_feature_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: devel_clear-cache:devel/cache/clear.
  $menu_links['devel_clear-cache:devel/cache/clear'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/cache/clear',
    'router_path' => 'devel/cache/clear',
    'link_title' => 'Clear cache',
    'options' => array(
      'attributes' => array(
        'title' => 'Clear the CSS cache and all database cache tables which store page, node, theme and variable caches.',
      ),
      'alter' => TRUE,
      'identifier' => 'devel_clear-cache:devel/cache/clear',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_devel-settings:devel/settings.
  $menu_links['devel_devel-settings:devel/settings'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/settings',
    'router_path' => 'devel/settings',
    'link_title' => 'Devel settings',
    'options' => array(
      'attributes' => array(
        'title' => 'Helper functions, pages, and blocks to assist Drupal developers. The devel blocks can be managed via the <a href="/admin/structure/block">block administration</a> page.',
      ),
      'identifier' => 'devel_devel-settings:devel/settings',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_entity-info:devel/entity/info.
  $menu_links['devel_entity-info:devel/entity/info'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/entity/info',
    'router_path' => 'devel/entity/info',
    'link_title' => 'Entity info',
    'options' => array(
      'attributes' => array(
        'title' => 'View entity information across the whole site.',
      ),
      'identifier' => 'devel_entity-info:devel/entity/info',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_execute-php-code:devel/php.
  $menu_links['devel_execute-php-code:devel/php'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/php',
    'router_path' => 'devel/php',
    'link_title' => 'Execute PHP Code',
    'options' => array(
      'attributes' => array(
        'title' => 'Execute some PHP code',
      ),
      'identifier' => 'devel_execute-php-code:devel/php',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_field-info:devel/field/info.
  $menu_links['devel_field-info:devel/field/info'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/field/info',
    'router_path' => 'devel/field/info',
    'link_title' => 'Field info',
    'options' => array(
      'attributes' => array(
        'title' => 'View fields information across the whole site.',
      ),
      'identifier' => 'devel_field-info:devel/field/info',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_function-reference:devel/reference.
  $menu_links['devel_function-reference:devel/reference'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/reference',
    'router_path' => 'devel/reference',
    'link_title' => 'Function reference',
    'options' => array(
      'attributes' => array(
        'title' => 'View a list of currently defined user functions with documentation links.',
      ),
      'identifier' => 'devel_function-reference:devel/reference',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_hookelements:devel/elements.
  $menu_links['devel_hookelements:devel/elements'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/elements',
    'router_path' => 'devel/elements',
    'link_title' => 'Hook_elements()',
    'options' => array(
      'attributes' => array(
        'title' => 'View the active form/render elements for this site.',
      ),
      'identifier' => 'devel_hookelements:devel/elements',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_menu-item:devel/menu/item.
  $menu_links['devel_menu-item:devel/menu/item'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/menu/item',
    'router_path' => 'devel/menu/item',
    'link_title' => 'Menu item',
    'options' => array(
      'attributes' => array(
        'title' => 'Details about a given menu item.',
      ),
      'alter' => TRUE,
      'identifier' => 'devel_menu-item:devel/menu/item',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_phpinfo:devel/phpinfo.
  $menu_links['devel_phpinfo:devel/phpinfo'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/phpinfo',
    'router_path' => 'devel/phpinfo',
    'link_title' => 'PHPinfo()',
    'options' => array(
      'attributes' => array(
        'title' => 'View your server\'s PHP configuration',
      ),
      'identifier' => 'devel_phpinfo:devel/phpinfo',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_rebuild-menus:devel/menu/reset.
  $menu_links['devel_rebuild-menus:devel/menu/reset'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/menu/reset',
    'router_path' => 'devel/menu/reset',
    'link_title' => 'Rebuild menus',
    'options' => array(
      'attributes' => array(
        'title' => 'Rebuild menu based on hook_menu() and revert any custom changes. All menu items return to their default settings.',
      ),
      'alter' => TRUE,
      'identifier' => 'devel_rebuild-menus:devel/menu/reset',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_reinstall-modules:devel/reinstall.
  $menu_links['devel_reinstall-modules:devel/reinstall'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/reinstall',
    'router_path' => 'devel/reinstall',
    'link_title' => 'Reinstall modules',
    'options' => array(
      'attributes' => array(
        'title' => 'Run hook_uninstall() and then hook_install() for a given module.',
      ),
      'alter' => TRUE,
      'identifier' => 'devel_reinstall-modules:devel/reinstall',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_run-cron:devel/run-cron.
  $menu_links['devel_run-cron:devel/run-cron'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/run-cron',
    'router_path' => 'devel/run-cron',
    'link_title' => 'Run cron',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'devel_run-cron:devel/run-cron',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_session-viewer:devel/session.
  $menu_links['devel_session-viewer:devel/session'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/session',
    'router_path' => 'devel/session',
    'link_title' => 'Session viewer',
    'options' => array(
      'attributes' => array(
        'title' => 'List the contents of $_SESSION.',
      ),
      'identifier' => 'devel_session-viewer:devel/session',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_theme-registry:devel/theme/registry.
  $menu_links['devel_theme-registry:devel/theme/registry'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/theme/registry',
    'router_path' => 'devel/theme/registry',
    'link_title' => 'Theme registry',
    'options' => array(
      'attributes' => array(
        'title' => 'View a list of available theme functions across the whole site.',
      ),
      'identifier' => 'devel_theme-registry:devel/theme/registry',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: devel_variable-editor:devel/variable.
  $menu_links['devel_variable-editor:devel/variable'] = array(
    'menu_name' => 'devel',
    'link_path' => 'devel/variable',
    'router_path' => 'devel/variable',
    'link_title' => 'Variable editor',
    'options' => array(
      'attributes' => array(
        'title' => 'Edit and delete site variables.',
      ),
      'alter' => TRUE,
      'identifier' => 'devel_variable-editor:devel/variable',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: main-menu_accueil:<front>.
  $menu_links['main-menu_accueil:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Accueil',
    'options' => array(
      'identifier' => 'main-menu_accueil:<front>',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: management_administration:admin.
  $menu_links['management_administration:admin'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin',
    'router_path' => 'admin',
    'link_title' => 'Administration',
    'options' => array(
      'identifier' => 'management_administration:admin',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 9,
    'customized' => 0,
  );
  // Exported menu link: management_blocks:admin/structure/block.
  $menu_links['management_blocks:admin/structure/block'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/block',
    'router_path' => 'admin/structure/block',
    'link_title' => 'Blocks',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure what block content appears in your site\'s sidebars and other regions.',
      ),
      'identifier' => 'management_blocks:admin/structure/block',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_structure:admin/structure',
  );
  // Exported menu link: management_comments:admin/content/comment.
  $menu_links['management_comments:admin/content/comment'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/content/comment',
    'router_path' => 'admin/content/comment',
    'link_title' => 'Comments',
    'options' => array(
      'attributes' => array(
        'title' => 'List and edit site comments and the comment approval queue.',
      ),
      'identifier' => 'management_comments:admin/content/comment',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_contenu:admin/content',
  );
  // Exported menu link: management_content:admin/content.
  $menu_links['management_content:admin/content'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'Content',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer content and comments.',
      ),
      'identifier' => 'management_content:admin/content',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
    'parent_identifier' => 'management_administration:admin',
  );
  // Exported menu link: management_dashboard:admin/dashboard.
  $menu_links['management_dashboard:admin/dashboard'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/dashboard',
    'router_path' => 'admin/dashboard',
    'link_title' => 'Dashboard',
    'options' => array(
      'identifier' => 'management_dashboard:admin/dashboard',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_administration:admin',
  );
  // Exported menu link: management_structure:admin/structure.
  $menu_links['management_structure:admin/structure'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure',
    'router_path' => 'admin/structure',
    'link_title' => 'Structure',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer blocks, content types, menus, etc.',
      ),
      'identifier' => 'management_structure:admin/structure',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -8,
    'customized' => 0,
    'parent_identifier' => 'management_administration:admin',
  );
  // Exported menu link: management_vue-densemble:admin/framaforms/dashboard.
  $menu_links['management_vue-densemble:admin/framaforms/dashboard'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/framaforms/dashboard',
    'router_path' => 'admin/framaforms/dashboard',
    'link_title' => 'Vue d\'ensemble',
    'options' => array(
      'attributes' => array(
        'title' => 'Dashboard générale contenant différentes statistiques sur Framaforms.',
      ),
      'identifier' => 'management_vue-densemble:admin/framaforms/dashboard',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -60,
    'customized' => 0,
    'parent_identifier' => 'management_administration:admin',
  );
  // Exported menu link: management_webform-reports:admin/content/webform_report.
  $menu_links['management_webform-reports:admin/content/webform_report'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/content/webform_report',
    'router_path' => 'admin/content/webform_report',
    'link_title' => 'Webform Reports',
    'options' => array(
      'attributes' => array(
        'title' => 'View and edit Webform reports.',
      ),
      'identifier' => 'management_webform-reports:admin/content/webform_report',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_contenu:admin/content',
  );
  // Exported menu link: navigation_add-content:node/add.
  $menu_links['navigation_add-content:node/add'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add content',
    'options' => array(
      'identifier' => 'navigation_add-content:node/add',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_article:node/add/article.
  $menu_links['navigation_article:node/add/article'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/article',
    'router_path' => 'node/add/article',
    'link_title' => 'Article',
    'options' => array(
      'attributes' => array(
        'title' => 'Utilisez les <em>articles</em> pour des contenus possédant une temporalité tels que des actualités, des communiqués de presse ou des billets de blog.',
      ),
      'identifier' => 'navigation_article:node/add/article',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_ajouter-du-contenu:node/add',
  );
  // Exported menu link: navigation_charts-examples:charts/examples.
  $menu_links['navigation_charts-examples:charts/examples'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'charts/examples',
    'router_path' => 'charts/examples',
    'link_title' => 'Charts examples',
    'options' => array(
      'identifier' => 'navigation_charts-examples:charts/examples',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_compose-tips:filter/tips.
  $menu_links['navigation_compose-tips:filter/tips'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'filter/tips',
    'router_path' => 'filter/tips',
    'link_title' => 'Compose tips',
    'options' => array(
      'identifier' => 'navigation_compose-tips:filter/tips',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_contact:contact.
  $menu_links['navigation_contact:contact'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'identifier' => 'navigation_contact:contact',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_expiration:expiration.
  $menu_links['navigation_expiration:expiration'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'expiration',
    'router_path' => 'expiration',
    'link_title' => 'Expiration',
    'options' => array(
      'attributes' => array(
        'title' => 'Page d\'instructions pour partager un formulaire.',
      ),
      'identifier' => 'navigation_expiration:expiration',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_formulaire:node/add/form1.
  $menu_links['navigation_formulaire:node/add/form1'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/form1',
    'router_path' => 'node/add/form1',
    'link_title' => 'Formulaire',
    'options' => array(
      'attributes' => array(
        'title' => 'Vous allez créer ou modifier un formulaire framaforms.
Commencez par remplir les champs ci-dessous, puis cliquez sur "Enregistrer".
NB : le titre est important, car il sera partiellement repris dans le titre. ',
      ),
      'identifier' => 'navigation_formulaire:node/add/form1',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_ajouter-du-contenu:node/add',
  );
  // Exported menu link: navigation_page-de-base:node/add/page.
  $menu_links['navigation_page-de-base:node/add/page'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/page',
    'router_path' => 'node/add/page',
    'link_title' => 'Page de base',
    'options' => array(
      'attributes' => array(
        'title' => 'Utilisez les <em>pages de base</em> pour votre contenu statique, tel que la page \'Qui sommes-nous\'.',
      ),
      'identifier' => 'navigation_page-de-base:node/add/page',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_ajouter-du-contenu:node/add',
  );
  // Exported menu link: navigation_partager:content/share.
  $menu_links['navigation_partager:content/share'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'content/share',
    'router_path' => 'content/share',
    'link_title' => 'Partager',
    'options' => array(
      'attributes' => array(
        'title' => 'Page de redirection lors de l\'expiration d\'un formulaire.',
      ),
      'identifier' => 'navigation_partager:content/share',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_search:search.
  $menu_links['navigation_search:search'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'search',
    'router_path' => 'search',
    'link_title' => 'Search',
    'options' => array(
      'identifier' => 'navigation_search:search',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_webform-report:node/add/webform-report.
  $menu_links['navigation_webform-report:node/add/webform-report'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/webform-report',
    'router_path' => 'node/add/webform-report',
    'link_title' => 'Webform report',
    'options' => array(
      'attributes' => array(
        'title' => 'A webform report is a dynamic page that contains user-specified data collected by the Webform module. The data can be sorted by a particular field, and fields can be included/excluded as needed.',
      ),
      'identifier' => 'navigation_webform-report:node/add/webform-report',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'navigation_ajouter-du-contenu:node/add',
  );
  // Exported menu link: user-menu_crer-un-formulaire:node/add/form1.
  $menu_links['user-menu_crer-un-formulaire:node/add/form1'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/form1',
    'router_path' => 'node/add',
    'link_title' => 'Créer un formulaire',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_crer-un-formulaire:node/add/form1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: user-menu_log-out:user/logout.
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 0,
  );
  // Exported menu link: user-menu_user-account:user.
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Accueil');
  t('Add content');
  t('Administration');
  t('Article');
  t('Blocks');
  t('Charts examples');
  t('Clear cache');
  t('Comments');
  t('Compose tips');
  t('Contact');
  t('Content');
  t('Créer un formulaire');
  t('Dashboard');
  t('Devel settings');
  t('Entity info');
  t('Execute PHP Code');
  t('Expiration');
  t('Field info');
  t('Formulaire');
  t('Function reference');
  t('Hook_elements()');
  t('Log out');
  t('Menu item');
  t('PHPinfo()');
  t('Page de base');
  t('Partager');
  t('Rebuild menus');
  t('Reinstall modules');
  t('Run cron');
  t('Search');
  t('Session viewer');
  t('Structure');
  t('Theme registry');
  t('User account');
  t('Variable editor');
  t('Vue d\'ensemble');
  t('Webform Reports');
  t('Webform report');

  return $menu_links;
}
