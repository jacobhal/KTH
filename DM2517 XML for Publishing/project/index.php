<!DOCTYPE HTML>
<html>
  <head>
    <link rel="stylesheet" href="app.css" type="text/css"> 
    <link rel="stylesheet" href="style.css" type="text/css"> 
    <link rel="shortcut icon" type="image/x-icon" href="favicon.ico"/>
    <meta http-equiv="content-type" content="text/html; charset=utf-8"></meta>
    <script type="text/javascript" src="javascript/jquery-1.12.0.js"></script>
    <script type="text/javascript" src="javascript/bootstrap.min.js"></script>
    <?php require 'db_fetch.php';?>

   
    <!-- Global variables -->
    <script>
      currentSorting = "pris";
      currentOrder = 1;
    </script>
    <title>Alla kurser</title>
  </head>
  <body>
  <div class="page-wrap">
    <div id="sidebar" class="cf">
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/index.php" class="active">Kurslista</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/addCourse.php">Lägg till kurs</a></div>
      <div class="element"><a href="http://xml.csc.kth.se/~jacobhal/DM2517/project/export.php">Exportera till Excel</a></div>
    </div>
    <div class="center main container">
    <h1>Alla kurser</h1>
    <?php getCourses(); ?>
      
    </div>
    <div class="clear"></div>
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
  </body>
</html>
