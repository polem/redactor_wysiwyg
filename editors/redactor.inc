<?php


function redactor_wysiwyg_redactor_editor() {

  $editor['redactor'] = array(
    'title' => 'Redactor',
    'vendor url' => 'http://imperavi.com/redactor',
    'download url' => 'http://imperavi.com/redactor/download',
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
    'version callback' => 'redactor_wysiwyg_redactor_version',
    'themes callback' => 'redactor_wysiwyg_redactor_themes',
    'init callback' => 'redactor_wysiwyg_redactor_init',
    'load callback' => 'redactor_wysiwyg_redactor_load',
    'settings callback' => 'redactor_wysiwyg_redactor_settings',
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

function redactor_wysiwyg_redactor_version($editor) {
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

function redactor_wysiwyg_redactor_load($editor, $library) {
  global $language ;
  $lang_name = $language->language;

  drupal_add_css($editor['library path'] . '/redactor.css');

  if($lang_name != 'en') {
    drupal_add_js($editor['library path'] . '/langs/' . $lang_name . '.js');
  }
}

function redactor_wysiwyg_redactor_init() {
}

function redactor_wysiwyg_redactor_themes($editor, $profile) {
  return array('simple', 'redactor');
}

function redactor_wysiwyg_redactor_settings($editor, $config, $theme) {
  global $language ;
  $lang_name = $language->language;

  $settings = array(
    'lang' => $lang_name,
  );
  return $settings;
}

