<?php
   include('initdb.php');
   session_start();

   makeDbConnection();
   global $conn;
   
   $user_check = $_SESSION['login_user'];
   
   $session_sql = mysqli_query($conn, "SELECT username FROM admin where username = '$user_check' ");
   
   $row = mysqli_fetch_array($ses_sql, MYSQLI_ASSOC);
   
   $login_session = $row['username'];
   
   if(!isset($_SESSION['login_user'])){
      header("location: index.php");
   }
?>