<?php session_start(); ?>
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
    <title>Lägg till kurs</title>
  </head>
  <body>
  <div class="page-wrap">
    <div id="sidebar" class="cf">
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/index.php">Kurslista</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/addCourse.php" class="active">Lägg till kurs</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/export.php">Exportera till Excel</a></div>
    </div>
    <div class="center main container">
    <h1>Lägg till kurs</h1>
    <!-- Todo: check that everything is filled in -->
    <form action="db_insert.php" method="post">
      <div class="form-group">
        <label for="name">Kursnamn:</label>
        <input type="text" class="form-control" id="name" name="name" required="true">
      </div>
      <div class="form-group">
        <label for="coursecode">Kurskod:</label>
        <input class="form-control" id="coursecode" name="coursecode" required="true">
      </div>
      <div class="form-group">
        <label for="year">Termin:</label>
        <select class="form-control" id="year" name="year" required="true">
          <option>HT16/VT17</option>
          <option>HT17/VT18</option>
          <option>HT18/VT19</option>
        </select>
      </div>
      <div class="form-group">
        <label for="link">URL till kurshemsidan:</label>
        <input class="form-control" id="link" name="link" required="true">
      </div>

      <div class="form-group">
        <label for="p1">Period 1:</label>
        <input type="number" step="any" class="form-control" id="p1" name="p1" min="0" required="true">
      </div>
      <div class="form-group">
        <label for="p2">Period 2:</label>
        <input type="number" step="any" class="form-control" id="p2" name="p2" min="0" required="true">
      </div>
      <div class="form-group">
        <label for="p3">Period 3:</label>
        <input type="number" step="any" class="form-control" id="p3" name="p3" min="0" required="true">
      </div>
      <div class="form-group">
        <label for="p4">Period 4:</label>
        <input type="number" step="any" class="form-control" id="p4" name="p4" min="0" required="true">
      </div>
      <button type="submit" class="btn btn-default">Lägg till</button>
    </form>
      
    </div>
    <div class="clear"></div>
    <?php 
    if (!empty($_SESSION['message'])) {

      echo '<div class="alert alert-success">';

      // let's show our message to a user
      echo $_SESSION['message'];
      // and don't forget to erase it from session
      unset($_SESSION['message']);
      echo '</div>';
      }
    if (!empty($_SESSION['fail_message'])) {

      echo '<div class="alert alert-danger">';

      // let's show our message to a user
      echo $_SESSION['fail_message'];
      // and don't forget to erase it from session
      unset($_SESSION['fail_message']);
      echo '</div>';
      }
      ?>
  </div>
  </body>
</html>
