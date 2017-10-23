//PreviewDishController Object Construction
var PreviewDishController = function(view, model, stateController) {

	$(document).on("click", ".dish-link", function() {
		var id = $(this).attr('id');
		model.setCurrentDish(id);
		view.update();
		stateController.showPreviewDishScreen();
	});

	$(document).on("click", "#backToSelectDishButton", function() {
		stateController.showSelectDishScreen();
	});

	$(document).on("click", "#dishConfirm", function() {
		var dishBeingViewed = model.getCurrentDish();
		var newID = dishBeingViewed.id;
		model.addDishToMenu(newID);
	});
	
}