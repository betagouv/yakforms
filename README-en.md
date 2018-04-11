Framaforms
==============

Description
===============
Framaforms helps you create online webforms and surveys.
See https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/ (in French ) and https://framablog.org/2016/10/05/en-savoir-un-peu-plus-sur-le-projet-framaforms/ (in French) for further informations.


Usage
=============
There isn't yet help for Framaforms. Nevertheless, you can read https://framaforms.org/fonctionnalites (in french) and https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/ for further information.


Installation
=================

Framaforms is based at 99% on Drupal 7, with some modules (like webform).

You don't need technical skills, but installation is a little bit more complicated than standard Drupal installation.

For performance reasons, Framaforms use postgresql databse which caused issues for making it a "[distribution](https://www.drupal.org/docs/7/distributions)"


## Prerequisite

* PHP 7+ (may works with previous version, but php7 is recommended for performance reason)
* Nginx (may works with Apache)
* postgresql 9.4.12 (or +)
* php extension mb_string for php7 ( ``sudo apt-get install php7.0-mbstring`` )
* a reachable web directory


## database

* create an user, a database and grant this user correct rights. See  http://www.sakana.fr/blog/2007/06/06/postgresql-create-a-user-a-database-and-grant-accesses/
  * next we will use ``framaforms_user`` as user and ``framaforms`` as database
* download initialization Framafoms database : http://framaforms.org/framaforms.sql (~ 20Mo)
* import this database (using ``postgres`` user)
  * `psql -U framaforms_user -W -h 127.0.0.1 framaforms < /path/to/framaforms.sql`
  * if you need to reimport the database, it is recommended to destroy and recreate the database before import:  `dropdb framaforms;createdb --encoding=UTF8 --owner=framaforms_user framaforms`

## Files

* type `git clone https://framagit.org/framasoft/framaforms.git` in your web directory
* make sure you apply corret user rights (``chown``) and give extended write/read permissions to /path/to/framaforms/sites/default/files
* create a directory and give it write permission (but not read permission). E.g: /path/to/framaforms_private_files/
* database connection configuration:
  * go to /path/to/framaforms/sites/default/
  * copy default.settings.php to settings.php
  * edit with database connection informations

```php
  $databases = array (
    'default' =>.
    array (
      'default' =>.
      array (
        'database' => 'framaforms',
        'username' => 'framaforms_user',
        'password' => 'yourpassword',
        'host' => 'localhost',
        'port' => '',
        'driver' => 'pgsql',
        'prefix' => '',
      ),
    ),
  );
```

* You can add an option to include forms in iframe by appending this to the file:

```php
  /**
   * Turn off the X-Frame-Options header entirely, to restore the previous
   * behavior of allowing the site to be embedded in a frame on another site.
   */
   $conf['x_frame_options'] = '';
```

## Site access

At the moment, you should (if everything is fine) access your site (e.g.: mysite.com).

* go to mysite.com
* connect with id ``admin`` and password ``changemeASAP!``
* **IMPORTANT**: edit your admin password :)
* edit informations of your site https://monsite.com/admin/config/system/site-information
* check paths https://monsite.com/admin/config/media/file-system
* check your installation and if your modules are up to date https://monsite.com/admin/reports/status
* optionally, activate cache informations for production use https://monsite.com/admin/config/development/performance

Logically, you could now use your framaforms site.
