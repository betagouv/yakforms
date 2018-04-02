Framaforms 
==============
(documentation is mainly in french. Some informations in english at the bottom of this file, you are very welcome to help translating)


Description
===============
Framaforms est un logiciel de création de formulaires en ligne.
Lire https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/ et https://framablog.org/2016/10/05/en-savoir-un-peu-plus-sur-le-projet-framaforms/ pour plus d'informations.

Current version
================
1.0 - 20180402

Changelog
============
Un changelog sommaire est disponible sur https://framagit.org/framasoft/framaforms/wikis/logbook


Utilisation
=============
Il n'existe pas encore d'aide pour Framaforms. Vous pouvez cependant lire https://framaforms.org/fonctionnalites et https://framablog.org/2016/10/05/framaforms-noffrez-plus-les-reponses-que-vous-collectez-a-google/ pour plus d'informations.


Installation
=================

Framaforms est basé à 99% sur Drupal 7, accompagné de différents modules (notamment le module webform).

Le niveau technique pour l'installer n'est pas très élevé, mais l'installation est tout de même plus complexe que l'installation d'un Drupal "standard".

Pour des raisons de performances, Framaforms utilise postgresql comme BDD, ce qui posait probleme pour en faire une "distribution" <https://www.drupal.org/docs/7/distributions>.

## Prérequis

* PHP 7+ (peut fonctionner avec des versions antérieures, mais PHP7 recommandé pour des raisons de performances)
* Nginx (peut fonctionner avec Apache)
* postgresql 9.4.12 (ou +)
* extension php mb_string pour php7 ( sudo apt-get install php7.0-mbstring )
* un dossier web accessible et fonctionnel


## Base de données

* Créer un utilisateur, une base de données, et attribuer les droits nécéssaires à cet utilisateur sur cette base. Ex: http://www.sakana.fr/blog/2007/06/06/postgresql-create-a-user-a-database-and-grant-accesses/
  * pour la suite, nous prendrons comme exemple le user "framaforms_user" et comme BDD "framaforms"
* Télécharger la BDD d'initialisation de Framaforms : http://framaforms.org/framaforms.sql (environ 20Mo)
* Importer cette base de données (à faire avec l'utilisateur système "postgres"
  * `psql -U framaforms_user -W -h 127.0.0.1 framaforms < /path/to/framaforms.sql`
  * NB : si vous devez réimporter la base d'initialisation, il est conseillé de détruire puis recréer la BDD avant importation :  `dropdb framaforms;createdb --encoding=UTF8 --owner=framaforms_user framaforms`

## Fichiers

* faire un `git clone https://framagit.org/framasoft/framaforms.git` dans le dossier web de votre choix
* assurez-vous d'appliquer les bons droits utilisateur (chown) et de donner des permissions étendues en lecture/écriture sur /path/to/framaforms/sites/default/files
* créez un dossier qui sera accessible en écriture (mais pas en lecture) à votre utilisateur web. Ex: /path/to/framaforms_private_files/
* configuration de la connexion à la BDD :.
  * allez dans le dossier /path/to/framaforms/sites/default/
  * copiez le fichier default.settings.php en settings.php
  * editez ce fichier et modifiez les information de connexion à la BDD
  
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

* profitez en pour ajouter la possibilité d'inclure vos formulaires dans des iframes en toute fin de fichier

```php
  /**
   * Turn off the X-Frame-Options header entirely, to restore the previous
   * behavior of allowing the site to be embedded in a frame on another site.
   */
   $conf['x_frame_options'] = '';
```

## Accéder au site

A ce stade, vous devriez (si tout va bien) accéder à votre site (par exemple sur monsite.com) .

* Rendez-vous sur https://monsite.com/
* Connectez vous avec l'identifiant "admin" et le mot de passe "changemeASAP!"
* IMPORTANT : Modifiez votre mot de passe administrateur :)
* Editez les infos de https://monsite.com/admin/config/system/site-information
* Vérifiez les chemins d'accès sur https://monsite.com/admin/config/media/file-system
* Vérifiez que votre installation et vos modules sont à jour sur https://monsite.com/admin/reports/status
* Activez éventuellement les informations de cache lorsque vous passerez en production : https://monsite.com/admin/config/development/performance

Logiquement, vous devriez pouvoir commencer à utiliser votre instance de Framaforms.


English version
==================
(not ready :-/ Why not help us to translate this file?)









