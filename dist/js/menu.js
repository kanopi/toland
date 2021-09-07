"use strict";

/**
 * Main and mobile Menu JS functions.
 * @file
 */
(function ($, Drupal, drupalSettings, once) {
  /*
  * Misc functions.
  */
  Drupal.behaviors.ucsfdermMainMenu = {
    attach: function attach(context) {
      // Accessible Mega menu.
      if ($().accessibleMegaMenu) {
        // Initialize the megamenu.
        $("#block-main-navigation").accessibleMegaMenu({
          /* prefix for generated unique id attributes, which are required
             to indicate aria-owns, aria-controls and aria-labelledby  */
          uuidPrefix: "main_menu",

          /* css class used to define the megamenu styling */
          menuClass: "main-menu__item-list",

          /* css class for a top-level navigation item in the megamenu */
          topNavItemClass: "nav-item",

          /* css class for a megamenu panel */
          panelClass: "main-menu__sub-nav",

          /* css class for a group of items within a megamenu panel */
          panelGroupClass: "sub-nav-group",

          /* css class for the hover state */
          hoverClass: "hover",

          /* css class for the focus state */
          focusClass: "has-focus",

          /* css class for the open state */
          openClass: "panel-is-open",

          /* Open on hover (remove to open on click */
          openOnMouseover: true
        }); // Hover states and classes for submenu panels.

        $(context).find(".main-menu__item--submenu-level-1").each(function () {
          $(this).hover(function () {
            $(this).children('.main-menu__item-list--level-2').addClass('content-panel-is-open').removeClass('content-panel-is-closed');
            $(this).addClass('link-expanded').removeClass('link-collapsed');
          }, function () {
            $(this).children('.main-menu__item-list--level-2').removeClass('content-panel-is-open').addClass('content-panel-is-closed');
            $(this).removeClass('link-expanded').addClass('link-collapsed');
          });
        }); // Enhanced menu theming functions.
        // Note the order of these calls are important.

        $(context).find(".main-menu__item--submenu-level-0").once('menu-classes').each(function () {
          // Add a default class for some basic styling.
          $(this).find('> a').addClass('dropmenu'); // if Mega menu, add a class to the parent and remove dropmenu which is the default.

          if ($(this).find('> a').hasClass('mega')) {
            $(this).find('> a').removeClass('dropmenu');
            $(this).addClass('main-menu__item--mega');
          } // Drop down menu.


          if ($(this).find('> a').hasClass('dropmenu')) {
            $(this).addClass('is-dropmenu main-menu__item--dropmenu');
          }
        });
      } // @TODO - the goal here is to allow for tabbing to open 3rd level menu items.
      // @TODO  This needs work - try to recycle some of the code from above.


      $(context).find(".main-menu__item--submenu-level-1").each(function () {
        $(this).on('keydown', function (e) {
          var keyCode = e.keyCode || e.which;

          if (keyCode === 9) {
            e.preventDefault();
          }
        });
      });
    }
  };
  /*
  * Off-canvas menu (mmenu JS).
  */

  Drupal.behaviors.ucsfdOffCanvas = {
    attach: function attach(context, settings) {
      // Check for and instantiate Mmenu.
      if ($().mmenu) {
        var menu = new Mmenu("#block-off-canvas-nav", {
          // Options below.
          extensions: ["theme-black", "pagedim-black"],
          dropdown: true,
          counters: false,
          screenReader: {
            // Screen reader options.
            text: true,
            aria: true
          }
        }, {
          // A11y Additions.
          screenReader: {
            // Screen reader configuration.
            text: {
              closeMenu: 'Close Menu',
              closeSubmenu: 'Back',
              openSubmenu: 'Open submenu',
              toggleSubmenu: 'Toggle submenu'
            }
          },
          navbar: {
            title: "Menu"
          }
        }, {
          dropdown: {
            offset: {
              button: {
                y: 0,
                x: -10
              }
            }
          }
        }); // Get the menu API and data.

        var api = menu.API; // Choose the menu trigger.

        var trigger = document.getElementById('off-canvas-opener');

        if (trigger) {
          // onClick function.
          trigger.addEventListener('click', function () {
            if (document.body.classList.contains('mm-wrapper_opening')) {
              api.close();
            } else {
              api.open();
            }
          }, false); // Listen for keyboard enter key.

          trigger.addEventListener("keyup", function (event) {
            if (event.key === 'Enter') {
              // Trigger the menu to open when the enter key is pressed.
              api.open();
            }
          });
        } // A11Y: Add a tabindex to spans for better keyboard navigation.


        var menu_item = once('each-menu-item', context.querySelectorAll('.mm-btn > span'));

        for (var i = 0; i < menu_item.length; i++, event) {
          // Add a tabindex to the buttons.
          menu_item[i].setAttribute('tabindex', '0');
        }
      }
    }
  };
})(jQuery, Drupal, drupalSettings, once);