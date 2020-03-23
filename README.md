# Framaforms

Framaforms helps you create online webforms and surveys.

See why we created it ([#1](https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/) and [#2](https://framablog.org/2016/10/05/en-savoir-un-peu-plus-sur-le-projet-framaforms/) in French) for further general information.

## Usage

There isn't yet dedicated help for Framaforms. Nevertheless, you can read ([#3](https://framaforms.org/fonctionnalites) and [#1](https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/) in french) for further contextual information.

## Installation

Framaforms is based at 99% on Drupal 7, with some modules (like webform). You don't need superpowers, but the installation is more involved than that of Drupal.

Framaforms being dependent on postgresql, it cannot be "[distributed as a module](https://www.drupal.org/docs/7/distributions)" per the Drupal community standard.

### Prerequisites

* PHP 7 or later (may work with previous versions, but php7 is recommended for performance-wise)
* postgresql 9.4.12 or later
* php extension `mb_string` for php7 (`sudo apt-get install php7.0-mbstring` on debian-based systems)

*note:* we only support Nginx as reverse-proxy

### Database

* create an postgresql user (we use `framaforms_user`), a database (we use `framaforms`) and grant this user correct rights ([doc](http://www.sakana.fr/blog/2007/06/06/postgresql-create-a-user-a-database-and-grant-accesses/)).
* now let's download the initializer (~20MB) and set it up:

```sh
curl -L http://framaforms.org/framaforms.sql --output framaforms.sql
sudo -u postgres psql -U framaforms_user -W -h 127.0.0.1 framaforms < framaforms.sql
```

*note:* if you need to reimport the database, it is recommended to destroy and recreate the database beforehand: `dropdb framaforms;createdb --encoding=UTF8 --owner=framaforms_user framaforms`

### Files

Drupal needs a private directory for its user files. We name it `framaforms_private`, it can be changed to another directory with the approriate permissions afterwards from the administration interface (at <mysite.org>/admin/config/media/file-system).
* go to your web directory (we then assume you are in this directory)
* clone code and ensure proper directory permissions:

```sh
git clone https://framagit.org/framasoft/framaforms.git`
chown -R www-data:www-data sites/default/files
chmod -R 600 sites/default/files
cd ..
mkdir framaforms_private
chown -R www-data:www-data framaforms_private
chmod -R 200 framaforms_private
```

* database connection configuration:
  * `cd sites/default/`
  * `cp default.settings.php settings.php`
  * edit with database connection informations:

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

### Site access

Your site should now be accessible, but not yet production-ready:

* go to your domain
* connect with id `admin` and password `changemeASAP!`
* **IMPORTANT**: edit your admin password :)
* edit informations of your site https://<your domain>/admin/config/system/site-information
* check paths https://<your domain>/admin/config/media/file-system
* check your installation and if your modules are up to date https://<your domain>/admin/reports/status
* optionally, activate cache informations for production use https://<your domain>/admin/config/development/performance

You site should now be usable.
