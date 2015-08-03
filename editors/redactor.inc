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
    'load callback' => 'redactor_redactor_load',
    'settings callback' => 'redactor_redactor_settings',
    'plugin callback' => 'redactor_redactor_wysiwyg_plugins',
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
    drupal_add_js($editor['library path'] . '/langs/' . $lang_name . '.js', array(
      'scope' => 'footer'
    ));
  }
}

function redactor_redactor_load_plugin_files($editor, $config) {
  if(!isset($config['files'])) {
    return;
  }

  $default_js_options = array(
    'scope' => 'footer',
    'group' => JS_DEFAULT
  );

  $default_css_options = array(
    'scope' => 'footer',
    'group' => JS_DEFAULT
  );

  if(isset($config['files']['js'])) {
    foreach($config['files']['js'] as $data => $options) {
      if(!is_string($data)) {
        $data = $options;
        $options = array();
      }
      $options = array_merge($default_js_options, $options);
      drupal_add_js($data, $options);
    }
  }

  if(isset($config['files']['css'])) {
    foreach($config['files']['css'] as $data => $options) {
      if(!is_string($data)) {
        $data = $options;
        $options = array();
      }
      drupal_add_css($data, $options);
    }
  }
}

function redactor_redactor_themes($editor, $profile) {
  return array('simple', 'redactor');
}

function redactor_redactor_settings($editor, $config, $theme) {

  $settings = array(
    'plugins' => array()
  );

  if (!empty($config['plugins'])) {
    foreach ($config['plugins'] as $plugin => $enabled_plugins) {
      foreach($enabled_plugins as $enabled_plugin => $plugin_name) {
        $plugin_config = redactor_get_plugin($enabled_plugin);
        redactor_redactor_load_plugin_files($editor, $plugin_config);

        // add plugins to enabled plugins
        $settings['plugins'][] = $enabled_plugin;
      }
    }
  }

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


/**
 * Load enabled redactor plugins (wysiwyg extensions)
 */
function redactor_load_readactor_enabled_plugins($editor, $config) {
  // get enabled extensions
  foreach ($plugins as $name => $plugin) {
    $settings['plugins'][] = $name;
    if (!empty($plugin['files'])) {
      if (!empty($plugin['files']['js'])) {
        foreach($plugin['files']['js'] as $filename) {
          drupal_add_js($editor['library path'] . '/plugins/' . $filename);
        }
      }
    }
  }
}

function redactor_redactor_wysiwyg_plugins($editor) {
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

