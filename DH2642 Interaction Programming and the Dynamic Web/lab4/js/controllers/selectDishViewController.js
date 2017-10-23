//SelectDishViewController Object Construction
var SelectDishViewController = function(view, model, stateController) {

	view.dishSelect.change(function() {
		view.update($(this).val());
		model.setCurrentDishType($(this).val());
		
	});

	view.dishSearch.submit(function(e) {
		e.preventDefault();
		view.update($(this));
	});

}