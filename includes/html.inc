<?php

/**
 * @file
 * Functions to support theming in the UCSF dermatology theme.
 */

use Drupal\node\NodeInterface;
use Drupal\group\Entity\GroupInterface;

/**
 * Implements hook_preprocess_HOOK() for HTML.
 */
function toland_preprocess_html(&$vars) {
  // Define the route.
  $route = \Drupal::routeMatch()->getRouteName();
  // Define the node.
  $node = \Drupal::routeMatch()->getParameter('node');
  // Determine the page status, if 404 or 403, add the utility class.
  $status = \Drupal::requestStack()->getCurrentRequest()->attributes->get('exception');
  // Define the group.
  $group = \Drupal::routeMatch()->getParameter('group');
  if ($status && $status->getStatusCode() == 404 || $status && $status->getStatusCode() == 403) {
    $vars['attributes']['class'][] = 'page-utility';
  }

  // Define an array of pages that are user pages.
  $user_paths = [
    'user.login',
    'user.pass',
    'user.register',
  ];

  // If the route matches, add the utility class to the pages above.
  if (in_array($route, $user_paths)) {
    $vars['attributes']['class'][] = 'page-utility';
  }

  if ($node instanceof NodeInterface) {
    // Define the node type.
    $node_type = $node->getType();
    // Define the nid.
    $nid = $node->id();
    // Add a nid class for internal reference.
    $vars['attributes']['class'][] = 'n' . $nid;

    // Check for field_hero, add a class.
    if ($node->hasField('field_hero') &&
      !$node->get('field_hero')->isEmpty()) {
      // If hero is not empty.
      if (isset($node->get('field_hero')->target_id)) {
        $vars['attributes']['class'][] = 'page-has-hero';
      }
    }

    // Check for field_full_width, add a class.
    if ($node->hasField('field_full_width') &&
      !$node->get('field_full_width')->isEmpty()) {
      // Define the value.
      $value = $node->get('field_full_width')->getString();
      // If the boolean is checked, set a class.
      if ($value === '1') {
        $vars['attributes']['class'][] = 'page-is-fullwidth';
      }
    }

    // Array of page types that get special treatment for titles.
    $page_types = [
      'page',
      'lab_page',
    ];

    // If in the array, add classes.
    if (in_array($node_type, $page_types)) {
      $vars['attributes']['class'][] = 'is-page-type';
    }
  }

  // For groups.
  if ($group && $group instanceof GroupInterface) {
    // Define the $gid.
    $gid = $group->id();
    // Add a $gid class for internal reference.
    $vars['attributes']['class'][] = 'g' . $gid;
  }

  // Variable for browsersync.
  $browsersync_setting = theme_get_setting('browsersync');
  // Add gulp browsersync if it's set in local
  // settings and the local environment.
  if ($browsersync_setting === 1) {
    $host = \Drupal::request()->getHost();
    if ($host === 'local.dermatology.ucsf.edu') {
      $vars['gulp_browsersync'] = TRUE;
    }
  }
}
