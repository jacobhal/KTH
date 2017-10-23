<?php
/**
 * Initiate database connection
 */
function makeDbConnection () {
	$servername = "localhost";
	$username = "root";
	$password = "";
	$db = "labb4";

	global $conn;
	try {
		// Create connection
		$conn = new PDO("mysql:host=$servername;dbname=$db;charset=utf8", $username, $password);

		$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

		//echo '<script>alert("Connected successfully")</script>';
	} catch (PDOException $e) {
	    //echo "Error: " . $e->getMessage();
	    echo '<script>alert("Error: " . $e->getMessage())</script>';
		//echo "<script type='text/javascript'>alert('error');</script>";
	}
}
?>