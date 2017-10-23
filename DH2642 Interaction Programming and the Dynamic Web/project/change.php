<?php
session_start();
//initilize PHP
ini_set('display_errors', 1);
error_reporting(E_ALL);

$id = $_GET['id'];

require 'initdb.php';
makeDbConnection();
global $conn;

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
}



// sql to delete a record
$sql = "UPDATE courses SET coursecode='$coursecode', year='$year', name='$name', link='$link', p1='$p1', p2='$p2', p3='$p3', p4='$p4' WHERE coursecode='$id'";

if ($conn->query($sql) === TRUE) {
    $_SESSION['message'] = 'Kursen ändrades!';
} else {
    $_SESSION['fail_message'] = 'Något gick fel:(';
}

$conn->close();

header("Location: index.php"); /* Redirect browser */

?>
