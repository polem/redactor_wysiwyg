<?php

/**
 * @image
 * Redactor image manager's hooks for api reference.
 */

/**
 * Alter default allowed images extensions
 * @see hook_TYPE_alter()
 */
function hook_redactor_imagemanager_allowed_images_extensions_alter(&$extensions) {
    $extensions[] = 'svg';
}


