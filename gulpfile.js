const gulp = require('gulp');
const { parallel, series, watch } = require('gulp');
const sass = require('gulp-sass')(require('sass')),
  autoprefixer = require('gulp-autoprefixer'),
  sourcemaps = require('gulp-sourcemaps'),
  browserSync = require('browser-sync').create(),
  uglifyes = require('uglify-es'),
  composer = require('gulp-uglify/composer'),
  uglify = composer(uglifyes, console),
  svgSprite = require('gulp-svg-sprite'),
  concat = require('gulp-concat'),
  babel = require('gulp-babel'),
  sasslint = require('gulp-sass-lint'),
  clean = require('gulp-clean'),
  csscomb = require('gulp-csscomb');

const styles = () => {
  return gulp.src(['!./src/scss/vendor/**/*.scss', './src/scss/**/*.scss'])
    .pipe(sasslint({
      configFile: './sass-lint.yml',
    }))
    .pipe(sasslint.format())
    .pipe(sasslint.failOnError())
    .pipe(sourcemaps.init())
    .pipe(sass({
      outputStyle: 'expanded',
    }).on('error', sass.logError))
    .pipe(autoprefixer({
      cascade: false
    }))
    .pipe(sourcemaps.write('./'))
    .pipe(csscomb('./csscomb.json'))
    .pipe(gulp.dest('./dist/css'))
    .pipe(browserSync.reload({
      stream: true,
      match: '**/*.css'
    }))
};
exports.sass = styles;

// browserSync.
// To get browserSync running locally, you can run fin gulp
// and then be sure to have this snippet in your local
// settings file: $config['toland.settings']['browsersync'] = 1;
// This hooks into a custom theme setting and adds the JS for browserSync.
// The reason for this is, we use a different local URL so browserSync proxy does
// not understand how to get to the page otherwise.
const browser_sync = () => {
  browserSync.init({
    injectChanges: true,
    logPrefix: 'Default Theme',
    baseDir: './',
    open: false,
    notify: true,
    host: process.env.VIRTUAL_HOST,
    openBrowserAtStart: false,
    reloadOnRestart: true,
    port: 31254,
    ui: false,
  });
};
exports.browserSync = series(styles, browser_sync);

// Copy the src icons to dist.
const copy_svg = () => {
  return gulp.src('./src/icon/raw/*.svg')
    .pipe(gulp.dest('./dist/icon/svg'));
};
exports.copy_svg = copy_svg;


// svgSprite function.
const sprites = (done) => {
  // Basic configuration example.
  var config = {
    //log: 'debug',
    shape: {
      dimension: { // Set maximum dimensions.
        maxWidth: 110,
        maxHeight: 110
      },
      spacing: { // Add padding.
        padding: 0
      },
    },
    mode: {
      view: {
        bust: false,
        common: 'ico',
        dest: './dist/icon/',
        example: {
          dest: './icons.html'
        },
        prefix: '.',
        render: {
          scss: {
            template: './src/icon/svg-sprite-template.scss',
            dest: '../../src/scss/_icons.scss'
          }
        },
        sprite: 'icons.svg',
      }
    }
  };

  gulp.src('./src/icon/raw/*.svg')
    .pipe(svgSprite(config))
    .pipe(gulp.dest('./'));  
  done();
};
exports.svgConcat = sprites;

// JS.
const scripts = () => {
  return gulp.src('./src/js/**/*.js')
    .pipe(babel({
      presets: ['@babel/env']
    }))
    .pipe(gulp.dest('./dist/js'))
    .pipe(uglify())
    .on('error', function (err) {
      console.log(err)
    })
};
exports.scripts = scripts;

// Combine the global css files into one for ckeditor to use.
const concater = () => {
  return gulp.src('./dist/css/global/*.css')
    .pipe(csscomb('./csscomb.json'))
    .pipe(concat('ckeditor.css'))
    .pipe(gulp.dest('./dist/css'));
};
exports.concat = concater;

// browser-sync watch.
//gulp.task('watch', ['browser-sync'], function (gulpCallback) {
//  gulp.watch("./src/scss/**/*.scss", ['sass']);
//  gulp.watch("./src/js/**/*.js", ['scripts']).on('change', browserSync.reload);
//  gulp.watch("./templates/**/*.html.twig").on('change', browserSync.reload);
  // Notify gulp that this task is done.
//  gulpCallback();
//});
const doWatch = () => {  
  watch("./src/scss/**/*.scss", styles)
  watch("./src/js/**/*.js", scripts);
  watch(["./src/icon/raw/*.svg", "./src/icon/svg-sprite-template.scss"], series(sprites, copy_svg));
}
exports.watch = doWatch;

exports.build = series(sprites, styles, scripts, concater, copy_svg);
// Task: handle svgs.
exports.svg = series(sprites, copy_svg);
// Task: Default gulp build and watch.
exports.default = series(styles, scripts);
// Concat CSS for ckeditor.
exports.combine = concat;
