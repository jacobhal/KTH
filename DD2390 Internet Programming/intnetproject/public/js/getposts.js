$(function() {
    // Perform on left-panel category click
    $('div.element').on( 'click', function() {
        // load is almost equivalent to $.get to prevent full page reload
        var fullpath = $(this).children().attr('href');
        //var fullpath = $(this).attr('target');
        //$('div.container').load(fullpath);
        
        $.ajax({
            url: fullpath,
            type: "GET",
            success: function(data){
                  $('div.main-content').html(data);
                  //$data = $(data); // the HTML content your controller has produced
                  //$('div.main-content').html($data[0]['text']);
            }
        });
        
        // Prevent default action
        return false;
    });
});