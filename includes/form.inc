<?php

/**
 * @file
 * Form functions to support theming in the Toland theme.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_alter().
 */
function toland_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // For toland_theme_suggestions_input_alter.
  // Alter the search form.
  if ($form["#id"] === "views-exposed-form-search-api-search-page") {
    // Theme hook for the search submit button.
    $form["actions"]["submit"]['#attributes']['data-twig-suggestion'] = 'header_search_submit';
    // Add the placeholder.
    $form["search"]["#attributes"]['placeholder'] = t('Search...');
    // Add a class.
    $form['#attributes']['class'][] = 'search-header';
  }

  // Alter the faux search form.
  if ($form["#id"] === "views-exposed-form-search-api-faux-search-page") {
    // Covert the form action to the real search page.
    $form["#action"] = '/search-results';
    // Add the placeholder.
    $form["search"]["#attributes"]['placeholder'] = t('Search...');
    // Add a form class.
    $form['#attributes']['class'][] = 'search-results';
  }

  // Alter the news media filters.
  if ($form["#id"] === 'views-exposed-form-news-media-latest-news-filters-block') {
    $form["#attributes"]["class"][] = 'news-media-filter';
    $form["article_type_id"]["#options"]["All"] = t('All');
  }

  // Alter the profile teaser view.
  if ($form["#id"] === 'views-exposed-form-profile-profile-block') {
    $form["field_person_type_target_id"]["#options"]["All"] = t('All');
  }
}

/**
 * Implements hook_theme_suggestions_input_alter().
 */
function toland_theme_suggestions_input_alter(&$suggestions, array $vars) {
  // Define the element.
  $element = $vars['element'];
  // Check for specific hooks.
  if ((isset($element['#attributes']['data-twig-suggestion']) && ($element['#attributes']['data-twig-suggestion'] === 'header_search_submit'))) {
    // Create a theme hook if there is a
    // data-twig-suggestion for header_search_submit.
    // From diabetes_form_alter.
    $suggestions[] = 'input__header_search_submit';
  }
}
