<?php

/**
 * Contains Framaforms custom function related to block contents
 */

/**
 * Returns the content for the personal contact form block.
 *
 * @param int $nid : the current page nid
 * @return string : the markup content to be rendered.
 */
function get_contact_form_content ($nid) {
    $current_path = current_path();
    $content = "";
    try{
      if(isset($nid)){
        $query_str = sprintf("SELECT users.name, users.uid FROM node INNER JOIN users ON node.uid = users.uid WHERE node.nid=%s;", $nid);
        $results = db_query($query_str)->fetchAssoc();
        $name = $results ? $results['name'] : NULL;
        $uid = $results ? $results['uid'] : NULL;

        $query_str = sprintf("SELECT users.data FROM node INNER JOIN users ON node.uid = users.uid WHERE node.nid=%s;", $nid);
        $results = db_query($query_str)->fetchAssoc();
        $contact = unserialize($results['data'])['contact'];
      }
      if($nid && isset($name) && isset($uid) && $contact == 1 ){
        $url_contact = '/' .drupal_get_path_alias('user/'.$uid) .'/contact';
        $content .= t("<h3>Contacter l'auteur du formulaire</h3>");
        $content .= sprintf("<p> Pour contacter l'auteur du formulaire, <a href='%s'> cliquez ici</a><p>", $url_contact);
        $content .= "<br>";
      }
      }
      catch(Exception $e){
        watchdog('framaforms', 'Error in contact form block' . $e);
      }
      return $content;
  }

/**
 * Returns true if the node whose NID is passed is of type form1
 *
 * @param int $nid : the NID of the node
 * @return void
 */
function node_is_form1($nid){
    $node = node_load($nid);
    if($node->type == 'form1'){
      return true;
    }
    return false;
  }