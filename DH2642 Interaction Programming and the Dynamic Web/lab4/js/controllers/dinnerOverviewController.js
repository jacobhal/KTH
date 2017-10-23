var DinnerOverviewController = function(view, model, stateController) {

	view.printRecipeBtn.click(function() {
		stateController.showDinnerPreparationScreen();
	}); 

	view.backButton.click(function() {
		stateController.showSelectDishScreen();
	}); 
}