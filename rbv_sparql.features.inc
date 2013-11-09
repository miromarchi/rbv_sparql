<?php
/**
 * @file
 * rbv_sparql.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function rbv_sparql_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "arc2_store" && $api == "arc2_store") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function rbv_sparql_default_search_api_index() {
  $items = array();
  $items['node_rdf_index'] = entity_import('search_api_index', '{
    "name" : "Node RDF index",
    "machine_name" : "node_rdf_index",
    "description" : null,
    "server" : "rdf_indexing_server",
    "item_type" : "node",
    "options" : {
      "fields" : { "search_api_language" : { "type" : "string" } },
      "data_alter_callbacks" : {
        "rdf_indexer_alter_entity_public" : { "status" : 1, "weight" : "-50", "settings" : [] },
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-49",
          "settings" : {
            "default" : "1",
            "bundles" : {
              "collaboration" : "collaboration",
              "org" : "org",
              "project" : "project",
              "relation" : "relation"
            }
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "-48", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 0, "weight" : "-47", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "-46", "settings" : { "fields" : [] } },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "-45", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "-44", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "-43", "settings" : { "mode" : "full" } }
      },
      "processors" : {
        "search_api_case_ignore" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : [],
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : { "fields" : [], "spaces" : "[^[:alnum:]]", "ignorable" : "[\\u0027]" }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : [],
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function rbv_sparql_default_search_api_server() {
  $items = array();
  $items['rdf_indexing_server'] = entity_import('search_api_server', '{
    "name" : "RDF indexing server",
    "machine_name" : "rdf_indexing_server",
    "description" : "",
    "class" : "rdf_indexer_service",
    "options" : { "store_id" : "default" },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
