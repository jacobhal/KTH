<?php
session_start();
ini_set('display_errors', 1);
error_reporting(E_ALL);

require 'initdb.php';

newCourse();

/**
 * Create a new sale for a house
 */
function newCourse() {
	makeDbConnection();
	global $conn;
	
	// Prepare sql and bind parameters
    $stmt = $conn->prepare("INSERT INTO courses(coursecode, year, name, link, p1, p2, p3, p4, user_id) 
    	VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    $stmt->bind_param('ssssddddd', $coursecode, $year, $name, $link, $p1, $p2, $p3, $p4, $user_id);

    // Insert a row
    if (!empty($_POST["coursecode"]) && !empty($_POST["year"]) && !empty($_POST["name"]) && !empty($_POST["link"])
        && isset($_POST["p1"]) && isset($_POST["p2"]) && isset($_POST["p3"]) && isset($_POST["p4"])) {

        $coursecode = $_POST["coursecode"];
        $year = $_POST["year"];
        $name = $_POST["name"];
        $link = $_POST["link"];
        $p1 = $_POST["p1"];
        $p2 = $_POST["p2"];
        $p3 = $_POST["p3"];
        $p4 = $_POST["p4"];
        if(isset($_SESSION['login_user']) != "") {
            $user_id = $_SESSION['login_user'];
        }

        $stmt->execute();

        $_SESSION['message'] = 'Kursen lades till!';
    } else {
        $_SESSION['fail_message'] = 'Något gick fel:(';
    }

    $stmt->close();

    header("Location: addCourse.php"); /* Redirect browser */
    exit();
}
?>