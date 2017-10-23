<?php
session_start();
//initilize PHP
ini_set('display_errors', 1);
error_reporting(E_ALL);

$id = $_GET['id'];

require 'initdb.php';
makeDbConnection();
global $conn;

// sql to delete a record
$sql = "DELETE FROM courses WHERE coursecode='$id'";

if ($conn->query($sql) === TRUE) {
    $_SESSION['message'] = 'Kursen togs bort!';
} else {
    $_SESSION['fail_message'] = 'Något gick fel:(';
}

$conn->close();

header("Location: index.php"); /* Redirect browser */

?>
