<?php

/**
 * @file
 * Redactor file manager's hooks for api reference.
 */

/**
 * Alter default allowed files extensions
 * @see hook_TYPE_alter()
 */
function hook_redactor_filemanager_allowed_files_extensions_alter(&$extensions) {
    $extensions[] = 'xls';
}

