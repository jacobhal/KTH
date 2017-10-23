<!DOCTYPE HTML>
<html>
  <head>
    <link rel="stylesheet" href="style.css" type="text/css"> 
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
    <?php require 'dbconnection.php';?>
  </head>
  <body>
  <div class="center">
    <h1>Bostadsköp</h1>
    <div id="housecontainer">
      <table id="houselist">
          <thead>
            <tr>
              <th>Län</th>
              <th>Objekttyp</th>
              <th>Adress</th>
              <th>Area</th>
              <th>Rum</th>
              <th>Pris</th>
              <th>Avgift</th>
            </tr>
          </thead>
        <tbody>
         <? getHouses(); ?>
       </tbody>
      </table>
    </div>
      <input type="submit" class="btn" name="insert" value="insert" />
  </div>
  </body>
</html>
