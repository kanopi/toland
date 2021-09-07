<?php

/**
 * @file
 * Functions to support theming in the UCSF dermatology theme.
 */

use Drupal\node\NodeInterface;

/**
 * Implements hook_preprocess_HOOK() for HTML.
 */
function toland_preprocess_node(&$vars) {
  // Define the node.
  $node = \Drupal::routeMatch()->getParameter('node');
  // If a node.
  if ($node instanceof NodeInterface) {
    // Act on the hero field.
    if ($node->hasField('field_hero') &&
      !$node->get('field_hero')->isEmpty()) {
      // Check how many items are in hero.
      $hero_items_count = count($node->get("field_hero"));
      // If more than 1, add a class.
      if ($hero_items_count > 1) {
        $vars['attributes']['class'][] = 'hero-has-linksbar';
      }
    }
  }
}

/**
 * Implements hook_theme_suggestions_HOOK().
 */
function toland_theme_suggestions_node_alter(array &$suggestions, array $vars) {
  // Define the node.
  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node instanceof NodeInterface) {
    // Define the view mode.
    $view_mode = $vars["elements"]["#view_mode"];
    // Define the node type.
    $node_type = $node->getType();
    // Array of page types that get special treatment.
    // These content types are identical so they can have the same
    // theme hook.
    $medical_page_types = [
      'surgery',
      'service',
      'condition',
    ];

    // Theme hook for this array.
    if (in_array($node_type, $medical_page_types)) {
      // Add the theme hook.
      // scm stands for services, conditions, surgery.
      if (!empty($view_mode)) {
        $suggestions[] = 'node__scs__' . $view_mode;
      }
    }
  }
}
