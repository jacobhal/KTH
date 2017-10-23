var DinnerPreparationView = function (container,model) {
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dinnerPreview = container.find("#dinnerPreview");
	this.secondNav = container.find("#dinnerPreparationNav");

	// header
	var $header = $('<h2/>').html('My Dinner: 4 people').addClass('pull-left');
	var $backButton = $('<a/>').html('Go back and edit dinner').addClass('pull-right').attr('href', '#').attr('id', 'backButton').addClass('btn').addClass('btn-default');
	$(this.secondNav).append($header);
	$(this.secondNav).append($backButton);


	// Placeholder for text under name of the dish.
	var $loremIpsum = $('<p/>').html("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor" +
	"incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation" +
	"ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in repre");
	// This header is always the same
	var $prepHeader = $('<h4/>').html('Preparation');

	// Add dishes for testing
	
	// Load new menu
	this.updateMenu = function() {
		var menu = model.getFullMenu();
		console.log(menu);
		console.log(model.getTotalMenuPrice());

		for (var i = 0; i < menu.length; i++) {
			// One row per dish
			var $row = $('<div/>').addClass('row');
			// Split the row into two columns, 1 for the thumbnail and caption and 
			// the instructions in the other.
			var $columnLeft = $('<div/>').addClass('col-md-6');
			var $columnRight = $('<div/>').addClass('col-md-6');
			// Split the left column into two so it looks good and stacks well
			var $columnLeftImg = $('<div/>').addClass('col-md-3');
			var $columnLeftText = $('<div/>').addClass('col-md-9');

			// Get all needed info from the model
			var $dishImg = $('<img/>').attr('src', 'images/' + menu[i].image);
			var $dishName = $('<h3/>').html(menu[i].name);
			var $dishPreparation = $('<p/>').html(menu[i].description);
			// Append everything in the left column.
			$columnLeftImg.append($dishImg);
			$columnLeftText.append($dishName);
			$loremIpsum.clone().appendTo($columnLeftText); // have to clone and appendTo since it will be moved by regular append.
			$columnLeft.append($columnLeftImg).append($columnLeftText);
			// Append everything in the right column.
			$prepHeader.clone().appendTo($columnRight);
			$columnRight.append($dishPreparation);
			// Append the two columns to the row and then the row to the container.
			$row.append($columnLeft).append($columnRight);
			$(this.dinnerPreview).append($row);
		}
	}

	this.backButton = container.find("#backButton");

	// Update view with new model values
	this.update = function(obj) {
		this.dinnerPreview.empty();
		this.updateMenu();
	}
}