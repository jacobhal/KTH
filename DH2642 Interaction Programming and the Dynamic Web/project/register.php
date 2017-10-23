<?php
session_start();
// Redirect to index if logged in
if (isset($_SESSION['login_user']) != "") {
	header("Location: index.php");
}
require_once 'initdb.php';

// Define $username and $password
$username = $_POST['username'];
$password = $_POST['password'];

// Security stuff
$username = stripslashes($username);
$password = stripslashes($password);
$username = mysql_real_escape_string($username);
$password = mysql_real_escape_string($password);

$pw = password_hash($password, PASSWORD_DEFAULT);





?>