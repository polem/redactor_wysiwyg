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

## Editor settings

You can activate or disable plugins in wysiwyg profiles

![plugins settings](http://i59.tinypic.com/2qu2g0p.png)

## File manager

to enable filemanager `drush en redactor_filemanager`

you can now edit file manager settings in wysiwyg profiles

![File manager settings](http://i57.tinypic.com/snibrt.png)

## Image manager

to enable imagemanager `drush en redactor_imagemanager`

you can now edit image manager settings in wysiwyg profiles

![Image manager settings](http://i62.tinypic.com/250nz1u.png)

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

