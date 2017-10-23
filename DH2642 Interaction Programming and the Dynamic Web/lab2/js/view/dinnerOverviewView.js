var DinnerOverviewView = function (container,model) {
	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.secondNav = container.find("#dinnerOverviewNav");
	this.dinnerOverview = container.find("#dinnerOverviewContent");

	// TODO: WHY THE FUCK DOES THIS NOT WORK WHEN PUT AT END OF FILE?!?
	// Update view with new model values
	this.update = function(obj) {
		$(this.dinnerOverview).find('*').not('#printRecipeBtn').remove();
		this.updateMenu();
	}


	var $header = $('<h2/>').html('My Dinner: 4 people').addClass('pull-left');
	var $backButton = $('<a/>').html('Go back and edit dinner').addClass('pull-right').attr('href', '#').attr('id', 'backButton').addClass('btn').addClass('btn-default');

	var $printRecipeBtn = $('<a/>').html('Print Full Recipe').attr('id', 'printRecipeBtn').addClass('btn').addClass('btn-default').attr('href', '#');

	this.printRecipeBtn = $printRecipeBtn;
	this.backButton = $backButton

	var parent = this;
	
	$(this.secondNav).append($header);
	$(this.secondNav).append($backButton);

	// Add dishes for testing

	this.updateMenu = function() {
		var menu = model.getFullMenu();
		var finalPrice = 0;
		console.log(menu);
		console.log(model.getTotalMenuPrice());

		for (var i = 0; i < menu.length; i++) {
			var $column = $('<div/>').addClass('col-sm-3');
			var $thumbnail = $('<div/>').addClass('thumbnail');

			var $img = $('<img/>').attr('src', 'images/' + menu[i].image);
			var $caption = $('<div/>').addClass('caption');

			var $h3 = $('<h5/>').html("<a href='previewDish.html?id=" + menu[i].id + "'>" + menu[i].name + "</a>");


			$caption.append($h3);

			$thumbnail.append($img);
			$thumbnail.append($caption);

			var ingredients = menu[i].ingredients;
			var totalPrice = 0;

			// Calculate total price
			for (var j = 0; j < ingredients.length; j++) {
				totalPrice += ingredients[j].price;
			}

			finalPrice += totalPrice;

			var $p = $('<p/>').html(totalPrice*model.getNumberOfGuests() + ' SEK');
			$thumbnail.append($p);

			$column.append($thumbnail);

			$(this.dinnerOverview).append($column);

		}

		var $span = $('<span/>').html('<b>Total:</b> <br>' + finalPrice*model.getNumberOfGuests() + ' SEK').css({"margin-top":"50px", "display":"inline-block"});

		var $hr = $('<hr/>').css({'height':'2px', 'width':'100%', 'background-color':'black'});

		$(this.dinnerOverview).append($span);
		$(this.dinnerOverview).append($hr);
		$(this.dinnerOverview).append($printRecipeBtn);

	}
	$(this.dinnerOverview).append($printRecipeBtn);

}