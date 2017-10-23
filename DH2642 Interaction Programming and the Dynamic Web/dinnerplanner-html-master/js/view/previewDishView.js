var PreviewDishView = function (container,model) {

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishdesc = container.find("#dishdesc");
	this.dishprep = container.find("#dishprep");

	// Get the dish description and ingredients
	var dish = model.getDish(100); // 100 = Meat balls
	var $columnLeft = $('<div/>').addClass('col-md-6');
	var $columnRight = $('<div/>').addClass('col-md-6');

	// Left column
	var $dishName = $('<h3/>').html(dish.name);
	var $dishImg = $('<img/>').attr('src', 'images/' + dish.image);
	// For some reason the description of the dish is also the instructions on how to make it.
	// If you look at the prototype they are suppose be separate, one under the img and one under
	// the header "Preparation". So I made this string as a placeholder.
	var loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in repre";
	var $dishCaption = $('<p/>').html(loremIpsum);
	var $backButton = $('<button/>').addClass('btn btn-default').html("Back to Select Dish");
	$columnLeft.append($dishName).append($dishImg).append($dishCaption).append($backButton);
	$(this.dishdesc).append($columnLeft);

	// Right column
	var ingredients = dish.ingredients;
	var $ingredientsHeader = $('<h3/>').html("Ingredients for 4 people");
	var $ingredientsTable = $('<table/>').addClass('table')

	var totalPrice = 0;
	for (var i = 0; i < ingredients.length; i++) {
		var $mesure = $('<td/>').html(ingredients[i].quantity + " " + ingredients[i].unit);
		var $name = $('<td/>').html(ingredients[i].name);
		var $price = $('<td/>').html('SEK ' + ingredients[i].price);
		totalPrice += ingredients[i].price;
		var $row = $('<tr/>').append($mesure).append($name).append($price);
		$ingredientsTable.append($row);
	}

	var $totalPrice = $('<td/>').html('SEK ' + totalPrice);
	var $confirmButton = $('<button/>').addClass('btn btn-default').html('Confirm dish');
	var $buttonTd = $('<td/>').html($confirmButton);
	var $lastRow = $('<tr/>').append($buttonTd).append('<td/>').append($totalPrice)
	$ingredientsTable.append($lastRow);

	$columnRight.append($ingredientsHeader).append($ingredientsTable);
	$(this.dishdesc).append($columnRight);

	// Get the preparation instructions and place it under the two previous columns
	var $fullColumn = $('<div/>').addClass('col-md-12');
	var $dishPreparation = $('<p/>').html(dish.description);
	var $prepHeader = $('<h3/>').html('Preparation');
	$fullColumn.append($prepHeader).append($dishPreparation);
	$(this.dishprep).append($fullColumn);

	// Update pending price on the menu to the left
	this.pendingPrice = container.find("#pendingPrice");
	$(this.pendingPrice).html(totalPrice);

}