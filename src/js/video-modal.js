/**
 * Video modal JS functions.
 * NOTE*** This file is ES6. If you need jQuery, add $ in the function call.
 * @file
 * once vanilla - see https://www.drupal.org/project/drupal/issues/2402103.
 */
(function (Drupal, drupalSettings, once) {
  /*
  * Accesible video modal.
  */
  Drupal.behaviors.ucsfVideoModal = {
    attach(context) {
      // https://github.com/KittyGiraudel/a11y-dialog.
      // Video modal variables, get the ids by wildcard.
      const videos = once('video-only-once', context.querySelectorAll("[id^=video-dialog-]"))
      // Loop through the videos.
      for (let video in videos) {
        // Define the modal
        let dialog = new A11yDialog(videos[video])
        // Define the iframe within.
        let each_video = videos[video].querySelectorAll("iframe")
        // Get the actual source.
        let attribute = each_video[0].getAttribute('src')
        // On close event.
        dialog.on('hide', function (video) {
          // Replace the source.
          each_video[0].setAttribute('src', attribute)
        })
        dialog.on('show', function (video) {
          context.body.classList.add('modal-is-open')
        })
      }
    },
  };
}(Drupal, drupalSettings, once));
