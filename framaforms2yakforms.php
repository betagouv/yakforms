<?php

/**
 * @file
 * Contains a script for the Framaforms => Yakforms transition.
 */

include 'sites/default/settings.php';

/**
 * Wrapper to query database with PDO.
 */
function query_db($db_conn, $query_str) {
  $result = $db_conn->query($query_str);
  if ($result === FALSE) {
    throw new Exception("Malformed query in Framaforms2Yakforms script : " . $query_str);
  }
  return $result->fetchAll();
}

/**
 * Abort the current script and rollback transaction.
 */
function abort_and_die($db_conn) {
  $db_conn->rollBack();
  exit("Something went wrong. Please check for any error above.\n");
}

/**
 * Commit transcation and clean-exit the script.
 */
function commit_and_exit($db_conn, $message) {
  $db_conn->commit();
  exit($message . "\n");
}

/**
 * Restore all data of old module when the new one is installed.
 */
function restore_all($db_conn) {
  // Check if the backup table exists, otherwise abort.
  if (!check_backup_table_exists($db_conn)) {
    return FALSE;
  }
  // Restore all default variables by the old variables.
  try {
    $variables = query_db($db_conn, "SELECT name FROM variable WHERE name LIKE 'tmpforms_%'");
    foreach ($variables as $variable) {
      $toreplace = str_replace('tmpforms_framaforms', 'yakforms', $variable['name']);
      $replace_query = $db_conn->prepare("UPDATE variable SET value = (SELECT value FROM variable WHERE name=:tmpname) WHERE name=:toreplace");
      $replace_query->bindParam(':tmpname', $variable['name'], PDO::PARAM_STR);
      $replace_query->bindParam(':toreplace', $toreplace, PDO::PARAM_STR);
      $replace_query->execute();
    }
    // Insert data from old framaforms_expired table into yakforms_expired.
    query_db($db_conn, "INSERT INTO yakforms_expired (SELECT * FROM framaforms_expired_bak)");
    return TRUE;
  }
  catch (Exception $e) {
    echo("There was an error trying to restore backup data : {$e->getMessage()}.\n");
    return FALSE;
  }
}

/**
 * Cleans up temporary tables and variables.
 */
