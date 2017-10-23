<!DOCTYPE HTML>
<html>
  <head>
    <link rel="stylesheet" href="app.css" type="text/css"> 
    <link rel="stylesheet" href="style.css" type="text/css"> 
    <link rel="shortcut icon" type="image/x-icon" href="favicon.ico"/>
    <meta http-equiv="content-type" content="text/html; charset=utf-8"></meta>
    <script type="text/javascript" src="javascript/jquery-1.12.0.js"></script>
    <script type="text/javascript" src="javascript/bootstrap.min.js"></script>
    <?php require 'initdb.php';?>
   
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
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/index.php">Kurslista</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/addCourse.php">Lägg till kurs</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/export.php" class="active">Exportera till Excel</a></div>
      <div class="clear"></div>
    </div>
    <div class="center main container">
    <h1>Exportera till Excel</h1>
    <!-- TODO -->
    <a href="#" class="btn btn-info" role="button">Exportera!</a>
    </div>
    <div class="clear"></div>
  </div>
  </body>
</html>
