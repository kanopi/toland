<?php

/**
 * @file
 * Block functions to support theming in the Toland theme.
 */

use Drupal\block\Entity\Block;

/**
 * @file
 * Block functions to support theming in the toland theme.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function toland_preprocess_block(&$vars) {
  // Pass block region value to content so this can be used in
  // toland_theme_suggestions_menu_alter.
  if (isset($vars['elements']['#id'])) {
    $block = Block::load($vars['elements']['#id']);
    if (!empty($block)) {
      $region = $block->getRegion();
      $vars['content']['#attributes']['region'] = $region;
    }
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function toland_theme_suggestions_block_alter(array &$suggestions, array $vars) {
  // Provide suggestion for block templates by custom block type.
  if (!empty($vars['elements']['content']['#block_content'])) {
    $block = $vars['elements']['content']['#block_content'];
    // Add `block--BLOCK-TYPE.html.twig`.
    $suggestions[] = 'block__' . $block->bundle();
    $view_mode = $vars['elements']['#configuration']['view_mode'];
    if (!empty($view_mode)) {
      // Add `block--BLOCK-TYPE--VIEW-MODE.html.twig`.
      $suggestions[] = 'block__' . $block->bundle() . '__' . $view_mode;
    }
  }

  return $suggestions;
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 *
 * Provide region based menu suggestions.
 */
function toland_theme_suggestions_menu_alter(&$suggestions, array $vars) {
  // Add theme suggestions to menus based on block region.
  if (isset($vars['attributes']['region'])) {
    $suggestion = 'menu__' . $vars['menu_name'] . '__region_' . $vars['attributes']['region'];
    $suggestion = str_replace('-', '_', $suggestion);
    $suggestions[] = $suggestion;
  }
}
