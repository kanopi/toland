/**
 * Card carousel JS functions.
 * NOTE*** This file is ES6. If you need jQuery, add $ in the function call.
 * @file
 * once vanilla - see https://www.drupal.org/project/drupal/issues/2402103.
 */
(function (Drupal, drupalSettings, once) {
  /*
  * Cards carousel.
  */
  Drupal.behaviors.ucsfCarousel = {
    attach(context) {
      // Define all carousels.
      const carousel = once('each-carousel-once' , context.querySelectorAll('.carousel-wrap'));
      // Define the controls button text.
      const prev_slide = Drupal.t("Previous Slide");
      const next_slide = Drupal.t("Next Slide");
      // Loop through each carousel in case there are multiple on one page.
      (carousel).forEach(slider => {
          tns({
            container: slider,
            items: 3,
            slideBy: 1,
            autoplay: true,
            controls: true,
            controlsPosition: 'bottom',
            controlsText: ['<span>' + prev_slide + '</span>', '<span>' + next_slide + '</span>'],
            autoplayHoverPause: true,
            autoplayTimeout: 6500,
            lazyload: true,
            lazyloadSelector: ".tns-lazy",
            responsive: {
              320: {
                items: 1,
                gutter: 10,
              },
              800: {
                items: 2,
                gutter: 30,
              },
              1100: {
                items: 3,
                edgePadding: 1,
              }
            },
          });
        });
    },
  };
}(Drupal, drupalSettings, once));
