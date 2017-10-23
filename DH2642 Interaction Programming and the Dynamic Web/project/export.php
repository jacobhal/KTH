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
   
    <!-- Global variables -->
    <script>
      currentSorting = "pris";
      currentOrder = 1;
    </script>
    <title>Exportera till Excel</title>
  </head>
  <body>
  <div class="page-wrap">
  <div id="sidebar" class="cf">
      <div class="element"><a href="index.php">Kurslista</a></div>
      <div class="element"><a href="addCourse.php">Lägg till kurs</a></div>
      <div class="element"><a href="export.php" class="active">Exportera till Excel</a></div>
      <div class="clear"></div>
    </div>
  <? if (isset($_SESSION['login_user']) == "") {

    echo '<h1 style="text-align:center;">Logga in för att exportera</h1>
        <form action="login.php" method="POST" class="form-inline" id="loginForm">
          <div class="form-group">
            <label for="username">Användarnamn:</label>
            <input type="username" class="form-control" id="username" name="username">
          </div>
          <div class="form-group">
            <label for="pwd">Lösenord:</label>
            <input type="password" class="form-control" id="password" name="password">
          </div>
          <button type="submit" class="btn btn-default" name="submit">Logga in</button>
        </form>';
  } else {
    echo '<a href="logout.php">Logga ut</a>
    <div class="center main container">
    <h1>Exportera till Excel</h1>
    <!-- TODO -->
    <a href="fetch_excel.php" class="btn btn-info" role="button">Exportera!</a>
    </div>
    <div class="clear"></div>';
  }
  ?>
  </div>
  </body>
</html>
