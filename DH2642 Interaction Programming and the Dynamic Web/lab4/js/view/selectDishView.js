var SelectDishView = function (container,model) {

	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishlist = container.find("#dishlist");
	this.dishSelect = container.find("#dish-select");
	this.dishSearch = container.find("#search-form");
	this.searchBox = container.find("#search");

	this.showLoadingText = function() {
		var $loadingText = $('<h2/>').html("Loading...");
		$(this.dishlist).append($loadingText);
	}


	this.makeDishList = function(dishType, searchTerm) {
		this.showLoadingText();
		var dishes = model.getAllDishes(dishType, searchTerm, function(dishes) {
			$(this.dishlist).empty();
			if (dishes['results'].length == 0) {
				var $noneFoundText = $('<h2/>').html("No dishes found!");
				$(this.dishlist).append($noneFoundText);
			} else {
				var allDishes = dishes['results'];
				for(var dish in allDishes) {

					var $column = $('<div/>').addClass('col-sm-3');
					var $thumbnail = $('<div/>').addClass('thumbnail');

					var $img = $('<img/>').attr('src', allDishes[dish].image);
					var $caption = $('<div/>').addClass('caption');

					var $h3 = $('<h3/>').html("<a href='#' class='dish-link' id='" + allDishes[dish].id + "'>" + allDishes[dish].title + "</a>");
					var $p = $('<p/>').html("DESCRIPTION");


					$caption.append($h3);
					$caption.append($p);

					$thumbnail.append($img);
					$thumbnail.append($caption);

					$column.append($thumbnail);

					$(this.dishlist).append($column);
					$("#people").attr('value', model.getNumberOfGuests());
				}
			}
			
		});

	}

	this.makeDishList("0", "");

	// Update view with new model values
	this.update = function(obj) {
		if($.isNumeric(obj)) {
			$(this.dishlist).empty();
			this.makeDishList(obj, this.searchBox.val());
		}
	}

}