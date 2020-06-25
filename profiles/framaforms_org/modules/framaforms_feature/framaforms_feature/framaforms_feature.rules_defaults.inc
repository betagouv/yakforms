<?php

/**
 * @file
 * framaforms_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function framaforms_feature_default_rules_configuration() {
  $items = array();
  $items['rules_check_url'] = entity_import('rules_config', '{ "rules_check_url" : {
      "LABEL" : "Disallow node\\/* access",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "AND" : [
            { "text_matches" : {
                "text" : [ "site:current-page:url" ],
                "match" : "node\\/\\\\d+(\\/?)$",
                "operation" : "regex"
              }
            },
            { "NOT user_has_role" : {
                "account" : [ "site:current-user" ],
                "roles" : { "value" : { "3" : "3" } }
              }
            }
          ]
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Sorry, URLs like [site:current-page:url] are not allowed around here ...",
            "type" : "error"
          }
        },
        { "redirect" : { "url" : "no_access" } }
      ]
    }
  }');
  $items['rules_clean_after_clone'] = entity_import('rules_config', '{ "rules_clean_after_clone" : {
      "LABEL" : "Clean_after_clone",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-8",
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "node_insert--form1" : { "bundle" : "form1" } },
      "DO" : [
        { "php_eval" : { "code" : "#DELETE FROM \\u0022webform_emails\\u0022 WHERE \\u0022nid\\u0022 = \\u002753763\\u0027;\\r\\nif (is_numeric($node-\\u003Enid)) {\\r\\n  db_delete(\\u0027webform_emails\\u0027)-\\u003Econdition(\\u0027nid\\u0027, $node-\\u003Enid)-\\u003Eexecute();\\r\\n}" } }
      ]
    }
  }');
  $items['rules_disallow_user_forms_access'] = entity_import('rules_config', '{ "rules_disallow_user_forms_access" : {
      "LABEL" : "Disallow user\\/%\\/forms access",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "DO" : [
        { "drupal_message" : {
            "message" : "Sorry, URLs like [site:current-page:url] are not allowed around here ...",
            "type" : "error"
          }
        },
        { "redirect" : { "url" : "no_access" } }
      ]
    }
  }');
  $items['rules_disallow_user_forms_access2'] = entity_import('rules_config', '{ "rules_disallow_user_forms_access2" : {
      "LABEL" : "Disallow user\\/*\\/forms access",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "OR" : [
            { "text_matches" : {
                "text" : [ "site:current-page:url" ],
                "match" : "user\\/\\\\d{1,9}\\/forms",
                "operation" : "regex"
              }
            },
            { "text_matches" : {
                "text" : [ "site:current-page:path" ],
                "match" : "users\\/.{1,30}\\/forms",
                "operation" : "regex"
              }
            }
          ]
        },
        { "NOT text_matches" : {
            "text" : [ "site:current-page:url" ],
            "match" : [ "site:current-user:uid" ]
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "D\\u00e9sol\\u00e9, vous n\\u0027avez pas les droits n\\u00e9cessaires pour acc\\u00e9der \\u00e0 l\\u0027adresse [site:current-page:url] \\u003Cbr\\/\\u003E\\r\\nIl n\\u0027est pas autoris\\u00e9 de voir les listes des formulaires des autres utilisateurs.",
            "type" : "error"
          }
        },
        { "redirect" : { "url" : "no_access" } }
      ]
    }
  }');
  $items['rules_disallow_user_s_access'] = entity_import('rules_config', '{ "rules_disallow_user_s_access" : {
      "LABEL" : "Disallow user(s)\\/* access",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "text_matches" : {
            "text" : [ "site:current-page:url" ],
            "match" : "user\\/\\\\d+(\\/?)\\/forms$",
            "operation" : "regex"
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Sorry, URLs like [site:current-page:url] are not allowed around here ...",
            "type" : "error"
          }
        },
        { "redirect" : { "url" : "no_access" } }
      ]
    }
  }');
  $items['rules_expiration_form1_expired'] = entity_import('rules_config', '{ "rules_expiration_form1_expired" : {
      "LABEL" : "expiration_form1_expired",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "expiration_form1" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--form1" : { "bundle" : "form1" } },
      "IF" : [
        { "data_is" : {
            "data" : [ "site:current-date" ],
            "op" : "\\u003E",
            "value" : [ "node:field-form1-expiration" ]
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Contenu expir\\u00e9 (date d\\u0027expiration : [node:field-form1-expiration] ).\\r\\nPour comprendre pourquoi, allez voir la page \\u003Ca href=\\u0022limitations\\u0022\\u003ELimitations\\u003C\\/a\\u003E.\\r\\n",
            "type" : "warning"
          }
        },
        { "node_unpublish" : { "node" : [ "node" ] } }
      ]
    }
  }');
  $items['rules_expiration_form1_inprogress'] = entity_import('rules_config', '{ "rules_expiration_form1_inprogress" : {
      "LABEL" : "expiration_form1_inprogress",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "expiration_form1" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--form1" : { "bundle" : "form1" } },
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "site:current-user:uid" ], "value" : [ "node:author:uid" ] } },
            { "data_is" : {
                "data" : [ "site:current-date" ],
                "op" : "\\u003E",
                "value" : {
                  "select" : "node:field-form1-expiration",
                  "date_offset" : { "value" : -1123200 }
                }
              }
            }
          ]
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Ce formulaire va bient\\u00f4t expirer ! [node:field-form1-expiration] ).\\r\\nPour comprendre pourquoi, allez voir la page \\u003Ca href=\\u0022limitations\\u0022\\u003ELimitations\\u003C\\/a\\u003E.\\u003Cbr\\/\\u003E\\u003Csmall\\u003ECe message n\\u0027est pas affich\\u00e9 aux participants, uniquement au cr\\u00e9ateur du questionnaire.\\u003C\\/small\\u003E\\r\\n",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  $items['rules_form1_is_to_republish'] = entity_import('rules_config', '{ "rules_form1_is_to_republish" : {
      "LABEL" : "form1_is_to_republish",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-6",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--form1" : { "bundle" : "form1" } },
      "IF" : [
        { "NOT node_is_published" : { "node" : [ "node" ] } },
        { "data_is" : {
            "data" : [ "node:field-form1-expiration" ],
            "op" : "\\u003E",
            "value" : [ "site:current-date" ]
          }
        }
      ],
      "DO" : [
        { "redirect" : { "url" : "[node:url]?info=republished" } },
        { "node_publish" : { "node" : [ "node" ] } }
      ]
    }
  }');
  $items['rules_form1_is_unpublished'] = entity_import('rules_config', '{ "rules_form1_is_unpublished" : {
      "LABEL" : "form1_is_unpublished",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-5",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--form1" : { "bundle" : "form1" } },
      "IF" : [ { "NOT node_is_published" : { "node" : [ "node" ] } } ],
      "DO" : [ { "redirect" : { "url" : "expiration?from=[node:url]" } } ]
    }
  }');
  $items['rules_prevent_delete_results'] = entity_import('rules_config', '{ "rules_prevent_delete_results" : {
      "LABEL" : "prevent delete results",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "text_matches" : {
            "text" : [ "site:current-page:url" ],
            "match" : "node\\/\\\\d{0,20}\\/submission\\/\\\\d{0,20}\\/delete$",
            "operation" : "regex"
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Vous ne pouvez pas supprimer une participation d\\u0027un formulaire dont vous n\\u0027\\u00eates pas l\\u0027auteur.",
            "type" : "error"
          }
        }
      ]
    }
  }');
  $items['rules_restrict_access_to_users_forms_list'] = entity_import('rules_config', '{ "rules_restrict_access_to_users_forms_list" : {
      "LABEL" : "restrict_access_to_users_forms_list",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "AND" : [
            { "text_matches" : {
                "text" : [ "site:current-page:path" ],
                "match" : "user\\/\\\\d{1,9}\\/forms(\\\\?.*)",
                "operation" : "regex"
              }
            },
            { "NOT text_matches" : {
                "text" : [ "site:current-page:url" ],
                "match" : [ "site:current-user:uid" ]
              }
            },
            { "NOT user_has_role" : {
                "account" : [ "site:current-user" ],
                "roles" : { "value" : { "3" : "3" } }
              }
            }
          ]
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Il n\\u0027est pas autoris\\u00e9 de voir les listes des formulaires des autres utilisateurs.",
            "type" : "warning"
          }
        },
        { "redirect" : { "url" : "no_access" } }
      ]
    }
  }');
  return $items;
}
