# What is this module ?

Yakforms provides a fully working form service. It is aimed to work along with the [Yakforms distribution](https://framagit.org/framasoft/framaforms) for Drupal 7.

Yakforms defines the following items for the website :

* A new **node type** : « form » or form1 (machine-name) nodes are publicly-accessible nodes that any authenticated user can create and configure. A webform is attached to each of node.
* Blocks and menu links for user navigation.
* Default pages.
* Cron tasks for limited-lifetime nodes : to avoid piling up useless data forever, forms expire after a few months by default. (This feature can be deactivated by the admin if necessary).
* A central administration menu to manage most of the website's parameters.

Though all releases are made available on Drupal.org to simplify the update process, the actual development takes place on [Framagit](https://framagit.org/framasoft/framaforms) for now.

# Some history
Yakforms was previously named `framaforms`, and was originally developped by French non-profit [Framasoft](https://framasoft.org/en/) during their [De-googleify Internet campaign](https://degooglisons-internet.org/en/).

# Where can I try Yakforms ?
A demonstration instance is available on [Framaforms.org](https://framaforms.org/).

# How can I contribute ?
Any help to develop this module is welcome !

You can get in touch on [Framacolibri](https://framacolibri.org/), a community help forum around free (as in freedom) software and culture.

Here is a non-limitative list of tasks we are looking to work on :
* a better design : the creation form for the `form1` node type is full of options and the amount of instructions can be overwhelming. We are looking to improve this process, which requires a _design_ look rather than a technical one.
* planning port to Drupal 8 and 9
* translation : we set up [a Weblate repo](https://weblate.framasoft.org/engage/framaforms/) to allow community translation of this module.
* everyday bugfixes and small improvements.

# Credits
Yakforms makes heavy use of [Webform](https://www.drupal.org/project/webform/) and [Form builder](https://www.drupal.org/project/form_builder/), along other modules. These modules are included in the distribution, and are required for this module.
