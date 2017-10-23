//DinnerModel Object constructor
var DinnerModel = function() {

	var parent = this;
	
	var dinnerTitle = "";
	var hostName = "";
	var numberOfGuests = 4;
	var selectedMenu = []; // Only contains ID's of selected dishes.
	var observers = [];
	var currentDish = {};
	var currentDishID = -1;
	var currentDishType = 0; // 0 = starter, 1 = main course etc.
	var pendingPrice = 0; // Price of dish that is being viewed but has not been added.

	this.setCurrentDish = function(id, type) {
		currentDishID = id;
		this.getDish(id, function(dish) {
			currentDish = dish;
		});
	}

	this.setCurrentDishType = function(type) {
		currentDishType = type;
	}

	this.setPendingPrice = function(value) {
		pendingPrice = value;
		//notifyObservers({'pendingPrice': value});
	}

	this.getPendingPrice = function() {
		return pendingPrice;
	}

	this.getCurrentDish = function() {
		return currentDish;
	}

	this.getCurrentDishID = function() {
		return currentDishID;
	}

	this.getCurrentDishType = function() {
		return currentDishType;
	}

	// Fucked
	this.getCurrentDishPrice = function() {
		var sum = 0;
		currentDish.ingredients.forEach(ingredient => {
			sum += numberOfGuests*ingredient.price;
		});
		return sum;
	}

	// Add new observer to array
	this.addObserver = function(observer) { 
		observers.push(observer);
		/* Your code here */ 
	} 

	// Call the update method on each of the observers in the array
	// Called every time model is updated
	var notifyObservers = function(obj) { 
		// TODO
		for (var i = 0; i < observers.length; i++) {
			observers[i].update(obj);
		}
		/* Your code here */ 
	}

	this.setNumberOfGuests = function(num) {
		numberOfGuests = num; 
		notifyObservers(); // numberOfGuests changed
	}

	//Set the title for this dinner party
	this.setDinnerTitle = function(title) {
		dinnerTitle = title; 
		notifyObservers(); // dinnerTitle changed
	}

	//Set the hosts name for this dinner party
	this.setHostName = function(name) {
		hostName = name; 
		notifyObservers(); // numberOfGuests changed
	}

	// should return 
	this.getNumberOfGuests = function() {
		return numberOfGuests;
	}

	//Returns the dish that is on the menu for selected type 
	this.getSelectedDish = function(type) {
		var fullMenu = this.getFullMenu();
		return fullMenu.find((dish) => {
			dish.type == type;
		});
	}

	//Returns all the dishes on the menu.
	this.getFullMenu = function() {
		return {};
		// Filter out dishes with ID's that are in selectedMenu
		
	}

	//Adds the passed dish to the menu. If the dish of that type already exists on the menu
	//it is removed from the menu and the new one added.
	this.addDishToMenu = function(id) {

		var fullMenu = this.getFullMenu();
		var dishToAdd = {};
		// Get the dish from API
		this.getDish(id, function(dish) {
			dishToAdd = dish;
			for (var i = 0; i < fullMenu.length; i++) {
				if (i == parent.getCurrentDishType()) {
					// Delete the id of the dish that was found with the same type.
					parent.removeDishFromMenu(fullMenu[i].id);
					selectedMenu[i] = dishToAdd;
					return;
				}
			}
			selectedMenu[parent.getCurrentDishType()] = dishToAdd;
			alert(selectedMenu);
			notifyObservers(parent.getFullMenu()); 
		});	
	}

	//Removes dish from menu
	this.removeDishFromMenu = function(id) {
		var index = -1;
		for (var i = 0; i < selectedMenu.length; i++) {
			if (selectedMenu[i].id == id ) {
				index = i;
			}
		}
		return selectedMenu.splice(index, 1);
		notifyObservers();
	}

	//Returns all ingredients for all the dishes on the menu.
	this.getAllIngredients = function() {
		var fullMenu = this.getFullMenu();
		// Concat all arrays of ingredients into one big array of objects.
		var allIngredients = fullMenu.forEach((dish) => {
			allIngredients.concat(dish.ingredients);
		});
		return allIngredients;
	}

	//Returns the total price of the menu (all the ingredients multiplied by number of guests).
	this.getTotalMenuPrice = function() {
		var fullMenu = this.getFullMenu();
		var sum = 0;
		for (var i = 0; i < fullMenu.length; i++) {
			fullMenu[i].ingredients.forEach((ingredient) => {
				sum += numberOfGuests*ingredient.price;
			});
		}
		return sum;
	}

	// Returns the instructions for the dish with the given id.
	this.getDishInstructions = function(id, cb) {
		var url = 'https://spoonacular-recipe-food-nutrition-v1.p.mashape.com/recipes/' + id + '/analyzedInstructions?stepBreakdown=false';
		$.ajax({
			url: url,
			headers: {
				'X-Mashape-Key': 'Qu9grxVNWpmshA4Kl9pTwyiJxVGUp1lKzrZjsnghQMkFkfA4LB'
			},
			success: function(data) {
				return cb(data);
			},
			error: function(data) {
			 	console.log("Error performing request");
			}
		});
	}

	//function that returns all dishes of specific type (i.e. "starter", "main dish" or "dessert")
	//you can use the filter argument to filter out the dish by name or ingredient (use for search)
	//if you don't pass any filter all the dishes will be returned. 'instructionsRequired' is always
	//set to true.
	this.getAllDishes = function (type, filter, cb) {
		var url = "";
		switch(type) {
			case "0": 
				var typeQuery = "starter";
				break;
			case "1": 
				var typeQuery = "main course";
				break;
			case "2": 
				var typeQuery = "dessert";
				break;
		}
		if(!filter) {
			url = 'https://spoonacular-recipe-food-nutrition-v1.p.mashape.com/recipes/searchComplex?type=' + typeQuery + '&instructionsRequired=true';
		} else {
			// TODO: Check if dish name matches filter
			url = 'https://spoonacular-recipe-food-nutrition-v1.p.mashape.com/recipes/searchComplex?type=' + typeQuery + '&query=' + filter + '&instructionsRequired=true';
		}

		$.ajax({
			url: url,
			headers: {
				'X-Mashape-Key': 'Qu9grxVNWpmshA4Kl9pTwyiJxVGUp1lKzrZjsnghQMkFkfA4LB'
			},
			success: function(data) {
				return cb(data);
			},
			error: function(data) {
			 	console.log("Error performing request");
			}
		});
	}

	//function that returns a dish of specific ID
	this.getDish = function (id, cb) {
		$.ajax({
			url: 'https://spoonacular-recipe-food-nutrition-v1.p.mashape.com/recipes/' + id + '/information',
			headers: {
				'X-Mashape-Key': 'Qu9grxVNWpmshA4Kl9pTwyiJxVGUp1lKzrZjsnghQMkFkfA4LB'
			},
			success: function(data) {
				return cb(data);
			},
			error: function(data) {
			 	console.log("Error performing request");
			}
		});
	}

}