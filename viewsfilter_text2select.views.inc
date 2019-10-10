<?php

/**
 * Implements hook_views_data_alter().
 */
function viewsfilter_text2select_views_data_alter(&$data) {
  $field_info = field_info_field_map();
  foreach ($field_info as $field_name => $info) {
    if (empty($info['type']) OR $info['type'] !== 'text') {
      continue;
    }
    $data['field_data_' . $field_name][$field_name . '_value']['filter']['handler']
        = 'viewsfilter_text2select_filter';
    $data['field_revision_' . $field_name][$field_name . '_value']['filter']['handler']
        = 'viewsfilter_text2select_filter';
  }
}