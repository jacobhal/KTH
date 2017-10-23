//SelectDishViewController Object Construction
var SidebarViewController = function(view, model, stateController) {

	view.peopleInput.on('input', function() {
		model.setNumberOfGuests(view.peopleInput.val());
		view.update(model.getFullMenu());
	});

	view.confirmDinnerButton.click(function() {
		stateController.showDinnerOverviewScreen();
	});
	
}