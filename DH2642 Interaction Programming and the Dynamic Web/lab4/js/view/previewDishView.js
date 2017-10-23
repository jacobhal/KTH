var PreviewDishView = function (container,model) {
	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishdesc = container.find("#dishdesc");
	this.dishprep = container.find("#dishprep");

	var $columnLeft = $('<div/>').addClass('col-md-6').addClass('dishOverview');
	var $columnRight = $('<div/>').addClass('col-md-6').addClass('ingredients');

	this.showLoadingTextIngredients = function() {
		var $loadingText = $('<h2/>').html("Loading...");
		$columnRight.append($loadingText);
	}

	this.showLoadingTextPreparation = function() {
		var $loadingText = $('<h2/>').html("Loading...");
		$(this.dishprep).append($loadingText);
	}

	// Right column (Ingredient list)
	this.makeIngredientsAndPicture = function(nrOfGuests, id) {
		this.showLoadingTextIngredients();
		model.getDish(model.getCurrentDishID(), function(data) {
			// remove loading text
			$columnRight.empty();
			// Picture and description
			var $dishName = $('<h3/>').html(data['title']);
			var $dishImg = $('<img/>').attr('src', data['image']).css({"width":"100%", "height":"200px", "display":"block", "margin":"0 auto"});
			var loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in repre";
 			var $dishCaption = $('<p/>').html(loremIpsum);
			var $backButton = $('<a/>').addClass('btn btn-default').html("Back to Select Dish").attr('href', '#').attr('id', 'backToSelectDishButton');
			$columnLeft.append($dishName).append($dishImg).append($dishCaption).append($backButton);
			$(this.dishdesc).append($columnLeft);

			// Ingredient list
			var ingredients = data['extendedIngredients'];

			// Table and table header
			var $ingredientsHeader = $('<h3/>').html("Ingredients for " + nrOfGuests + " people").attr('id', 'ingredientsHeader');
			var $ingredientsTable = $('<table/>').addClass('table');
			var totalPrice = 0;

			for(var i = 0; i < ingredients.length; i++) {
				var $mesure = $('<td/>').html(ingredients[i].amount*nrOfGuests + " " + ingredients[i].unitShort);
				var $name = $('<td/>').html(ingredients[i].name);
				var $price = $('<td/>').html('SEK ' + ingredients[i].amount*nrOfGuests);
				totalPrice += ingredients[i].amount*nrOfGuests;
				var $row = $('<tr/>').append($mesure).append($name).append($price);
				$ingredientsTable.append($row);
			}
			var $totalPrice = $('<td/>').html('SEK ' + totalPrice);
			var $confirmButton = $('<button/>').addClass('btn btn-default').attr('id', 'dishConfirm').html('Confirm dish');
			var $buttonTd = $('<td/>').html($confirmButton);
			var $priceElement = $($totalPrice).attr('id', 'totalPrice');
			var $lastRow = $('<tr/>').append($buttonTd).append('<td/>').append($priceElement);
			$ingredientsTable.append($lastRow);
			$columnRight.append($ingredientsHeader).append($ingredientsTable);
			$(this.dishdesc).append($columnRight);
			model.setPendingPrice(totalPrice);
		});	
	}

	this.makePreparationInstructions = function() {
		this.showLoadingTextPreparation();
		model.getDishInstructions(model.getCurrentDishID(), function(data) {
			// remove loading text
			$(this.dishprep).empty();
			var $fullColumn = $('<div/>').addClass('col-md-12 prepText');
			var $prepHeader = $('<h3/>').html('Preparation');
			$fullColumn.append($prepHeader);
			// var dish means 1 thing that you have to cook that is part of the whole *actual* dish.
			// for example, if you have to make a sauce with the dish
			for(var i = 0; i < data.length; i++) {
				//console.log(i);
				var $stepList = $('<ol/>');
				var cookingSteps = data[i]['steps'];
				//console.log(cookingSteps);

				for(var j = 1; j < cookingSteps.length; j += 2) {
					// Skip every other step since API is fucking stupid
					var $li = $('<li/>').html(cookingSteps[j].step);
					$($stepList).append($li);
				}
				if (data[i].name != "") {
					$fullColumn.append('<h3>' + data[i].name + '<h3/>');
				}
				$fullColumn.append($stepList);
			}
			$(this.dishprep).append($fullColumn);
		});
	}

	$("#people").attr('value', model.getNumberOfGuests());

	// Update view with new model values
	this.update = function(id) {
		$(".ingredients").empty();
		$(".prepText").remove();
		$(".dishOverview").empty();
		this.makeIngredientsAndPicture(model.getNumberOfGuests());
		this.makePreparationInstructions();
		
	}

}