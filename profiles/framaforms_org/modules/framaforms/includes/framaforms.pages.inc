<?php

/**
 * Contains Framaforms custom function related to pages
 */

/**
 *  Create nodes of type "page", based on a title and an HTML template name.
 * The page should be placed under includes/html/ and only contain the necessary HTML
 * content (not a complete HTML document).
 *
 * @param string $page_title : name of the page to use.
 * @param string $file_name : name of the HTML template to use for content.
 * @return void
 */
function create_custom_page ($page_title, $file_name){
    global $user;
    // check if the node already exists, based on node title
    $query = db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('type', 'page')
        ->condition('title', $page_title)
        ->execute()
        ->fetchAssoc();
    if($query){
        watchdog('framaforms', 'returning from query in create_custom_page()');
        return -1;
    }
    $custom_node = new stdClass();
    $custom_node->type = 'page';
    $custom_node->title = t($page_title);
    node_object_prepare($custom_node);
    // HTML template to use for the content
    $file_path = drupal_get_path('module', 'framaforms'). '/includes/html/' . $file_name;

    $custom_node->uid = $user->uid;
    $custom_node->name = $user->name;
    $custom_node->language = 'fr';
    $custom_node->comment = 0;
    $custom_node->status = 1;       //status = published
    $custom_node->revision = 0;
    $custom_node->changed =  $_SERVER['REQUEST_TIME'];
    $custom_node->created =  $_SERVER['REQUEST_TIME'];
    $custom_node->path['pathauto'] = 0; // enable pathauto

    $custom_node->body = array(
        'und' => array(
            0 => array(
                'value' => file_get_contents($file_path),
                'safe_value' => file_get_contents($file_path),
                'format' => 'full_html'
            )
        )
    );

    try{
        node_submit($custom_node);
        node_save($custom_node);
    }
    catch(Exception $e){
        watchdog('framaforms', 'Error creating custom page' .$title . ' : '. $e);
        return -1;
    }

    // register alias for the page
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
function create_all_pages (){
    // Create custom Framaforms pages
    $frontpage_nid = create_custom_page('Bienvenue sur Framaforms', 'frontpage.html');
    // if a new frontpage was created from the default Framaforms template, set it as the site frontpage.
    if($frontpage_nid != -1){
        variable_set('site_frontpage', 'node/'.$frontpage_nid);
    }
    $forbidden_nid = create_custom_page('Accès refusé','403.html');
    if($forbidden_nid != -1){
        variable_set('site_403', 'node/'.$forbidden_nid);
    }
    $notfound_nid = create_custom_page('Page not found / Page introuvable','404.html');
    if($notfound_nid != -1){
        variable_set('site_404', 'node/'.$notfound_nid);
    }

    create_custom_page('Partager','share_feature.html');
    create_custom_page('Fonctionnalités','base_features.html');
    create_custom_page('Création rapide de formulaires','quick_creation_feature.html');
    create_custom_page('Créer un modèle','model_feature.html');
    create_custom_page('Règles de validation','validation_rule_feature.html');
    create_custom_page('Champs conditionnels','conditionnal_fields_feature.html');
    create_custom_page('Courriels','mail_feature.html');
    create_custom_page('Confirmation','confirmation_feature.html');
    create_custom_page('Téléchargement','download_feature.html');
    create_custom_page('Limitations','limits.html');

    // return to frontpage
    drupal_goto('/');
    drupal_set_message(t("Les pages par défaut ont bien été crées. Rendez-vous sur <a href='/admin/content'>ce menu</a> pour les visualiser."), 'stat   us');
    return;
}

/**
 * Content callback for the expiration page :
 * returns a page indacting the form was expired and giving instruction
 * on how to change its expiration date.
 *
 * @return void
 */
function get_expiration_content () {
    global $user;
    $content = variable_get('framaforms_expiration_page_content');
    if(isset($_GET['from'])){
        $content .= "<p>" . t("Vous pouvez éditer le formulaire en vous rendant directement sur ce lien : ");
        $content .= "<a href='". $_GET['from'] . "/edit'> Vers le formulaire </a> </p>";
    }
    $placeholders = ['[my_forms_url]'];
    $replacers = ['/user/'.$user->uid.'/forms'];
    $content = str_replace($placeholders, $replacers, $content);
    return $content;
}

/**
 * Content callback for the 'share' page.
 * Originally written by pyg.
 *
 * @return void
 */
function get_share_content () {
    // this is very explicit cause it can vary from configuration
    //determination of http or https protocol
    if (isset($_SERVER['HTTPS']) && ($_SERVER['HTTPS'] == 'on' || $_SERVER['HTTPS'] == 1) ||isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https') {
        $protocol = 'https://';
    }
    else {
        $protocol = 'http://';
    }

    //build full URL
    $thisUrl = $protocol.$_SERVER['HTTP_HOST'].dirname($_SERVER['REQUEST_URI']);

    //get full path
    $fullPath= $_SERVER['REQUEST_URI'];

    //get interesting part of alias
    $paths = explode('/', $fullPath);
    $alias = $paths[1];

    $realpath = drupal_lookup_path("source", $alias);

    $realpaths = explode('/', $realpath);
    $thisNid= $realpaths[1];

    $thisCloneLink = $protocol.$_SERVER['HTTP_HOST']."/node/".$thisNid."/clone/confirm";

    $thisLink = '&lt;a href=&quot;'. $thisUrl .'&quot;&gt;Formulaire&lt;/a&gt;';
    $thisIframe400 = '&lt;iframe src=&quot;'. $thisUrl .'&quot; width=&quot;100%&quot; height=&quot;400&quot; border=&quot;0&quot; &gt;&lt;/iframe&gt;';
    $thisIframe800 = '&lt;iframe src=&quot;'. $thisUrl .'&quot; width=&quot;100%&quot; height=&quot;800&quot; border=&quot;0&quot; &gt;&lt;/iframe&gt;';

    $file_path = $base_url . drupal_get_path('module', 'framaforms'). '/includes/html/share_page.html';
    $content = file_get_contents($file_path);
    $placeholders = ['[thislink]', '[thisurl]', '[thisclonelink]' ,'[thisiframe800]'];
    $replacers = [$thisLink, $thisUrl, $thisCloneLink, $thisIframe800];
    $content = str_replace($placeholders, $replacers, $content);

    return $content;
}