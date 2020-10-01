# Changelog
All notable changes to this project will be documented in this file.

_Note : the file `CHANGELOG.txt` is the Drupal 7 changelog. The present file lists changes made to Framaforms._

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## Unreleased

### Added
* BOTCHA module to fix the possible bypass of CAPTCHA Riddler.
* IP module to log user IPs.
* Anti-spam module `framaforms_spam` that put forms in quarantine containing suspicious words in title, or don't have any webform component.
* VBO (Views Bulk Operations) to put nodes inside quarantine and to take them out.
* Automatic deletion of forms in quarantine after a period of time.
* Views : /suspicious, displays unpublished forms from above.
* Views : /quarantine, displays forms in quarantine.
* Number of forms / user limit

### Fixed
* Empty "Share" tab on forms (#106)
* Unconsistent cache strategies for blocks in hook_block_info (`framaforms` module)
* Automatic deletion of forms to take into account notification period

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
