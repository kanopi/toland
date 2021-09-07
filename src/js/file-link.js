/**
 * File JS functions.
 * NOTE*** This file is ES6. If you need jQuery, add $ in the function call.
 * @file
 * once vanilla - see https://www.drupal.org/project/drupal/issues/2402103.
 */
(function (Drupal, drupalSettings, once) {
  /*
  * File functions.
  */
  Drupal.behaviors.ucsfCustomFile = {
    attach(context) {
      // Add classes to the sidebar file download links.
      // Define the file Title/Name.
      const file_name = once('file-name-once', context.querySelectorAll('.media--type-document .field--name-name'))
      // Define the file link.
      const file_link = once('file-link-once', context.querySelectorAll('.media--type-document span.file > a'))
      // If there is a filelink.
      if (file_link) {
        // Define the classes to be added.
        const class_list = ['link-bg', 'link-bg--download']
        // Loop and add the classes.
        file_link.forEach(element => element.classList.add(...class_list))
        // Loop and replace text.
        for (let i = 0; i < file_name.length; i++) {
          // Replace the text.
          file_link[i].innerHTML = Drupal.t("Download ") + file_name[i].innerHTML
        }
      }
    },
  };
}(Drupal, drupalSettings, once));
