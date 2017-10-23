$(function() {

  $.searchGlobal = function search(count){
    var game = $('#games-global-search').val();
    var url = APP_URL + '/search/games';

    if(!game) {
      $("#global-search-result").hide();
      $("input#games-global-search").css('border-bottom-left-radius', '5px');
      $("input#games-global-search").css('border-bottom-right-radius', '5px');
    } else {
      $("#global-search-result").show();
      $("input#games-global-search").css('border-bottom-left-radius', '0');
      $("input#games-global-search").css('border-bottom-right-radius', '0');
    }
    $.ajax({
      type: "GET",
      url: url,
      data: { 'searchword' : game },
      error: function(xhr, status, error) {
        alert(xhr.responseText);
        //$('#gameslist').text('An error occurred');
      },
      success: function(response) {
        var result = $.parseJSON(response);
        var output = "";
        if(result.length == 0) {
          $('#global-games-search-ul').html('<li style=";border-bottom: 2px solid #fff;"><p style="margin-left: 15px;">No results</p></li>');
        } 
        else {       
          output = '<ul class="nav nav-pills nav-stacked span2" id="global-games-search-ul"><li class="global-game-counter" style=";border-bottom: 2px solid #fff;"><p style="margin-left: 15px;">Showing ' + result.length + ' results</p></li>';
          for (var i in result) 
          {
            output += '<li class="search-result-game"><a href="' + APP_URL + '/games/' + result[i].category_token + '/' + result[i].token + '">' + result[i].title + '</a></li>';
          }
          output += '</ul>';
          $('#global-games-search-ul').html(output);
        }
       
      }
    });
  
  }

});
