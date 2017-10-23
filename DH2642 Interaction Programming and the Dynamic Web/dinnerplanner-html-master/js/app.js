$(function() {
	//We instantiate our model
	var model = new DinnerModel();
	
	//And create the needed controllers and views
	
	// Views
	var exampleView = new ExampleView($("#exampleView"), model);
	var previewDishView = new PreviewDishView($("#mainContentPreview"), model);
	var selectDishView = new SelectDishView($("#maincontent"), model);
	

	// Controllers
	var dinnerController = new DinnerController($("#exampleView"), model, exampleView);
	var dinnerController2 = new DinnerController($("#main-content"), model, selectDishView);

});