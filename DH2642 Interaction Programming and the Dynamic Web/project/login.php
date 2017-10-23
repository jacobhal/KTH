<?php
session_start();
if (empty($_POST['username']) || empty($_POST['password'])) {
	$_SESSION['fail_message'] = 'Fyll i båda fälten';
} else {

require 'initdb.php';
makeDbConnection();
global $conn;

// Define $username and $password
$username = $_POST['username'];
$password = $_POST['password'];

// Security stuff
$username = stripslashes($username);
$password = stripslashes($password);
$username = mysql_real_escape_string($username);
$password = mysql_real_escape_string($password);

// Query
$sql = "SELECT * FROM users WHERE username='$username' AND password='$password'";

$result = mysqli_query($conn, $sql);
$row = mysqli_fetch_array($result, MYSQLI_ASSOC);  
$count = mysqli_num_rows($result);

if($count == 1) {
	$_SESSION['login_user'] = $row['id'];
	$_SESSION['message'] = "Inloggningen lyckades!";

} else {
	$_SESSION['fail_message'] = 'Användarnamn och/eller lösenord felaktigt';
}
$conn->close();

}
header("location: index.php");


?>