<?php

/**
 * @file
 * Functions to support theming in the Toland theme.
 */

use Drupal\node\NodeInterface;
use Drupal\group\Entity\GroupInterface;

/**
 * Implements hook_preprocess_HOOK() for HTML.
 */
function toland_preprocess_page(&$vars) {
  // Define the node.
  $node = \Drupal::routeMatch()->getParameter('node');
  // Load the site name out of configuration.
  $config = \Drupal::config('system.site');
  // Define the group.
  $group = \Drupal::routeMatch()->getParameter('group');
  // Define the homepage.
  $is_front_page = \Drupal::service('path.matcher')->isFrontPage();
  // Site vars.
  $vars['site_name'] = $config->get('name');
  $vars['site_slogan'] = $config->get('slogan');

  if ($node instanceof NodeInterface) {
    // Check for paragraphs.
    $field_hero = $node->hasField('field_hero');
    // Define the $paragraph field.
    if ($field_hero && $paragraph_field_items = $node->get('field_hero')->getValue()) {
      // Get storage. This is useful for loading a small number of objects.
      $paragraph_get_storage = \Drupal::entityTypeManager()
        ->getStorage('paragraph');
      // Collect paragraph field ids.
      $ids = array_column($paragraph_field_items, 'target_id');
      // Load all paragraph items.
      $paragraphs_items = $paragraph_get_storage->loadMultiple($ids);
      /** @var \Drupal\paragraphs\Entity\Paragraph $paragraph */
      // Loop through the $paragraphs_items.
      foreach ($paragraphs_items as $paragraph) {
        // $paragraph bundle name, hero.
        if ($paragraph->getType() === 'hero') {
          // Unset thew page title if there is a hero.
          unset($vars['page']['content']['toland_page_title']);
        }
      }
    }

    // Check for field_suppress_page_title and get the value.
    if ($node->hasField('field_suppress_page_title') &&
      !$node->get('field_suppress_page_title')->isEmpty()) {
      // Define the value.
      $value = $node->get('field_suppress_page_title')->getString();
      // If the boolean is checked, remove the standard page title block.
      if ($value === '1') {
        unset($vars['page']['content']['toland_page_title']);
      }
    }

    // Check for field_exclude_sidebar and get the value.
    if ($node->hasField('field_exclude_sidebar') &&
      !$node->get('field_exclude_sidebar')->isEmpty()) {
      // Define the value.
      $value = $node->get('field_exclude_sidebar')->getString();
      // If the boolean is checked, set a variable
      // for the page template.
      if ($value === '1') {
        $vars['exclude_sidebar'] = TRUE;
      }
    }

    if ($is_front_page) {
      // No breadcrumbs on homepage.
      unset($vars['page']['highlighted']['breadcrumbs']);
    }
  }

  // For groups.
  if ($group && $group instanceof GroupInterface) {
    // No breadcrumbs on group pages.
    unset($vars['page']['highlighted']['breadcrumbs']);
  }
}
