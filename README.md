# UCSF Toland Theme

- [Getting started](#getting-started)
- [Sass and CSS](#sass-and-css)
- [Gulp Sass Linting](#gulp-sass-linting)
- [Gulp Sass JS transpiling using Babel](#gulp-sass-js-transpiling-using-babel)
  - [Mixins](#mixins)
  - [Extends](#extends)
  - [Units](#units)
  - [Utility classes](#utility-classes)
  - [SVG icons](#svg-icons)
  - [Gulp functions via fin](#gulp-functions-via-fin)
  - [Media Queries and Breakpoints](#media-queries-and-breakpoints)
    - [Examples](#examples)
      - [Min width](#min-width)
      - [Range](#range)
      - [Max-width](#max-width)
- [BrowserSync and live CSS injection](#browsersync-and-live-css-injection)
- [Javascript](#javascript)
- [IE11](#ie11)
- [Theming helpers](#theming-helpers)
- [Coding tips](#coding-tips)
- [Notes](#notes)

## Getting started

When you initially run `fin init` to get up and running with this project, that
command will spawn a sub-command to install NPMs. However, if you ever need to
make updates and re-run the front-end build install, you can run 
`fin init-theme`.

Thereafter you can run `fin gulp` to watch for changes for Sass and JS which 
in turn will compile the CSS. Sass and JS sources are in the `./src` folder 
and compiled assets land in the `./dist` folder. You'll always want to use 
Fin's version of gulp rather than a local version and `fin init-theme` takes
care of that and sets the correct version.

Note, you can run all these commands from the root of the project as the 
commands CD into the custom theme folder, 
`/ucsf8/docroot/sites/dermatology.ucsf.edu/themes/custom/toland`.

This theme uses core's *Stable* as a base theme.

## Sass and CSS

For this project, we are taking a granular approach via individual CSS files 
being output and then compartmentalized into various libraries loaded from 
specific templates. This aligns with Drupal core but gives us the ability to 
boost performance as well.

## Gulp Sass Linting

This project uses Sass linting to help us write better code. When you run 
`fin gulp`, you will see a list of errors and warnings print out in terminal
if there are any issues. An error will stop gulp so you can fix it and a 
warning will still continue to compile. If you need to adjust the linting 
settings, you can look in `sass-lint.yml`.

## Gulp Sass JS transpiling using Babel

This project converts any ES6 / 2015 code to ES5 in the `dist` folder so that 
Internet Explorer 11 can understand it. Your modern JS stays intact in the
`src` folder.

### Mixins

There are a whole host of mixins that can be utilized located in the `abstract` 
folder, `./scss/abstract/...`. Be sure to review these file for existing mixins
that will come in handy for theming.

### Extends

Use Sass extends sparingly only to extend page headings (`h1-h6` tags).
Ideally, just for headings when you need to change a heading's font size
but it might not be ideal to change the heading tag itself because of 
accessibility.

For example, you have an h2 that follows and h1 tag but the h2 needs to be
sized like an h3. Note, when extending a heading, use its class,
`@extend .h3;` rather than `@extend h3;`

```sass
.page-title__lede h2 {
  @extend .h3;
}
```

### Units

For font sizes use the rem mixin. e.g. `@include rem(font-size, 48px);` which 
compiles as `font-size: 3rem;`. For anything else, use pixels.

### Utility classes

There are a number of utility classes.

### SVG icons

- There are three mixins to utilize SVG icons that take arguments, some of them
  optional.
  - `@mixin icon-before()`
  - `@mixin icon-after()`
  - `@mixin icon()`

  These take various arguments, the `null` ones being optional:

  ```scss
  $icon,
  $width,
  $height,
  $rotate: null,
  $position: null,
  $top: null,
  $right: null,
  $bottom: null,
  $left: null,
  $opacity: null,
  $background-position: null,
  $translate_y: null
  ```

```scss
@include icon-before(icon-letters, 35px, 35px, $position: absolute);
```

- If you add new icons to `./icon/raw` run `fin gulp svg` to regenerate HTML.

### Gulp functions via fin

- `fin gulp` - (default) watches for JS and Sass changes, compiles the CSS.
  Live injects new css if you have BrowserSync enabled. See "BrowserSync
  and live CSS injection" below for more information.
- `fin gulp build` - Compiles the CSS
- `fin gulp svg` - Builds icon preview page and copies icons to the `dist`
  folder. You can preview the icons at [http://local.dermatology.ucsf.edu/sites/dermatology.ucsf.edu/themes/custom/toland/dist/icon/icons.html](http://local.dermatology.ucsf.edu/sites/dermatology.ucsf.edu/themes/custom/toland/dist/icon/icons.html)
- `fin gulp combine` - combines any css in `/dist/css/global` for use in
  ckeditor.

### Media Queries and Breakpoints

We are using Sass MQ for media queries as it's very versatile. They have
great documentation here: [https://github.com/sass-mq/sass-mq](https://github.com/sass-mq/sass-mq)

#### Examples

##### Min width

```sass
@include mq($from: large) {
```

##### Range

```sass
@include mq($from: large, $until: wide) {
```

##### Max-width

```sass
@include mq($until: large) {
```

***Note***, write media queries in small chunks within individual selectors
rather than encompassing many selectors with one giant media query.
For example:

```scss
   .header-no-lede {
      @include mq($from: large) {
       // CSS here.
      }
    }

    .header-has-link {
      @include mq($from: large) {
       // CSS here.
    }
```

## BrowserSync and live CSS injection

The gulpfile is set to reload pages upon save using BrowserSync and refresh
CSS while theming using `fin gulp`. As you make changes to Sass, your CSS
will get injected without a page reload for a more seamless and rapid theming
process. To make this work, you will need to add
`$config['toland.settings']['browsersync'] = 1;` to your local
settings file.

## Javascript

- Custom JS (mostly jQuery) is written in various scripts loaded per library in
- Use individual contexts for specific or related functions. e.g.

```javascript
Drupal.behaviors.tolandMenu = {
    attach: function (context, settings) {...
```

- Running `fin gulp` will compile the source JS located
  in `/ucsf8/docroot/sites/dermatology.ucsf.edu/themes/custom/toland/src/js`
  into the `dist` folder
- You can use ES2015 / ES6 code if you like as we are using gulp *uglifyes*.
- If adding a third party library and you do not need it to render
  everywhere, use specific conditions with a preprocess function to narrow
  the scope or use the Twig library method whereby adding the library
  right from within your template.

## IE11

You can target ie11 in Sass by using the IE11 mixin, e.g. `@include ie11 {...`

## Theming helpers

- **Twig tweak**
  - For documentation, see [the twig tweak cheat sheet](https://www.drupal.org/docs/8/modules/twig-tweak/cheat-sheet) and ["Rendering blocks with Twig Tweak"](https://www.drupal.org/node/2964457).
  - This is a handy module for rendering entities directly in a template.
      To discover plugin ids, you can run this command:

```bash
fin drush ev "print_r(array_keys(\Drupal::service('plugin.manager.block')->getDefinitions()));"
```

- Once you discover your plugin id, you can render it right in the template
  like this:
  - `{{ drupal_block('simple_gse_search_block') }}`

- **[Twig field value](https://www.drupal.org/project/twig_field_value)** - Allows you to get partial data from field render arrays. It gives you more control over the output without drilling deep into the render array or using preprocess functions.

- **[Link attributes](https://www.drupal.org/project/link_attributes)** - This lets you add custom attributes to menu items in the Drupal menu UI, the best use case being custom classes.

- **Twig template debugging** - This comes in handy to use Xdebug within Twig
  templates. Add `{{ drupal_breakpoint() }}` to your template and start
  debugging. You'll need the devel module enabled and Xdebug turned on in
  Docksal, see more info below under Coding tips.

## Coding tips

- It would be ideal to use [BEM style CSS syntax](https://css-tricks.com/bem-101/) in combination with Twig Field Value. For example:

    ```twig
    <div class = "column">
      {% if content.field_iconcard_title | render %}
        <div class="column__card-title">
          {{ content.field_iconcard_title | field_value }}
        </div>
      {% endif %}
    </div>
    ```

- It would be ideal to [setup PHPCS / Drupal coder](https://www.drupal.org/docs/8/modules/code-review-module/installing-coder-sniffer) for this project.
- Generously comment your code.
- Use a `docksal-local.env` file to enable [Xdebug](https://docs.docksal.io/tools/xdebug/). > `XDEBUG_ENABLED=1` You can find a `docksal-local.example.env` as an example in the `/.docksal folder`.

## Notes

You can generate a new TOC for this readme file here if needed: [https://ecotrust-canada.github.io/markdown-toc/](https://ecotrust-canada.github.io/markdown-toc/) Note, remove h1 tag in the TOC UI first before you generate.
