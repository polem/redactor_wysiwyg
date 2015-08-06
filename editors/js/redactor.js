(function($) {

Drupal.wysiwyg.editor.init.redactor = function(settings) {
  $(document).trigger('redactor.init', [settings]);
};

/**
 * Attach this editor to a target element.
 *
 * See Drupal.wysiwyg.editor.attach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.attach.redactor = function(context, params, settings) {
  $(document).trigger('redactor.attach', [context, params, settings]);
  $('#' + params.field).redactor(settings);
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.redactor = function (context, params, trigger) {
  if(trigger === 'serialize') {
    return;
  }

  $(document).trigger('redactor.detach', [context, params, settings]);
  $('#' + params.field).redactor('core.destroy');
};

Drupal.wysiwyg.editor.instance.redactor = {

};

})(jQuery);


