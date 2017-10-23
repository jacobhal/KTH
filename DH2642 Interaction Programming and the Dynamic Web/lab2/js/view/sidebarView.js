var SidebarView = function (container,model) {
	// Add view to observers
	model.addObserver(this);

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.dishlist = container.find("#sidebar");
	
	var $header = $('<h2/>').html('My Dinner');
	var $form = $('<form/>').addClass('form-inline');
	var $formDiv = $('<div/>').addClass('form-group');
	var $formLabel = $('<label/>').attr('for', 'form-group').html('People');
	var $formInput = $('<input/>').addClass('form-control').attr('id', 'people').attr('type', 'number').attr('value', model.getNumberOfGuests()).attr('min', '0');

	var $box1 = $('<div/>').addClass('box1');
	var $box1Name = $('<h4/>').addClass('pull-left').html("Dish Name");
	var $box1Cost = $('<h4/>').addClass('pull-right').html("Cost");

	$formDiv.append($formLabel);
	$formDiv.append($formInput);

	$form.append($formDiv);

	$box1.append($box1Name);
	$box1.append($box1Cost);

	var $box2 = $('<div/>').addClass('box2');
	var $divClear1 = $('<div/>').addClass('clear');
	var $hr = $('<hr>').css({"background-color":"#000", "height":"2px"});
	var $h4finalPrice = $('<h4/>').attr('id', 'finalPrice').addClass('pull-right').html('SEK 0');
	var $divClear2 = $('<div/>').addClass('clear');
	var $a = $('<a/>').addClass("btn").addClass("btn-default").attr('href', "#").attr('id', 'confirmDinnerButton').html("Confirm Dinner");

	var $divPending = $('<div/>').attr('id', 'pending');
	var $h4Pending = $('<h4/>').addClass('pull-left').html('Pending');
	var $h4Price = $('<h4/>').addClass('pull-right').attr('id', 'pendingPrice').html('0.00');
	$divPending.append($h4Pending);
	$divPending.append($h4Price);
	$box2.append($divPending);

	$box2.append($divClear1);
	$box2.append($hr);
	$box2.append($h4finalPrice);
	$box2.append($divClear2);
	$box2.append($a);

	$(this.dishlist).append($header).append($form).append($box1).append($box2);

	this.updatePrice = function(prices, names, totalPrice) {
		$("#finalPrice").html('SEK ' + totalPrice);
		$('.box2').find('.sidebarDish').remove();
		for (var i = 0; i < prices.length; i++) {		
			// TODO: Fetch each dish and display name + price in a pending div
			var $divSidebarDish = $('<div/>').addClass('sidebarDish');
			var $sidebarDishName = $('<h4/>').addClass('pull-left sidebarDishName').html(names[i]);
			var $sidebarDishPrice = $('<h4/>').addClass('pull-right').html(prices[i]);
			$divSidebarDish.append($sidebarDishName).append($sidebarDishPrice);
			$box2.prepend($divSidebarDish);
		} 
		
	}

	// Get all additional elements of the view
	this.peopleInput = container.find("#people");
	this.confirmDinnerButton = container.find("#confirmDinnerButton");

	// Update view with new model values
	this.update = function(obj) {
		var prices = [];
		var names = [];
		if(obj !== undefined) {
			for(var i = 0; i < obj.length; i++) {
				names.push(obj[i].name);
				var ingredients = obj[i].ingredients;
				var dishPrice = 0;
				for (var j = 0; j < ingredients.length; j++) {
					dishPrice += ingredients[j].price;
				}	
				prices.push(dishPrice*model.getNumberOfGuests());
			}
		}
		var totalMenuPrice = model.getTotalMenuPrice();
		this.updatePrice(prices, names, totalMenuPrice);
		if($("#selectDish").is(":visible")) {
			$('#pendingPrice').html('0.00');
		}
	}

}