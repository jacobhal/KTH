$(function() {

  $.searchQ = function search(counter){
    var counter = counter;
    var url = $('#basic-addon1').attr('href');
    var refurl = $('#hiddendummy').attr('href');
    var game = $('#searchbar').val();

    $.ajax({
      type: "GET",
      url: url,
      data: { 'searchword' : game },
      error: function(xhr, status, error) {
        //alert(xhr.responseText);
        $('#gameslist').text('An error occurred');
      },
      success: function(response) {
        //$('#gameslist').html(response);
        var result = $.parseJSON(response);
        var output = "";
        if(result.length == 0) {
          $('#gameslist').html('<div>No games found</div>');
        } 
        else {
          for (var i in result) 
          {

            output += '<div class="col-lg-7" style="border: 2px solid #ccc; margin: 5px 0; padding: 10px; border-radius: 5px;"><a href="' 
            + refurl + '/' + result[i].token + '">' + result[i].title + '</a>' +'<span style="float: right; min-width: 40px;margin: 0; padding; 0;"><span class="glyphicon glyphicon-comment" aria-hidden="true" style="margin: 0; padding; 0;"></span><span style="float:right;margin: 0; padding; 0;">' 
            + counter[result[i].id] +'</span></span></div>';
            /*
            output += '<div><a href="' + refurl + '/' + result[i].token + '">' 
            + result[i].title + '</a></div>';
            */
          }
          $('#gameslist').html(output);
        }
      }
    }); 
  }

});
