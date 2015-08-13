redactor
========

Drupal 7 redactor wysiwyg adapter

## Add a redactor plugin

You have to implement `hook_redactor_plugins` css and js files will be loaded by the module

```php
/**
 * Implements hook_redactor_plugins().
 */
function my_module_redactor_plugins($editor) {

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
      )
    ),
  );
}
```

## Alter settings in javascript.

```js
(function($) {
  'use strict';
  Drupal.behaviors.my_redactor_module = {
    attach: function(context, settings) {

      $(document).bind('redactor.attach', function(e, context, params, settings) {
        settings.linkifyCallback = function(elements) {
        };
      });
    }
  };
})(jQuery);
```

