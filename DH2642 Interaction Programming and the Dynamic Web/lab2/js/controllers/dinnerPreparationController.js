//DinnerPreparationController Object Construction
var DinnerPreparationController = function(view, model, stateController) {
	view.backButton.click(function() {
		stateController.showSelectDishScreen();
	});
	
}