"use strict";

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
  Drupal.behaviors.myTeaser = {
    attach: function attach(context) {
      // Define the view ids.
      var glossary_view_conditions = once('glossary-view-once', '#views-exposed-form-scs-conditions-block');
      var glossary_view_services = once('glossary-view-once', '#views-exposed-form-scs-services-block'); // If either one of these do not exist, add a message.

      if (!glossary_view_services.length && !glossary_view_conditions.length) {
        // Get the element we want to append to.
        var glossary_message = once('glossary-append-once', context.getElementById("scs-glossary") || []);

        if (glossary_message.length) {
          // Now append the message.
          glossary_message[0].insertAdjacentHTML('afterend', '<h2 class="h4">' + Drupal.t("Sorry, there were no results found.") + ' <a href="' + window.location.href.split('?')[0] + '">' + Drupal.t(" Click here") + '</a> ' + Drupal.t("to remove the filter, and search by another letter.") + '</h2>');
        }
      }
    }
  };
})(Drupal, drupalSettings, once);