<?php


function redactor_redactor_editor() {

  $editor['redactor'] = array(
    'title' => 'Redactor',
    'vendor url' => 'http://imperavi.com/redactor',
    'download url' => 'http://imperavi.com/redactor/download',
    'library path' => wysiwyg_get_path('redactor') . '/dist',
    'libraries' => array(
      '' => array(
        'title' => 'Default',
        'files' => array(
          'redactor.js' => array('preprocess' => FALSE),
        ),
      ),
      'src' => array(
        'title' => 'Source',
        'files' => array(
          'redactor.js' => array('preprocess' => FALSE),
        ),
      ),
    ),
    'version callback' => 'redactor_redactor_version',
    'themes callback' => 'redactor_redactor_themes',
    'init callback' => 'redactor_redactor_init',
    'load callback' => 'redactor_redactor_load',
    'settings callback' => 'redactor_redactor_settings',
    'plugin callback' => 'redactor_redactor_plugins',
    'proxy plugin' => array(
      'drupal' => array(
        'load' => TRUE,
        'proxy' => TRUE,
      ),
    ),
    'versions' => array(
      '10.0.0' => array(
        'js files' => array('redactor.js'),
      ),
    )
  );
  return $editor;
}

function redactor_redactor_version($editor) {
  $library = $editor['library path'] . '/redactor.js';
  if (!file_exists($library)) {
    return;
  }
  $library = fopen($library, 'r');
  $max_lines = 8;
  while ($max_lines && $line = fgets($library, 500)) {
    if (preg_match('@Redactor v*([\d\.]+)@', $line, $version)) {
      fclose($library);
      return $version[1];
    }
    $max_lines--;
  }
  fclose($library);
}

function redactor_redactor_load($editor, $library) {
  global $language ;
  $lang_name = $language->language;

  drupal_add_css($editor['library path'] . '/redactor.css');

  if($lang_name != 'en') {
    drupal_add_js($editor['library path'] . '/langs/' . $lang_name . '.js');
  }
}

function redactor_redactor_init() {
}

function redactor_redactor_themes($editor, $profile) {
  return array('simple', 'redactor');
}

function redactor_redactor_settings($editor, $config, $theme) {
  global $language ;
  $lang_name = $language->language;

  $settings = array();

  $plugins = wysiwyg_get_plugins($editor['name']);

  if (!empty($config['buttons'])) {
    $buttons = array();
    foreach ($config['buttons'] as $plugin => $enabled_buttons) {
      foreach($enabled_buttons as $enabled_button => $button_name) {
        $buttons[] = $enabled_button;
      }
    }
    $settings['buttons'] = $buttons;
  }

  if (isset($config['language'])) {
    $settings['lang'] = $config['language'];
  }

  return $settings;
}

function redactor_redactor_plugins($editor) {
  return array(
    'default' => array(
      'buttons' => array(
        'html' => 'Html',
        'formatting' => 'Formatting',
        'bold' => 'Bold',
        'italic' => 'Italic',
        'deleted' => 'Deleted',
        'unorderedlist' => 'Unordered List',
        'orderedlist' => 'Ordered List',
        'outdent' => 'Outdent',
        'indent' => 'Indent',
        'image' => 'Image',
        'file' => 'File',
        'link' => 'Link',
        'alignment' => 'Alignment',
        'horizontalrule' => 'Horizontal Rule',
      ),
      'internal' => TRUE,
    ),
  );
}

