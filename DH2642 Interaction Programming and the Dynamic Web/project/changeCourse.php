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
    <?php require 'initdb.php';?>
   
    <!-- Global variables -->
    <script>
      currentSorting = "pris";
      currentOrder = 1;
    </script>
    <title>Ändra kurs</title>
  </head>
  <body>
  <div class="page-wrap">
    <div id="sidebar" class="cf">
      <div class="element"><a href="index.php">Kurslista</a></div>
      <div class="element"><a href="addCourse.php">Lägg till kurs</a></div>
      <div class="element"><a href="export.php">Exportera till Excel</a></div>
    </div>
    <div class="center main container">
    <h1>Ändra kurs</h1>
    <!-- Todo: check that everything is filled in -->
    <form action="change.php?id=<?php echo $_GET['id']?>" method="post">
      <div class="form-group">
        <label for="name">Kursnamn:</label>
        <input type="text" class="form-control" id="name" name="name" required="true" value="<?= $_GET['name'] ?>">
      </div>
      <div class="form-group">
        <label for="coursecode">Kurskod:</label>
        <input class="form-control" id="coursecode" name="coursecode" required="true" value="<?= $_GET['id'] ?>">
      </div>
      <div class="form-group">
        <label for="year">Termin:</label>
        <select class="form-control" id="year" name="year" required="true" value="<?= $_GET['year'] ?>">
          <option <?php if ($_GET['year'] === 'HT16/VT17') echo 'selected' ; ?>>HT16/VT17</option>
          <option <?php if ($_GET['year'] === 'HT17/VT18') echo 'selected' ; ?>>HT17/VT18</option>
          <option <?php if ($_GET['year'] === 'HT18/VT19') echo 'selected' ; ?>>HT18/VT19</option>
        </select>
      </div>
      <div class="form-group">
        <label for="link">URL till kurshemsidan:</label>
        <input class="form-control" id="link" name="link" required="true" value="<?= $_GET['link'] ?>">
      </div>

      <div class="form-group">
        <label for="p1">Period 1:</label>
        <input type="number" step="any" class="form-control" id="p1" name="p1" min="0" required="true" value="<?= $_GET['p1'] ?>">
      </div>
      <div class="form-group">
        <label for="p2">Period 2:</label>
        <input type="number" step="any" class="form-control" id="p2" name="p2" min="0" required="true" value="<?= $_GET['p2'] ?>">
      </div>
      <div class="form-group">
        <label for="p3">Period 3:</label>
        <input type="number" step="any" class="form-control" id="p3" name="p3" min="0" required="true" value="<?= $_GET['p3'] ?>">
      </div>
      <div class="form-group">
        <label for="p4">Period 4:</label>
        <input type="number" step="any" class="form-control" id="p4" name="p4" min="0" required="true" value="<?= $_GET['p4'] ?>">
      </div>
      <button type="submit" class="btn btn-default">Ändra</button>
    </form>
      
    </div>
    <div class="clear"></div>
    <?php include 'messages.php';?>
  </div>
  </body>
</html>
