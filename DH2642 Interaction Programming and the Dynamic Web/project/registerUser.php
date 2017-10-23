<?php session_start(); ?>
<!DOCTYPE HTML>
<html>
  <head>
    <link rel="stylesheet" href="app.css" type="text/css"> 
    <link rel="stylesheet" href="styling.css" type="text/css"> 
    <link rel="shortcut icon" type="image/x-icon" href="favicon.ico"/>
    <meta http-equiv="content-type" content="text/html; charset=utf-8"></meta>
    <script type="text/javascript" src="javascript/jquery-1.12.0.js"></script>
    <script type="text/javascript" src="javascript/bootstrap.min.js"></script>
  

  <title>Registrera</title>
  </head>
  <div class="page-wrap">
   
    <div class="center main container">
    <h1>Registrera</h1>
     <!-- Register form -->
    <form action="register.php" method="POST" id="registerForm">
      <div class="form-group">
        <label for="username">Användarnamn:</label>
        <input type="username" class="form-control" id="username" name="username">
      </div>
      <div class="form-group">
        <label for="pwd">Lösenord:</label>
        <input type="password" class="form-control" id="password" name="password">
      </div>
      <button type="submit" class="btn btn-default" name="submit">Logga in</button>
    </form>
    <div class="clear"></div>
    <?php include 'messages.php';?>
  </div>

  </body>
</html>
