//PreviewDishController Object Construction
var PreviewDishController = function(view, model, stateController) {
	var fetchDishID = function() {
		$(".dish-link").click(function () {
			var id = $(this).attr('id');
			model.setCurrentDish(id)
			view.update(id);
			stateController.showPreviewDishScreen(id);
		});
	}
	fetchDishID();

	$("#previewDish").bind("DOMSubtreeModified", function () {
		$('#pendingPrice').html(model.getCurrentDishPrice());
		$("#backToSelectDishButton").click(function () {
			stateController.showSelectDishScreen();
		});

		$("#dishConfirm").click(function () {
			var dishBeingViewed = model.getCurrentDish();
			var newID = dishBeingViewed.id;
			model.addDishToMenu(newID);
		});
	});

	$("#dishlist").bind("DOMSubtreeModified", function () {
		fetchDishID();
	});
	
}