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
    <!-- AJAX search script -->
    <script type="text/javascript">
      function searchCourses() {
        var search = document.getElementById('search').value;
        var sortBy = document.getElementById('sortBy').value;
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
              document.getElementById("coursesTable").innerHTML = this.responseText;
          }
        };
        xmlhttp.open("GET", "db_fetch.php?search=" + search + "&sortBy=" + sortBy, true);
        xmlhttp.send();
			}
    </script>

    <title>Alla kurser</title>
  </head>
  <body onload="searchCourses('')">
  <div class="page-wrap">
    <div id="sidebar" class="cf">
      <div class="element"><a href="index.php" class="active">Kurslista</a></div>
      <div class="element"><a href="addCourse.php">Lägg till kurs</a></div>
      <div class="element"><a href="export.php">Exportera till Excel</a></div>
    </div>
    <?if (isset($_SESSION['login_user']) == "") {
      echo '<!-- Login form -->
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
      echo '<a href="logout.php">Logga ut</a>';
    }
    ?>
    <div class="center main container">
    <h1>Alla kurser</h1>
    <div class="form-group">
      <label for="search">Sök:</label>
      <input class="form-control" id="search" name="search" type="text" placeholder="Namn, Kurskod, Läsår..." onkeyup="searchCourses()">
    </div>
   <div class="form-group">
      <label for="sortBy">Sortera efter:</label>
      <select class="form-control" id="sortBy" name="sortBy" onchange="searchCourses()">
          <option value="name" selected>Namn</option>
          <option value="year">År</option>
          <option value="coursecode">Kurskod</option>
      </select>
    </div>
    <div id="coursesTable"></div>
    </div>
    <div class="clear"></div>
    <?php include 'messages.php';?>
  </div>

  </body>
</html>
