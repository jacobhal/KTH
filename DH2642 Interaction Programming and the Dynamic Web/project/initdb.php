<?php
/**
 * Initiate database connection
 */
function makeDbConnection () {
	$servername = "localhost";
	$username = "root";
	$password = "";
	$db = "xmlproject";

	global $conn;
	// Connect using host, username, password and databasename
    $conn = mysqli_connect($servername, $username, $password, $db);

    // Check connection
    if (!$conn) {
    	echo "Error: Unable to connect to MySQL." . PHP_EOL;
        echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
	    echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
	    exit;
    }

}
?>