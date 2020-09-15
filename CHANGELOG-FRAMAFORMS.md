# Changelog
All notable changes to this project will be documented in this file.

_Note : the file `CHANGELOG.txt` is the Drupal 7 changelog. The present file lists changes made to Framaforms._

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## Unreleased

### Added
* BOTCHA module to fix the possible bypass of CAPTCHA Riddler.
* IP module to log user IPs.
* Anti-spam measures that unpublish forms containing suspicious words in title, or don't have any webform component.
* Automatic deletion of forms after a period of time.
* Views : /possible-spam, displays unpublished forms from above.

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