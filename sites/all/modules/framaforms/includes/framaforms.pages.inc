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
 * Content callback for the expiration page :
 * returns a page indacting the form was expired and giving instruction
 * on how to change its expiration date.
 *
 * @return void
 */
function get_expiration_content() {
  global $user;
  $content = variable_get('framaforms_expiration_page_content');
  if (isset($_GET['from'])) {
    $content .= "<p>" . t("You can edit this form by going to this link : ");
    $content .= "<a href='" . $_GET['from'] . "/edit'>" . t("To the form") . "</a> </p>";
  }
  $placeholders = ['[my_forms_url]'];
  $replacers = ['/user/' . $user->uid . '/forms'];
  $content = str_replace($placeholders, $replacers, $content);
  return $content;
}

/**
 * Content callback for the 'share' tab.
 * Originally written by pyg for Framasoft.
 *
 * @return void
 */
function get_share_content() {
  // Get the site's default language code
  $language_code = language_default()->language;
  // This is very explicit cause it can vary from configuration
  // determination of http or https protocol.
  if (isset($_SERVER['HTTPS']) && ($_SERVER['HTTPS'] == 'on' || $_SERVER['HTTPS'] == 1) ||isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https') {
    $protocol = 'https://';
  }
  else {
    $protocol = 'http://';
  }

  // Build full URL.
  $thisUrl = $protocol . $_SERVER['HTTP_HOST'] . dirname($_SERVER['REQUEST_URI']);

  // Get full path.
  $fullPath = $_SERVER['REQUEST_URI'];

  // Get interesting part of alias.
  $paths = explode('/', $fullPath);
  $alias = $paths[1];

  $realpath = drupal_lookup_path("source", $alias);

  $realpaths = explode('/', $realpath);
  $thisNid = $realpaths[1];

  $thisCloneLink = $protocol . $_SERVER['HTTP_HOST'] . "/node/" . $thisNid . "/clone/confirm";

  $thisLink = '&lt;a href=&quot;' . $thisUrl . '&quot;&gt;Formulaire&lt;/a&gt;';
  $thisIframe400 = '&lt;iframe src=&quot;' . $thisUrl . '&quot; width=&quot;100%&quot; height=&quot;400&quot; border=&quot;0&quot; &gt;&lt;/iframe&gt;';
  $thisIframe800 = '&lt;iframe src=&quot;' . $thisUrl . '&quot; width=&quot;100%&quot; height=&quot;800&quot; border=&quot;0&quot; &gt;&lt;/iframe&gt;';

  $file_path = $base_url . drupal_get_path('module', 'framaforms') . "/includes/html/{$language_code}/share_page.html";
  $content = file_get_contents($file_path);
  $placeholders = ['[thishtmlelement]', '[thisurl]', '[thisclonelink]' , '[thisiframe800]'];
  $replacers = [$thisLink, $thisUrl, $thisCloneLink, $thisIframe800];
  $content = str_replace($placeholders, $replacers, $content);

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
