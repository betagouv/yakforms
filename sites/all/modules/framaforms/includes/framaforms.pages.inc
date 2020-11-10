<?php

/**
 * @file
 * Contains Framaforms custom function related to pages.
 */

/**
 * Creates a custom Framaforms page from a HTML template.
 *
 * Create nodes of type "page", based on a title and an HTML template name.
 * The page should be placed under includes/html/{language_code} and only contain the necessary HTML
 * content (not a complete HTML document).
 *
 * @param String $page_title
 *   : name of the page to use.
 * @param String $file_name
 *   : name of the HTML template to use for content.
 */
function create_custom_page($page_title, $file_name){
  global $user;
  // Get default site language to define which templates to use
  $language_code = language_default()->language;
  // Check if the node already exists, based on node title.
  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'page')
    ->condition('title', $page_title)
    ->execute()
    ->fetchAssoc();
  if ($query) {
    // Early return if a page with the same title is found in the database.
    return -1;
  }
  $custom_node = new stdClass();
  $custom_node->type = 'page';
  $custom_node->title = $page_title;
  node_object_prepare($custom_node);
  // Define HTML template to use for the content based on the site's default language.
  $file_path = _get_template_file_path($language_code, $file_name);

  $custom_node->uid = $user->uid;
  $custom_node->name = $user->name;
  $custom_node->language = 'fr';
  $custom_node->comment = 0;
  // Status = published.
  $custom_node->status = 1;
  $custom_node->revision = 0;
  $custom_node->changed = $_SERVER['REQUEST_TIME'];
  $custom_node->created = $_SERVER['REQUEST_TIME'];
  // Enable pathauto.
  $custom_node->path['pathauto'] = 0;

  $custom_node->body = array(
    'und' => array(
      0 => array(
        'value' => file_get_contents($file_path),
        'safe_value' => file_get_contents($file_path),
        'format' => 'full_html',
      ),
    ),
  );

  try {
    node_submit($custom_node);
    node_save($custom_node);
  }
  catch (Exception $e) {
    watchdog('framaforms', "There was an error creating the page %title : %error", array('%title' => $title, '%error' => $e), WATCHDOG_WARNING);
    return -1;
  }

  // Register alias for the page.
  $alias = strtolower($custom_node->title);
  $chars = ['é', 'è', ' '];
  $replacers = ['e', 'e', '-'];
  $alias = str_replace($chars, $replacers, $alias);
  $path = array(
    'source' => 'node/' . $custom_node->nid,
    'alias' => $alias,
  );
  path_save($path);

  return $custom_node->nid;
}

/**
 * Menu callback for admin/framaforms/create_default_pages :
 * Creates all default pages, checking each pages doesn't exist prior
 * to creating it in order to avoid overwriting user modifications.
 *
 * @return void
 */
function create_all_pages() {
  // Create custom Framaforms pages.
  $frontpage_title = t('Welcome to Framaforms');
  $frontpage_nid = create_custom_page($frontpage_title, 'frontpage.html');
  // If a new frontpage was created from the default Framaforms template, set it as the site frontpage.
  if ($frontpage_nid != -1) {
    variable_set('site_frontpage', 'node/' . $frontpage_nid);
  }
  $forbidden_nid = create_custom_page(t('Access denied'), '403.html');
  if ($forbidden_nid != -1) {
    variable_set('site_403', 'node/' . $forbidden_nid);
  }
  $notefound_title = t("Page not found");
  $notfound_nid = create_custom_page($notefound_title, '404.html');
  if ($notfound_nid != -1) {
    variable_set('site_404', 'node/' . $notfound_nid);
  }

  create_custom_page(t("Share"), 'share_feature.html');
  create_custom_page(t("Features"), 'base_features.html');
  create_custom_page(t("Quick form creation"), 'quick_creation_feature.html');
  create_custom_page(t("Create a template"), 'model_feature.html');
  create_custom_page(t("Validation rules"), 'validation_rule_feature.html');
  create_custom_page(t('Conditional fields'), 'conditionnal_fields_feature.html');
  create_custom_page(t("Emails"), 'mail_feature.html');
  create_custom_page(t("Confirmation"), 'confirmation_feature.html');
  create_custom_page(t("Downloads"), 'download_feature.html');
  create_custom_page(t("Limits"), 'limits.html');

  // Return to frontpage.
  drupal_goto('/');
  return;
}

/**
 * Content callback for the expiration page.
 *
 *  Returns the content of the HTML template with replaced tokens.
 * @return void
 */
function get_expiration_content() {
  global $user;
  // Get the node which was redirected to the present page
  $from_url = $_REQUEST['from'];
  // Trim the base URL
  $from_url = explode('/', $from_url)[3];
  // Get the node object from this URL
  $expired_node = menu_get_object('node', 1, drupal_get_normal_path($from_url));

  // Get base page content from template
  // Get the site's default language code
  $language_code = language_default()->language;
  $file_path = _get_template_file_path($language_code, 'expiration_page.html');
  $content = file_get_contents($file_path);

  return token_replace($content, array('node' => $expired_node, 'user' => $user));
}

/**
 * Content callback for the 'share' tab.
 *
 * Returns the content of the HTML template with replaced tokens.
 * @return void
 */
function get_share_content() {
  // Get the site's default language code
  $language_code = language_default()->language;

  // Get base page content from template
  $file_path = _get_template_file_path($language_code, 'share_page.html');
  $content = file_get_contents($file_path);

  // Replace tokens within this content. They need to be passed a node object.
  $this_nid = explode('/', current_path())[1];
  $this_node = node_load($this_nid);
  $content = token_replace($content, array('node' => $this_node));
  return $content;
}

/**
 * Returns a template path based on a language code and a filename.
 *
 * If the template exists under includes/html in the desired language,
 * returns this one.
 * If not, returns the English version by default.
 *
 * @param String $language
 * @param String $filename
 * @return String the template path
 */
function _get_template_file_path($language, $filename){
  $translated_template_path = drupal_get_path('module', 'framaforms') . "/includes/html/{$language}/{$filename}";
  if(file_exists($translated_template_path)){
    return $translated_template_path;
  }
  // Fallback to English otherwise
  return drupal_get_path('module', 'framaforms') . "/includes/html/en/{$filename}";
}
