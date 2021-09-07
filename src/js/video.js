/**
 * Misc JS functions.
 * @file
 */
(function ($, Drupal, drupalSettings) {

  /*
* Tabs bar.
*/
  Drupal.behaviors.ucsfVideo = {
    attach: function (context, settings) {
      // Video background.
      if ($().YTPlayer) {
        $(context).find("#video-url").once("video-bg").each(function () {
          $("#video-url").YTPlayer();
        });
      }
    }
  };

})(jQuery, Drupal, drupalSettings);
