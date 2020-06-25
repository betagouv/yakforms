<?php

/**
 * @file
 * framaforms_feature.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function framaforms_feature_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard';
  $page->task = 'page';
  $page->admin_title = 'Total Control administrative dashboard';
  $page->admin_description = '';
  $page->path = 'admin/dashboard';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'have total control',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Dashboard',
    'name' => 'management',
    'weight' => '-100',
    'parent' => array(
      'type' => 'normal',
      'title' => 'Dashboard',
      'name' => 'management',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => TRUE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Admin Dashboard',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Dashboard';
  $display->uuid = 'f43b424f-a7b1-405c-be4d-c768cb83c23a';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_dashboard_panel_context';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-b209a3f1-2df2-4149-8caf-c9c31967419a';
  $pane->panel = 'left';
  $pane->type = 'create';
  $pane->subtype = 'create';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'project' => 'project',
      'page' => 0,
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = 'b209a3f1-2df2-4149-8caf-c9c31967419a';
  $display->content['new-b209a3f1-2df2-4149-8caf-c9c31967419a'] = $pane;
  $display->panels['left'][0] = 'new-b209a3f1-2df2-4149-8caf-c9c31967419a';
  $pane = new stdClass();
  $pane->pid = 'new-41db574c-195c-4c9b-866b-11c1f83c5fe2';
  $pane->panel = 'left';
  $pane->type = 'overview_content';
  $pane->subtype = 'overview_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'page' => 'page',
      'project' => 'project',
      'video' => 'video',
    ),
    'comments' => array(
      'article' => 'article',
      'page' => 0,
      'project' => 0,
      'video' => 0,
    ),
    'spam' => 0,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = '';
  $pane->uuid = '41db574c-195c-4c9b-866b-11c1f83c5fe2';
  $display->content['new-41db574c-195c-4c9b-866b-11c1f83c5fe2'] = $pane;
  $display->panels['left'][1] = 'new-41db574c-195c-4c9b-866b-11c1f83c5fe2';
  $pane = new stdClass();
  $pane->pid = 'new-46258c06-884a-49e6-85d1-ae13d08acaee';
  $pane->panel = 'left';
  $pane->type = 'views_panes';
  $pane->subtype = 'control_users_panes-pane_tc_new_users';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'items_per_page' => '10',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '46258c06-884a-49e6-85d1-ae13d08acaee';
  $display->content['new-46258c06-884a-49e6-85d1-ae13d08acaee'] = $pane;
  $display->panels['left'][2] = 'new-46258c06-884a-49e6-85d1-ae13d08acaee';
  $pane = new stdClass();
  $pane->pid = 'new-1d2c66d2-e39c-4ebe-831d-7db4fcfaea68';
  $pane->panel = 'left';
  $pane->type = 'views_panes';
  $pane->subtype = 'control_content_panes-pane_tc_new';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'items_per_page' => '10',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = '';
  $pane->uuid = '1d2c66d2-e39c-4ebe-831d-7db4fcfaea68';
  $display->content['new-1d2c66d2-e39c-4ebe-831d-7db4fcfaea68'] = $pane;
  $display->panels['left'][3] = 'new-1d2c66d2-e39c-4ebe-831d-7db4fcfaea68';
  $pane = new stdClass();
  $pane->pid = 'new-899484ab-1069-4780-956f-d7dd8a2a41a9';
  $pane->panel = 'right';
  $pane->type = 'menus';
  $pane->subtype = 'menus';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'item1' => NULL,
    'item2' => NULL,
    'override_title' => 0,
    'override_title_text' => '',
    'menus' => array(
      'main-menu' => 'main-menu',
      'navigation' => 'navigation',
      'devel' => 0,
      'management' => 0,
      'user-menu' => 0,
    ),
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = '899484ab-1069-4780-956f-d7dd8a2a41a9';
  $display->content['new-899484ab-1069-4780-956f-d7dd8a2a41a9'] = $pane;
  $display->panels['right'][0] = 'new-899484ab-1069-4780-956f-d7dd8a2a41a9';
  $pane = new stdClass();
  $pane->pid = 'new-d7148774-01c9-492c-8e11-23707a7906e1';
  $pane->panel = 'right';
  $pane->type = 'node_types';
  $pane->subtype = 'node_types';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'page' => 'page',
      'project' => 'project',
      'video' => 'video',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = '';
  $pane->uuid = 'd7148774-01c9-492c-8e11-23707a7906e1';
  $display->content['new-d7148774-01c9-492c-8e11-23707a7906e1'] = $pane;
  $display->panels['right'][1] = 'new-d7148774-01c9-492c-8e11-23707a7906e1';
  $pane = new stdClass();
  $pane->pid = 'new-b1001384-74d7-4bd8-8220-04ebabd8bcb7';
  $pane->panel = 'right';
  $pane->type = 'taxonomy';
  $pane->subtype = 'taxonomy';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'vids' => array(
      0 => '2',
      1 => '1',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = '';
  $pane->uuid = 'b1001384-74d7-4bd8-8220-04ebabd8bcb7';
  $display->content['new-b1001384-74d7-4bd8-8220-04ebabd8bcb7'] = $pane;
  $display->panels['right'][2] = 'new-b1001384-74d7-4bd8-8220-04ebabd8bcb7';
  $pane = new stdClass();
  $pane->pid = 'new-ac1d31e9-89bb-4697-8809-3a5240a87be4';
  $pane->panel = 'right';
  $pane->type = 'panel_pages';
  $pane->subtype = 'panel_pages';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'item1' => NULL,
    'item2' => NULL,
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = '';
  $pane->uuid = 'ac1d31e9-89bb-4697-8809-3a5240a87be4';
  $display->content['new-ac1d31e9-89bb-4697-8809-3a5240a87be4'] = $pane;
  $display->panels['right'][3] = 'new-ac1d31e9-89bb-4697-8809-3a5240a87be4';
  $pane = new stdClass();
  $pane->pid = 'new-a4efde88-f29e-42bd-852b-3499e2d40201';
  $pane->panel = 'top';
  $pane->type = 'welcome';
  $pane->subtype = 'welcome';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = 'a4efde88-f29e-42bd-852b-3499e2d40201';
  $display->content['new-a4efde88-f29e-42bd-852b-3499e2d40201'] = $pane;
  $display->panels['top'][0] = 'new-a4efde88-f29e-42bd-852b-3499e2d40201';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard'] = $page;

  return $pages;

}
