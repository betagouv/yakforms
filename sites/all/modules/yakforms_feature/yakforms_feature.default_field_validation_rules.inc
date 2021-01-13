<?php

/**
 * @file
 * yakforms_feature.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function yakforms_feature_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'date expiration validation';
  $rule->name = 'date_expiration_validation';
  $rule->field_name = 'field_date_sch2';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'webform';
  $rule->validator = 'field_validation_date_range2_validator';
  $rule->settings = array(
    'cycle' => 'global',
    'min' => 'now',
    'max' => '+12 month',
    'reverse' => 0,
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
    ),
    'errors' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'equals',
      'condition_value' => '',
    ),
  );
  $rule->error_message = 'La date d\'expiration ne peut pas excéder 12 mois';
  $export['date_expiration_validation'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'date expiration';
  $rule->name = 'expiration_date';
  $rule->field_name = 'field_date_sch';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'webform';
  $rule->validator = 'field_validation_date_range2_validator';
  $rule->settings = array(
    'cycle' => 'global',
    'min' => 'now',
    'max' => '+12 month',
    'reverse' => 0,
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
    ),
    'errors' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'equals',
      'condition_value' => '',
    ),
  );
  $rule->error_message = 'La date d\'expiration ne peut pas excéder 12 mois';
  $export['expiration_date'] = $rule;

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Date d\'expiration';
  $rule->name = 'form1_expiration_date';
  $rule->field_name = 'field_form1_expiration';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'form1';
  $rule->validator = 'field_validation_date_range2_validator';
  $rule->settings = array(
    'cycle' => 'global',
    'min' => '',
    'max' => '+6 month',
    'reverse' => 0,
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
    ),
    'errors' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'equals',
      'condition_value' => '',
    ),
  );
  $rule->error_message = 'La date d\'expiration ne peut pas excéder 6 mois suivant votre dernière mise à jour du formulaire.';
  $export['form1_expiration_date'] = $rule;

  return $export;
}
