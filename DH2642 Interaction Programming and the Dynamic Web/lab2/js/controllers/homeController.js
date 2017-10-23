//HomeController Object Construction
var HomeController = function(model, stateController) {

	$('#newDinnerButton').click(function () {
		stateController.showSelectDishScreen();
	});

	$('.navbar-brand').click(function () {
		stateController.showHomeScreen();
	});
	
}