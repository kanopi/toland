/**
 * Custom JS functions.
 * NOTE*** This file is ES6. If you need jQuery, add $ in the function call.
 * @file
 * once vanilla - see https://www.drupal.org/project/drupal/issues/2402103.
 */
(function (Drupal, drupalSettings, once) {
  /*
  * Act on the glossary / exposed form.
  */
  Drupal.behaviors.Blazy = {
    attach(context) {
      // Blazy lazy load for fallback images.
      // Check if the script exists.
      if (typeof Blazy === 'function') {
        // Instantiate the script.
        const bLazy = new Blazy({});
      }
    },
  };
}(Drupal, drupalSettings, once));
