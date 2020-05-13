<?php 
include 'sites/default/settings.php';

/*
 * Creates a JSON output with general statistics about the website. 
 * The script should be called with the -f flag to indicate the output file.
 * To be executed through the crontab once a day or so. 
 * The database credentials are retrieved from the Drupal settings 
 * file (sites/default/settings.php)
 */

/***********
 * VARIABLES
 ***********/
$credentials = $databases['default']['default']; // from the Drupal settings

/***********
 * FUNCTIONS 
 ***********/

 // returns an associative array with the results
 // from the query passed as a string
 function returnQueryResult ($dbconn, $queryStr) {
    try {
        $result = $dbconn->query($queryStr);
        if(is_bool($result)){
            $error = "Malformed query in Framastats script : ". $queryStr ; 
            throw new Exception($error); 
        }
        return $result->fetchColumn();
    }
    catch(Exception $e){
        error_log("Error retrieving Framastats information from database : ". $e->getMessage()); 
        return array(); 
    }
 }

// Calls a query for each time interval : last day, week, month or year.
// $formatStr should be ready to be passed to sprintf(), for ex : 
// "SELECT COUNT(*) FROM node WHERE type = 'form1' AND to_timestamp(created) > NOW() - interval'%s'";
function getStatPerInterval ($dbconn, $formatStr){
    $intervals = array(
        'last24h' => '1 day', 
        'lastWeek' => '1 week', 
        'lastMonth' => '1 month', 
        'lastYear' => '1 year',
    );
    $statsForType = array();
    // get result for each interval 
    foreach($intervals as $key => $interval) {
        $statsForType[$key] = returnQueryResult($dbconn, sprintf($formatStr, $interval));
    }
    return $statsForType;
}

// returns associative array of statistics queried from the database.
function getFramaformsStats ($dbconn){
    $stats = array(); 

    // Get number of forms created per interval of time
    $nbFormsPerInterval = 
        "SELECT COUNT(*) FROM node WHERE type = 'form1' AND to_timestamp(created) > NOW() - interval'%s'";
    $stats['nbForms'] = getStatPerInterval($dbconn, $nbFormsPerInterval); 

    // Get total number of forms
    $stats['nbForms']['total_count'] = returnQueryResult($dbconn, "SELECT count(*) FROM node WHERE type='form1'"); 

    // Get number of users registered per interval of time
    $nbUsersPerInterval = 
        "SELECT COUNT(*) FROM users WHERE to_timestamp(created) > NOW() - interval'%s'";
    $stats['nbUsers'] = getStatPerInterval($dbconn, $nbUsersPerInterval);

    // Get total number of users
    $stats['nbUsers']['total_count'] = returnQueryResult($dbconn, "SELECT COUNT(*) FROM users");

    // Get number of webform submissions per interval of time
    $nbSubmissionsPerInterval = 
        "SELECT COUNT(*) FROM webform_submissions WHERE to_timestamp(submitted) > NOW() - interval'%s' AND is_draft = 0";
    $stats['nbSubmissions'] = getStatPerInterval($dbconn, $nbSubmissionsPerInterval);

    // Get total number of submissions
    $stats['nbSubmissions']['total_count'] = returnQueryResult($dbconn, "SELECT COUNT(*) FROM webform_submissions WHERE is_draft = 0");

    return $stats; 
}

/********
 * SCRIPT 
 ********/

 // Define flags
 // -f : the JSON output file
$options = "";
$options .= "f:";

$options = getopt($options);
$output_file = isset($options['f']) ? $options['f'] : '/var/www/framaforms/framaforms.json';

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
