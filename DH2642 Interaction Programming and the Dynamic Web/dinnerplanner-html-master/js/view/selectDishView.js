//ExampleView Object constructor
var SelectDishView = function (container,model) {

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishlist = container.find("#dishlist");
	
	model.getAllDishes("main dish").forEach(function (main) {
		var $column = $('<div/>').addClass('col-sm-2');
		var $thumbnail = $('<div/>').addClass('thumbnail');

		var $img = $('<img/>').attr('src', 'images/' + main.image);
		var $caption = $('<div/>').addClass('caption');

		var $h3 = $('<h3/>').html(main.name);
		var $p = $('<p/>').html(main.description);


		$caption.append($h3);
		$caption.append($p);

		$thumbnail.append($img);
		$thumbnail.append($caption);

		$column.append($thumbnail);

		$(this.dishlist).append($column);

	});

	

}