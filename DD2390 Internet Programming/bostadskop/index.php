<!DOCTYPE HTML>
<html>
  <head>
    <link rel="stylesheet" href="style.css" type="text/css"> 
    <meta http-equiv="content-type" content="text/html; charset=utf-8"></meta>
    <script type="text/javascript" src="javascript/jquery-1.12.0.js"></script>
    <?php require 'initdb.php';?>
    <!-- Global variables -->
    <script>
      currentSorting = "pris";
      currentOrder = 1;
    </script>
    <title>Bostadsköp</title>
  </head>
  <body>
  <div class="center">
    <h1>Bostadsköp</h1>
    <span id="nores" hidden="true">No Results</span>
    <div id="additem">
      <form id="search" action="" method="post" onkeyup="$.searchQ(currentSorting, currentOrder);">
        <div class="minmaxwrapper">
          <input id="searchfield" type="text" name="search" placeholder="Search...">
          <select id="options">
            <option value="">Sök bland alla län</option>
            <?php 
              makeDbConnection();
              global $conn;
              $stmt = $conn->prepare("SELECT DISTINCT lan FROM bostader");
              $stmt->execute();
              $rows = $stmt->fetchAll();
              $count = $stmt->rowCount();
              if($count != 0) {
                foreach($rows as $row) {
                  echo "<option value=" . $row['lan'] . ">" . $row['lan'] . "</option>";
                }
              }     
            ?>
        </select>
      </div>
      <div class="minmaxwrapper">
        <input class="minmax" type="text" name="minArea" placeholder="Area from">
        <input class="minmax" type="text" name="maxArea" placeholder="Area to">
      </div>
      <div class="minmaxwrapper">
        <input class="minmax" type="text" name="minPrice" placeholder="Price from">
        <input class="minmax" type="text" name="maxPrice" placeholder="Price to">
      </div>
      <div class="minmaxwrapper">
        <input class="minmax" type="text" name="minRoom" placeholder="Room from">
        <input class="minmax" type="text" name="maxRoom" placeholder="Room to">
      </div>
      <div class="minmaxwrapper">
        <input class="minmax" type="text" name="minFee" placeholder="Fee from">
        <input class="minmax" type="text" name="maxFee" placeholder="Fee to">
      </div>
      </form>
    </div>
    <div id="housecontainer">
      <table id="houselist">
          <thead class="unmarkable">
            <tr class="unmarkable">
              <th class="unmarkable"><a ascending=1 id="lan" href="#">Län<span style='font-family:Comic Sans MS;' class="arrow hidden"></span></a></th>
              <th class="unmarkable"><a ascending=1 id="objekttyp" href="#">Objekttyp<span class="arrow hidden"></span></a></th>
              <th class="unmarkable"><a ascending=1 id="adress" href="#">Adress<span class="arrow hidden"></span></a></th>
              <th class="unmarkable"><a ascending=1 id="area" href="#">Area<span class="arrow hidden"></span></a></th>
              <th class="unmarkable"><a ascending=1 id="rum" href="#">Rum<span class="arrow hidden"></span></a></th>
              <th class="unmarkable"><a ascending=1 id="pris" href="#">Pris<span class="arrow hidden">&#x25BC</span></a></th>
              <th class="unmarkable"><a ascending=1 id="avgift" href="#">Avgift<span class="arrow hidden"></span></a></th>
            </tr>
          </thead>
        <tbody id="output"></tbody>
      </table>
    </div>
      <input type="submit" class="btn" id="insert" name="insert" value="insert" />
  </div>
 <script>
 $(function() {
    $('#searchfield').focus();
    $('form').submit(function(e) {e.preventDefault();});
    $('#options').change(function() {
      $.searchQ(currentSorting, currentOrder);
    });

    // Sort on click
    $('a#lan').click(         function () { $.searchQ('lan', $(this).attr('ascending')); });
    $('a#objekttyp').click(   function () { $.searchQ('objekttyp', $(this).attr('ascending')); });
    $('a#adress').click(      function () { $.searchQ('adress', $(this).attr('ascending')); });
    $('a#area').click(        function () { $.searchQ('area', $(this).attr('ascending')); });
    $('a#rum').click(         function () { $.searchQ('rum', $(this).attr('ascending')); });
    $('a#pris').click(        function () { $.searchQ('pris', $(this).attr('ascending')); });
    $('a#avgift').click(      function () { $.searchQ('avgift', $(this).attr('ascending')); });

    // Read cookies and set fields where cookies are present
    var cookie = readCookie('searchWord');
    var cookie2 = readCookie('searchSelect');
    $('#searchfield').val(cookie);
    $('#options').val(cookie2);

    // Ajax search function
    $.searchQ = function(sort, order) {
      // TODO: Add arrow to show if ascending or descending
      var searchTxt = $("input[name='search']").val();
      var selector = "a#" + sort;
      var category = $("#options").val();
      var minArea = $("input[name='minArea']").val();
      var maxArea = $("input[name='maxArea']").val();
      var minPrice = $("input[name='minPrice']").val();
      var maxPrice = $("input[name='maxPrice']").val();
      var minRoom = $("input[name='minRoom']").val();
      var maxRoom = $("input[name='maxRoom']").val();
      var minFee = $("input[name='minFee']").val();
      var maxFee = $("input[name='maxFee']").val();
      currentSorting = sort;
      currentOrder = order;

      document.cookie='searchWord=' + $('form input#searchfield').val();
      document.cookie='searchSelect=' + $('form select').val();

      $.post("gethouses.php", {searchVal: searchTxt, sort: sort, order: order, cat: category, 
        minArea: minArea, maxArea: maxArea, minPrice: minPrice, maxPrice: maxPrice, minRoom: minRoom, maxRoom: maxRoom,
        minFee: minFee, maxFee: maxFee}, function(output) {
        if(output.length < 1) { 
          $('#nores').fadeIn(500);
        } else {
          $('#nores').fadeOut(500);
          $("#output").html(output);
        }
      });

        // Handle arrow direction
      if(order == 1) {
        $(selector + " span").css('font-size', '0.2em');
        $('thead th span').html(''); // Remove other headers arrows
        $(selector + " span").html('&#x25BC') // Add arrow to header clicked
        $('thead a').attr('ascending', 1);  // Reset other header arrows to make firt click ascending
        $(selector).attr('ascending', 0);  // Toggle current header arrow
      } else {
        $(selector + " span").css('font-size', '0.2em');
        $('thead th span').html('');
        $(selector + " span").html('&#x25B2');
        $('thead a').attr('ascending', 1);
        $(selector).attr('ascending', 1); 
      }
    }
    // Call searchQ initially with price ascending
    $.searchQ('pris', 1);

    // Split cookie string and read the specified one
    function readCookie(name) {
      var nameEQ = name + "=";
      var ca = document.cookie.split(';');
      for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
      }
      return null;
    }
  });
  </script>
  <!-- Insert new house script -->
  <script>
  // Additional functionality add a house with fixed parameters (see newhouse.php)
  $(document).on('click','#insert',function(e) {
      $.ajax({
         type: "post",
         url: "newhouse.php",
         success: function(status){
              //alert("New house added!" + status);
              $.searchQ(currentSorting, currentOrder);
         },
         error: function (xhr, ajaxOptions, thrownError) {
             //alert(xhr.status);
             alert(xhr.responseText);
             //alert(thrownError);
         }
    });
 });
  </script>
  </body>
</html>
