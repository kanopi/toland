"use strict";

/**
 * Sidebar menu JS functions.
 * NOTE*** This file is ES6. If you need jQuery, add $ in the function call.
 * @file
 * once vanilla - see https://www.drupal.org/project/drupal/issues/2402103.
 */
(function (Drupal, drupalSettings, once) {
  /*
  * Sidebar menu.
  */
  Drupal.behaviors.ucsfDermSidebarMenu = {
    attach: function attach(context, settings) {
      // Find sidebar child menu items.
      var active_child_menu = once('sidebar-menu-once', context.querySelectorAll('.sidebar-menu--child .sidebar-menu__item')); // Loop through them.

      for (var i = 0; i < active_child_menu.length; i++) {
        // If a child has an active trail, add a class.
        if (active_child_menu[i].classList.contains('sidebar-menu__item--active-trail')) {
          document.body.classList.add('sidebar-active-child');
        }
      }
    }
  };
})(Drupal, drupalSettings, once);