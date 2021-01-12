<?php

/**
 * Resend mails for a given node.
 *
 * Adapted from benkoren's work :
 *   https://www.drupal.org/project/webform/issues/1147072#comment-5862752.
 * Allows this to manually resend mails for a given node, useful if they were
 * flagged as spam for example.
 * Note that this script needs to be edited with the right nid on the first
 * line, as Drush scripts don't allow passing parameters.
 */

// Change this to the ID of the node you're wanting to resend the emails for.
$nid = 12345;
$node = node_load($nid);
if ($node == NULL) {
  exit("Bad NID : couldn't load node #$nid\n");
}

$header = theme('webform_results_submissions_header', array('node' => $node));
$pager_count = 900;
$submissions = webform_get_submissions($node->nid, $header, $pager_count);

// Only select emails of the "Confirmation email" type (eid=2)
$emails = $node->webform['emails'];
var_dump($emails);
$confirmation_emails = [];
foreach ($emails as $mail) {
  echo("Sending mail with subject : {$mail['subject']}\n");
  if ($mail['eid'] === '1') {
    $confirmation_emails[] = $mail;
  }
}

foreach ($submissions as $sid => $submission) {
  echo("Sending email for submission #$sid\n");
  webform_submission_send_mail($node, $submission, $confirmation_emails);
}
