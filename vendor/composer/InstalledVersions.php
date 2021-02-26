<?php











namespace Composer;

use Composer\Semver\VersionParser;






class InstalledVersions
{
private static $installed = array (
  'root' => 
  array (
    'pretty_version' => 'dev-master',
    'version' => 'dev-master',
    'aliases' => 
    array (
    ),
    'reference' => 'c0457253f59708f09b54bf5ce982f935dc8b039a',
    'name' => 'framaforms/yakforms',
  ),
  'versions' => 
  array (
    'drupal/ctools' => 
    array (
      'pretty_version' => '1.17.0',
      'version' => '1.17.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.17',
    ),
    'drupal/drupal' => 
    array (
      'pretty_version' => '7.77.0',
      'version' => '7.77.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.77',
    ),
    'drupal/entity' => 
    array (
      'pretty_version' => '1.9.0',
      'version' => '1.9.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.9',
    ),
    'drupal/form_builder' => 
    array (
      'pretty_version' => '1.22.0',
      'version' => '1.22.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.22',
    ),
    'drupal/options_element' => 
    array (
      'pretty_version' => '1.12.0',
      'version' => '1.12.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.12',
    ),
    'drupal/pathauto' => 
    array (
      'pretty_version' => '1.3.0',
      'version' => '1.3.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.3',
    ),
    'drupal/token' => 
    array (
      'pretty_version' => '1.7.0',
      'version' => '1.7.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.7',
    ),
    'drupal/views' => 
    array (
      'pretty_version' => '3.24.0',
      'version' => '3.24.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-3.24',
    ),
    'drupal/views_access_callback' => 
    array (
      'pretty_version' => '1.0.0-beta1',
      'version' => '1.0.0.0-beta1',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.0-beta1',
    ),
    'drupal/views_bulk_operations' => 
    array (
      'pretty_version' => '3.6.0',
      'version' => '3.6.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-3.6',
    ),
    'drupal/webform' => 
    array (
      'pretty_version' => '4.23.0',
      'version' => '4.23.0.0',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-4.23',
    ),
    'drupal/yakforms' => 
    array (
      'pretty_version' => '1.1.0-beta1',
      'version' => '1.1.0.0-beta1',
      'aliases' => 
      array (
      ),
      'reference' => '7.x-1.1-beta1',
    ),
    'framaforms/yakforms' => 
    array (
      'pretty_version' => 'dev-master',
      'version' => 'dev-master',
      'aliases' => 
      array (
      ),
      'reference' => 'c0457253f59708f09b54bf5ce982f935dc8b039a',
    ),
    'squizlabs/php_codesniffer' => 
    array (
      'pretty_version' => '3.5.8',
      'version' => '3.5.8.0',
      'aliases' => 
      array (
      ),
      'reference' => '9d583721a7157ee997f235f327de038e7ea6dac4',
    ),
  ),
);







public static function getInstalledPackages()
{
return array_keys(self::$installed['versions']);
}









public static function isInstalled($packageName)
{
return isset(self::$installed['versions'][$packageName]);
}














public static function satisfies(VersionParser $parser, $packageName, $constraint)
{
$constraint = $parser->parseConstraints($constraint);
$provided = $parser->parseConstraints(self::getVersionRanges($packageName));

return $provided->matches($constraint);
}










public static function getVersionRanges($packageName)
{
if (!isset(self::$installed['versions'][$packageName])) {
throw new \OutOfBoundsException('Package "' . $packageName . '" is not installed');
}

$ranges = array();
if (isset(self::$installed['versions'][$packageName]['pretty_version'])) {
$ranges[] = self::$installed['versions'][$packageName]['pretty_version'];
}
if (array_key_exists('aliases', self::$installed['versions'][$packageName])) {
$ranges = array_merge($ranges, self::$installed['versions'][$packageName]['aliases']);
}
if (array_key_exists('replaced', self::$installed['versions'][$packageName])) {
$ranges = array_merge($ranges, self::$installed['versions'][$packageName]['replaced']);
}
if (array_key_exists('provided', self::$installed['versions'][$packageName])) {
$ranges = array_merge($ranges, self::$installed['versions'][$packageName]['provided']);
}

return implode(' || ', $ranges);
}





public static function getVersion($packageName)
{
if (!isset(self::$installed['versions'][$packageName])) {
throw new \OutOfBoundsException('Package "' . $packageName . '" is not installed');
}

if (!isset(self::$installed['versions'][$packageName]['version'])) {
return null;
}

return self::$installed['versions'][$packageName]['version'];
}





public static function getPrettyVersion($packageName)
{
if (!isset(self::$installed['versions'][$packageName])) {
throw new \OutOfBoundsException('Package "' . $packageName . '" is not installed');
}

if (!isset(self::$installed['versions'][$packageName]['pretty_version'])) {
return null;
}

return self::$installed['versions'][$packageName]['pretty_version'];
}





public static function getReference($packageName)
{
if (!isset(self::$installed['versions'][$packageName])) {
throw new \OutOfBoundsException('Package "' . $packageName . '" is not installed');
}

if (!isset(self::$installed['versions'][$packageName]['reference'])) {
return null;
}

return self::$installed['versions'][$packageName]['reference'];
}





public static function getRootPackage()
{
return self::$installed['root'];
}







public static function getRawData()
{
return self::$installed;
}



















public static function reload($data)
{
self::$installed = $data;
}
}