function clean_tmp_data($dbconn) {
  try {
    // Delete backup table.
    query_db($dbconn, "DROP TABLE framaforms_expired_bak");
    // Delete temporary variables.
    query_db($dbconn, "DELETE FROM variable WHERE name LIKE 'tmpforms_framaforms_%'");
    return TRUE;
  }
  catch (Exception $e) {
    echo("There was an error trying to delete temporary backup data : {$e->getMessage()} .
    This shouldn't bother normal site use. However, you can delete this data manually by running the following lines in your database :

    DELETE FROM variable WHERE name LIKE 'tmpforms_framaforms_%;
    DROP TABLE framaforms_expired_bak;

    ");
    return FALSE;
  }
}

/**
 * Looks up database to make sure backup tables exist.
 */
function check_backup_table_exists($db_conn) {
  try {
    $check_backup_query_table = "SELECT 1 FROM framaforms_expired_bak";
    $result = query_db($db_conn, $check_backup_query_table);
    return TRUE;
  }
  catch (Exception $e) {
    echo("The backup tables don't seem to exist. Did you run the script in backup mode ?\n");
    echo($e->getMessage());
    return FALSE;
  }
}

/**
 * Return database PDO connection from passed credentials, or FALSE if failed.
 */
function get_db_connection(array $credentials) {
  // Make sure the database array is properly formatted.
  $format = [
    'database' => "dummy",
    'username' => "dummy",
    'host' => "dummy",
    'password' => "dummy",
    'driver' => "dummy",
    'port' => "dummy",
  ];
  if (!is_array($credentials)
    && array_intersect_key($credentials, $format) === $credentials) {
    echo("The credentials in sites/default/settings.php don't seem to be properly formatted.\n");
    return NULL;
  }

  // Check the driver is either MySQL or PostgreSQL.
  if (!in_array($credentials['driver'], ['mysql', 'pgsql'])) {
    echo("Your database doesn't seem to be running PostgreSQL or MySQL.\n");
    return NULL;
  }

  // Get the database connection information.
  $db_name = $credentials['database'];
  $db_user = $credentials['username'];
  $db_host = $credentials['host'];
  $db_pw = $credentials['password'];
  $db_driver = $credentials['driver'];
  $db_port = $credentials['port'] == '' ? '5432' : $credentials['port'];

  // Create DB connection.
  $dsn = sprintf("%s:host=%s;dbname=%s;port=%s", $db_driver, $db_host, $db_name, $db_port);
  try {
    $dbconn = new PDO($dsn, $db_user, $db_pw, []);
    echo("Connected to database successfully.\n");
    return $dbconn;
  }
  catch (\PDOException $e) {
    echo("Error connecting to database : {$e->getMessage()}. \n Please check the credentials provided in sites/default/settings.php.\n");
    return NULL;
  }
}

/**
 * Returns the path of the installed module.
 */
function get_module_path() {
  if (file_exists(dirname(__FILE__) . '/sites/all/modules/framaforms/framaforms.info')) {
    return 'sites/all/modules/framaforms';
  }
  if (file_exists(dirname(__FILE__) . '/profiles/framaforms_org/modules/framaforms/framaforms.info')) {
    return 'profiles/framaforms_org/modules/framaforms';
  }
  echo("The module folder for Framaforms doesn't seem to exist under sites/all/modules or profiles/framaforms_org/modules. Are you executing this file in the root folder of your instance ?");
  return FALSE;
}

/*
 * SCRIPT.
 */

// Get the mode to run the script with : backup or restore.
$mode = isset($argv[1]) ? $argv[1] : NULL;
if (!isset($mode) || !in_array($mode, ['backup', 'restore', 'clean'])) {
  exit("Usage : php {$argv[0]} [backup | restore | clean]
    backup => Save all module data in temporary tables. Run before uninstalling Framaforms.
    restore => Restore all saved data after Yakforms is installed.
    clean => Delete temporary tables after data is restored.
"
  );
}
echo("Running with mode {$mode}\n");

// Open database connection.
$credentials = $databases['default']['default'];
$dbconn = get_db_connection($credentials);
if (!isset($dbconn)) {
  exit("Something went wrong when trying to connect to the database.\n");
}
$dbconn->beginTransaction();

if ($mode === "restore") {
  // Run in restore mode.
  $restored = restore_all($dbconn);
  if (!$restored) {
    // If something went wrong, abort the transaction.
    abort_and_die($dbconn);
  }
  // Otherwise, commit to validate changes.
  commit_and_exit($dbconn, "Done restoring data. Please check that your sites works properly.");
}

if ($mode === "clean") {
  // Run in clean mode.
  $cleaned = clean_tmp_data($dbconn);
  if (!$cleaned) {
    abort_and_die($dbconn);
  }
  // Otherwise, commit to validate changes.
  commit_and_exit($dbconn, "Done deleting temporary backup data. You can go back to using your site normally.");
}

// Run in backup mode.
$resSTDIN = fopen("php://stdin", "r");
echo("
This script will migrate legacy Framaforms module to a brand new Yakforms module.
This should not be run if framaforms is not installed.
WARNING ! this script will affect your living instance of Framaforms. You should backup your database to prevent any problem.
Are you sure you want to do this ? (y / n)
");
$line = stream_get_contents($resSTDIN, 1);
if ($line != "y" && $line != "Y") {
  abort_and_die($dbconn);
}
echo("Proceeding to the script.\n");

// Make sure the script is executed in the right place.
$module_path = get_module_path();
if (!$module_path) {
  abort_and_die($dbconn);
}

// Backup framaforms_expired this is deleted on module uninstall.
try {
  $backup_query = "CREATE TABLE framaforms_expired_bak AS TABLE framaforms_expired";
  $result = query_db($dbconn, $backup_query);
  // Backup framaforms_expired table.
  echo("The table framaforms_expired was saved as framaforms_expired_bak. Continuing...\n");
}
catch (Exception $e) {
  echo("An error was encountered when trying to backup the table framaforms_expired in your database : {$e->getMessage()}.\n");
  echo("Script aborted.\n");
  abort_and_die($dbconn);
}

// Save variables with a temp name as they are also deleted on module uninstall.
try {
  $variables = query_db($dbconn, "SELECT name FROM variable WHERE name LIKE 'framaforms_%'");
  // Insert variables back into the variables table with new names.
  foreach ($variables as $variable) {
    $tmp_varname = "tmpforms_" . $variable['name'];
    $insert_query = $dbconn->prepare("INSERT INTO variable VALUES(:name, (SELECT value FROM variable WHERE NAME=:original_name))");
    $insert_query->bindParam(':original_name', $variable['name'], PDO::PARAM_STR);
    $insert_query->bindParam(':name', $tmp_varname, PDO::PARAM_STR);
    $insert_query->execute();
  }
}
catch (PDOEXception $e) {
  echo("There was an error while creating a backup of the variables : {$e->getMessage()}\n");
  echo("Aborting the script so you don't loose data.\n");
  abort_and_die($dbconn);
}

commit_and_exit($dbconn, "
Backup of global variables finished.
You're done ! You can now proceed to the deinstallation of framaforms and to the installation of yakforms.
");
