var PreviewDishView = function (container,model) {
	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishdesc = container.find("#dishdesc");
	this.dishprep = container.find("#dishprep");

	var $columnLeft = $('<div/>').addClass('col-md-6').addClass('dishOverview');
	var $columnRight = $('<div/>').addClass('col-md-6').addClass('ingredients');

	var dish = model.getDish(100);

	this.getDish = function(id) {
		if(id !== undefined) {
			dish = model.getDish(id);
		}
		// Get the dish description and ingredients
		 // 100 = Meat balls

		// Left column
		var $dishName = $('<h3/>').html(dish.name);
		var $dishImg = $('<img/>').attr('src', 'images/' + dish.image).css({"width":"100%", "height":"200px", "display":"block", "margin":"0 auto"});
		// For some reason the description of the dish is also the instructions on how to make it.
		// If you look at the prototype they are suppose be separate, one under the img and one under
		// the header "Preparation". So I made this string as a placeholder.
		var loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in repre";
		var $dishCaption = $('<p/>').html(loremIpsum);
		var $backButton = $('<a/>').addClass('btn btn-default').html("Back to Select Dish").attr('href', '#').attr('id', 'backToSelectDishButton');
		$columnLeft.append($dishName).append($dishImg).append($dishCaption).append($backButton);
		$(this.dishdesc).append($columnLeft);

	
	}


	// Right column (Ingredient list)
	this.makeIngredientList = function(nrOfGuests) {
		var ingredients = dish.ingredients;
		var $ingredientsHeader = $('<h3/>').html("Ingredients for " + nrOfGuests + " people").attr('id', 'ingredientsHeader');
		var $ingredientsTable = $('<table/>').addClass('table');

		var totalPrice = 0;
		for (var i = 0; i < ingredients.length; i++) {
			var $mesure = $('<td/>').html(ingredients[i].quantity*nrOfGuests + " " + ingredients[i].unit);
			var $name = $('<td/>').html(ingredients[i].name);
			var $price = $('<td/>').html('SEK ' + ingredients[i].price*nrOfGuests);
			totalPrice += ingredients[i].price;
			var $row = $('<tr/>').append($mesure).append($name).append($price);
			$ingredientsTable.append($row);
		}

		var $totalPrice = $('<td/>').html('SEK ' + totalPrice*nrOfGuests);
		var $confirmButton = $('<button/>').addClass('btn btn-default').attr('id', 'dishConfirm').html('Confirm dish');
		var $buttonTd = $('<td/>').html($confirmButton);
		var $priceElement = $($totalPrice).attr('id', 'totalPrice');
		var $lastRow = $('<tr/>').append($buttonTd).append('<td/>').append($priceElement);
		$ingredientsTable.append($lastRow);

		$columnRight.append($ingredientsHeader).append($ingredientsTable);
		$(this.dishdesc).append($columnRight);

		// Get the preparation instructions and place it under the two previous columns
		var $fullColumn = $('<div/>').addClass('col-md-12 prepText');
		var $dishPreparation = $('<p/>').html(dish.description);
		var $prepHeader = $('<h3/>').html('Preparation');
		$fullColumn.append($prepHeader).append($dishPreparation);
		$(this.dishprep).append($fullColumn);

	}


	$("#people").attr('value', model.getNumberOfGuests());



	// Update view with new model values
	this.update = function(obj) {
		$(".ingredients").empty();
		$(".prepText").remove();
		if($.isNumeric(obj)) { 
			$(".dishOverview").empty();
			this.getDish(obj); 
		}
		this.makeIngredientList(model.getNumberOfGuests());
	}

}