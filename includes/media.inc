<?php

/**
 * @file
 * Functions to support theming in the Toland theme.
 */

use Drupal\image\Entity\ImageStyle;

/**
 * Prepares variables for media templates.
 */
function toland_preprocess_media(array &$vars) {
  // Get the video URL.
  if (isset($vars["content"]["field_media_oembed_video"]["#items"]->value)) {
    $vars['video_url'] = $vars["content"]["field_media_oembed_video"]["#items"]->value;
  }

  // Get the video fallback image URI.
  if (isset($vars["content"]["field_fallback_image"]["#items"]->target_id)) {
    $fallback_image = $vars["content"]["field_fallback_image"][0]["#media"]->get('field_media_image')->entity->uri->value;
    // Convert to an image style.
    $vars['video_fallback_image'] = ImageStyle::load('max_1300x1300')->buildUrl($fallback_image);
  }
}
