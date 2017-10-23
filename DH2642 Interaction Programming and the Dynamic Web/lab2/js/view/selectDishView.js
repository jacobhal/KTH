var SelectDishView = function (container,model) {

	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishlist = container.find("#dishlist");
	this.dishSelect = container.find("#dish-select");
	this.dishSearch = container.find("#search-form");
	this.searchBox = container.find("#search");


	this.makeDishList = function(dishType, searchTerm) {
		model.getAllDishes(dishType).forEach(function (dish) {
				if(dish.name.indexOf(searchTerm) >= 0 || typeof searchTerm === undefined) {
					var $column = $('<div/>').addClass('col-sm-3');
					var $thumbnail = $('<div/>').addClass('thumbnail');

					var $img = $('<img/>').attr('src', 'images/' + dish.image);
					var $caption = $('<div/>').addClass('caption');

					var $h3 = $('<h3/>').html("<a href='#' class='dish-link' id='" + dish.id + "'>" + dish.name + "</a>");
					var $p = $('<p/>').html(dish.description);


					$caption.append($h3);
					$caption.append($p);

					$thumbnail.append($img);
					$thumbnail.append($caption);

					$column.append($thumbnail);

					$(this.dishlist).append($column);
					$("#people").attr('value', model.getNumberOfGuests());
			}

		});

	}

	this.makeDishList("main dish", "");

	// Update view with new model values
	this.update = function(obj) {
		$(this.dishlist).empty();
		this.makeDishList(this.dishSelect.val(), this.searchBox.val());
	}

}