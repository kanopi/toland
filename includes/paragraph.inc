<?php

/**
 * @file
 * Functions to support theming in the Toland theme.
 */

use Drupal\node\NodeInterface;
use Drupal\image\Entity\ImageStyle;

/**
 * Prepares variables for paragraph templates.
 *
 * Default template: paragraph.html.twig.
 *
 * Most themes use their own copy of paragraph.html.twig. The default is located
 * inside "templates/paragraph.html.twig". Look in there for the
 * full list of variables.
 *
 * @param array $vars
 *   An associative array containing:
 *   - elements: An array of elements to display in view mode.
 *   - paragraph: The paragraph object.
 *   - view_mode: View mode; e.g., 'full', 'teaser'...
 */
function toland_preprocess_paragraph(array &$vars) {
  // Define various vars needed.
  // From paragraphs_theme_suggestions_paragraph.
  $paragraph = $vars['elements']['#paragraph'];
  // Define the bundle.
  $paragraph_bundle = $paragraph->bundle();
  // Define the node.
  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node instanceof NodeInterface) {
    // Define the node title.
    $vars['node_title'] = $node->getTitle();
  }

  // Check for empty $paragraph.
  if (!empty($paragraph)) {
    // card_container $paragraph bundle.
    if ($paragraph_bundle === 'card_container') {
      // Get the card count.
      $card_count = count($vars["elements"]["field_card"]["#items"]);
      // Count the number of items in the array, if greater than 3.
      if ($card_count > 3) {
        // Set a twig variable.
        $vars['is_carousel'] = TRUE;
      }
    }

    if ($paragraph_bundle === 'filtered_list') {
      // Check for the scs view.
      if (!empty($paragraph->get("field_views")) && $paragraph->get("field_views")[0]->target_id === 'scs') {
        // Set a template variable.
        $vars['is_scs_view'] = TRUE;
      }
    }

    // Card $paragraph bundle.
    if ($paragraph_bundle === 'card') {
      // Get all the image attributes so we construct
      // the image for the template. This helps us lazy load it in the carousel.
      if (!empty($vars["content"]["field_image"][0]["#media"]->field_media_image->entity->uri->value)) {
        $img_path = $vars["content"]["field_image"][0]["#media"]->field_media_image->entity->uri->value;
        $vars["carousel_img"] = ImageStyle::load('max_650x650')->buildUrl($img_path);
        $vars["img_alt"] = 'alt ="' . $vars["content"]["field_image"][0]["#media"]->field_media_image->alt . '"';
        $vars["img_width"] = $vars["content"]["field_image"][0]["#media"]->field_media_image->width;
        $vars["img_height"] = $vars["content"]["field_image"][0]["#media"]->field_media_image->height;
      }
    }

    if ($paragraph_bundle === 'person') {
      if (!empty($paragraph->getParentEntity()->field_components)) {
        $vars['attributes']['class'][] = 'c-person--is-freestanding-person';
      }
    }

    // People List bundle.
    if ($paragraph_bundle === 'people_list') {
      // Add classes depending on where this is being rendered.
      if (!empty($paragraph->getParentEntity()->field_sidebar_components)
        && ($paragraph->hasField('field_person') &&
          !$paragraph->get('field_person')->isEmpty())
      ) {
        if ($paragraph->get('parent_field_name')->value === 'field_sidebar_components') {
          $vars['attributes']['class'][] = 'people-list--is-sidebar';
        }
      }
    }

    // Add classes depending on where this is being rendered.
    if (!empty($paragraph->getParentEntity()->field_components)
      && ($paragraph->hasField('field_person') &&
        !$paragraph->get('field_person')->isEmpty())
    ) {
      if ($paragraph->get('parent_field_name')->value === 'field_components') {
        $vars['attributes']['class'][] = 'people-list--is-main-content';
      }
    }

    // Hero $paragraph bundle.
    if ($paragraph_bundle === 'hero') {
      // If field_background is set.
      if (isset($vars["content"]["field_background"])) {
        // Check for the media bundle name.
        if (isset($vars["content"]["field_background"][0]["#media"]->bundle->target_id)) {
          // Define the media type bundle.
          $media_bundle = $vars["content"]["field_background"][0]["#media"]->bundle->target_id;
          // Check for the media type image.
          if ($media_bundle === 'image') {
            // Set a variable for use in twig.
            $vars['is_media_image'] = TRUE;
          }

          // Check for the media type Remote video.
          if ($media_bundle === 'remote_video') {
            // Set a variable for use in twig.
            $vars['is_media_remote_video'] = TRUE;
          }

          // Array to target both bundles.
          $media_bundles = [
            'image',
            'remote_video',
          ];

          // Check for either media bundle and
          // add a class if field_hero_overlay is true.
          if (in_array($media_bundle, $media_bundles)) {
            if (!empty($vars["content"]["field_hero_overlay"][0]["#markup"])) {
              if ($vars["content"]["field_hero_overlay"][0]["#markup"] == 1) {
                // Add a class if the overlay box has been checked.
                $vars['attributes']['class'][] = 'hero--has-overlay';
              }
            }
          }
        }
      }
    }
  }
}

/**
 * Implements hook_theme_suggestions_HOOK().
 */
function toland_theme_suggestions_paragraph_alter(array &$suggestions, array $vars) {
  // Define various vars needed.
  // From paragraphs_theme_suggestions_paragraph.
  $paragraph = $vars['elements']['#paragraph'];
  // Define the bundle.
  $paragraph_bundle = $paragraph->bundle();
  // Define the view mode.
  $sanitized_view_mode = strtr($vars['elements']['#view_mode'], '.', '_');

  // Card bundle.
  if ($paragraph_bundle === 'card') {
    // Get the parent entity count for field_card.
    // We evaluate the expression and from that, we set a
    // theme hook if greater than 3.
    if (isset($paragraph->getParentEntity()->field_card)) {
      if (count($paragraph->getParentEntity()->field_card) > 3) {
        $suggestions[] = 'paragraph__' . $paragraph->bundle() . '__' . $sanitized_view_mode . '__carousel';
        $suggestions[] = 'paragraph__' . $paragraph->bundle() . '__carousel';
      }
    }
  }
}
