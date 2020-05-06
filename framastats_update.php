<?php 
include 'sites/default/settings.php';

/*
 * Creates a JSON output with general statistics about the website. 
 * To be executed through the crontab once a day or so. 
 * The database credentials are retrieved from the Drupal settings 
 * file (sites/default/settings.php)
 */

/***********
 * VARIABLES
 ***********/
$output_file = '/your/path/to/framaforms.json';     // absolute path to the output JSON file
$credentials = $databases['default']['default']; // from the Drupal settings

/***********
 * FUNCTIONS 
 ***********/

function getFramaformsStats($dbconn){
    $stats = array(); 
    try{
        // get total number of forms
        $forms_query = $dbconn->query("SELECT count(*) from node where type='form1'"); 
        $stats['nbForms'] = $forms_query->fetchColumn();

        // get total number of users
        $users_query = $dbconn->query("SELECT count(*) from users");
        $stats['nbUsers'] = $users_query->fetchColumn();;

        // get total number of submissions
        $submissions_query = $dbconn->query("SELECT count(*) from webform_submissions");
        $stats['nbSubmissions'] = $submissions_query->fetchColumn();
    }
    catch(Exception $e){
        error_log("Error retrieving Framastats information from database : ". $e->getMessage()); 
        return array(); 
    }
    return $stats; 
}

/********
 * SCRIPT 
 ********/ 

// retrieve the database credentials from the Drupal settings
$db_name = $credentials['database'];
$db_user = $credentials['username'];
$db_host = $credentials['host'];
$db_pw = $credentials['password'];
$db_driver = $credentials['driver'];
$db_port = $credentials['port'] == '' ? '5432' : $credentials['port'];

// connect to Postgres database
// $db_conn_instruction = sprintf("dbname=%s user=%s host=%s password=%s", $db_name, $db_user, $db_host, $db_pw);
$dsn = sprintf("%s:host=%s;dbname=%s;port=%s", $db_driver, $db_host, $db_name, $db_port);
try{
    $dbconn = new PDO($dsn, $db_user, $db_pw, array());
}
catch(\PDOException $e){
    error_log("Framastat update : Error connecting to database.");
    error_log($e->getMessage());
    echo("Error connecting to database. Please check the credentials you provided.");
    exit(-1);
}

// open file for writing
$file = fopen($output_file, 'w');
$stats = getFramaformsStats($dbconn);
// test the return array to check it is not empty.
// If it is, log and return with an error.
if(empty($stats)){
    error_log("Framastats error : there was an error executing queries for Framastats update. Please check the update script.", 0);
    exit(-1);
}

fwrite($file, json_encode($stats));
fclose($file);
?>
