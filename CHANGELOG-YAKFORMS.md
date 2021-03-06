# Changelog
All notable changes to this project will be documented in this file.

_Note : the file `CHANGELOG.txt` is the Drupal 7 changelog. The present file lists changes made to Yakforms._

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [1.1] 2021/05/20

IMPORTANT NOTE : Framaforms has become Yakforms. The modules were renamed, and manual action is needed on your instance
to upgrade to the latest version. Instructions here : https://framagit.org/yakforms/yakforms/-/wikis/From-Framaforms-to-Yakforms.

### Added
* Option to automatically export form submissions as CSV files before deletion (#113, introducted by !85, fixed by !104).
* Introduced Drupal Token mechanism, usable on full-HTML pages (#118, !100, !107).
* jQuery warning on form modification (!109).
* Option to set custom 'from' mail address and subject for notification emails.
* Warning message on forms where results are public (#67, !120).
* Possibility to limit the number of forms / user (#116, !126).
* Script to resend mails : `scripts/resend-mail.php` (!146).
* The custom modules ([Yakforms](drupal.org/project/yakforms), [Yakforms Public Results](https://www.drupal.org/project/yakforms_public_results) and [Yakforms Share Results](https://www.drupal.org/project/yakforms_share_results)) are now distributed on Drupal.org, allowing easier individual modules update using Drush or the Drupal admin UI.
* Subthemes based on TailwindCSS palette, selectable by end user on forms (!163)
* Possibility to translate the node creation form.

### Changed
* The `form1` content type is now part of the Framaforms module (declared via `includes/framaforms.node.inc`) (!89).
* Better admin menu (!93, !96).
* The HTML templates for default pages are now translatable (!99).
* Better stylesheet for printing forms (!124)
* Wide theme modifications for new graphical identity (!162)
* Drupal core and contrib module updates (!113, !150, !152).

### Fixed
* Expiration date is now modified when a form is cloned (#61)
* Useless fields were deleted from `framaforms_feature` (!89, fixed with !98).
* Cron notification of user (!112).
* Ajax 500 error when sharing results with users (#65).
* Fixed display of grid component submissions when no answer was provided by the user (#12, !118).
* Block links didn't take `$base_url` into account (#120, !110).
* Fixing handling of the modification of expired forms (!130).
* `Reply-To`and `From` email addresses on personal contact forms (!129).

## [1.0.3] 2020/10/12

### Added
* BOTCHA module to fix the possible bypass of CAPTCHA Riddler.
* IP module to log user IPs.
* VBO (Views Bulk Operations) to put nodes inside quarantine and to take them out.
* Automatic deletion of forms in quarantine after a period of time.
* Views : /suspicious, displays unpublished forms from above.
* Views : /quarantine, displays forms in quarantine.
* Number of forms / user limit
* Additional filter/check on user email
* Variables can now be reset from the adminstration pannel
* `translations/` subfolder to all custom modules, containing `.pot` and French `.po` file to allow translation.

#### New modules
* Anti-spam module `framaforms_spam` that put forms in quarantine containing suspicious words in title, or don't have any webform component. (Needs work)
* Akismet module (optional) to call the Akismet API (Wordpress)
* Node title validation to strengthen spam control

### Changed
* the notification email is now loaded from an external template.
* removed unused and unsecure `webform_report` module.
* Usage of `t()` function and other system functions to allow translation.

### Fixed
* Empty "Share" tab on forms (#106)
* Unconsistent cache strategies for blocks in hook_block_info (`framaforms` module)
* Automatic deletion of forms to take into account notification period.

## [1.0.1] 2020/07/15

### Added
* static assets that were previously missing (#68)

### Changed
* creation of default pages, now done through the admin menu of `framaforms` (#104)
* all displayed are now in French by default.

### Fixed
* issues with the notification email
* trailing error (#105)

## [1.0] 2020/07/07

### Added
* automatic expiration and deletion of webforms
* personnal contact form link at the bottom of forms

### Changed
* installation made easier through the installation profile

### Fixed
* some CSS and JS issues for responsive display
* "unique" box now possible to check (#84)
* errors when sorting results (#56)
* confirmation email fixed (#85, following December '19 update).

## [0.1] 2020/03/02

### Changed
* Modules updates not previously committed
