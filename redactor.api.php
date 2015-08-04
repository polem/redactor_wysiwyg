<?php

/**
 * @file
 * Integrates redactor editors with Drupal.
 */

/**
 * hook_redactor_plugins
 *
 * @param array $editor
 */
function hook_redactor_plugins($editor) {

  return array(
    'my_plugin_id' => array(
      'name' => 'My plugin',
      'files' => array(
        'js' => array(
          $editor['library path'] . '/plugin.js',
        ),
        'css' => array(
          $editor['library path'] . '/plugin.css',
        ),
      ),
      'config' => array(
          'param1' => 'value1',
          'param2' => 'value2'
      ),
    ),
  );
}
