<?php

/**
 * @file
 * Functions to support theming in the Toland theme.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Allow themes to alter the theme-specific settings form.
 */
function toland_form_system_theme_settings_alter(&$form, FormStateInterface $form_state) {
  $form['theme']['custom'] = [
    '#type' => 'fieldset',
    '#title' => 'Custom Settings',
  ];

  // Custom setting to enable browserSync locally.
  $form['theme']['custom']['browsersync'] = [
    '#type' => 'checkbox',
    '#disabled' => TRUE,
    '#description' => t("Enable this through your local settings file, see the theme readme for more info."),
    '#title' => 'Use browserSync for local development',
    '#default_value' => theme_get_setting('browsersync', 'toland'),
  ];
}
