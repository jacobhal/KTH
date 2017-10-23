$(function() {
	//We instantiate our model
	var model = new DinnerModel();

	//And create the needed controllers and views
	
	// Views
	var selectDishView 	= new SelectDishView($("#selectDish"), model);
	var previewDishView = new PreviewDishView($("#previewDish"), model);
	var sidebarView 	= new SidebarView($("body"), model);
	var dinnerOverviewView 	  = new DinnerOverviewView($("#dinnerOverview"), model);
	var dinnerPreparationView = new DinnerPreparationView($("#dinnerPreparation"), model);

	// Controllers
	var stateController 		 	= new StateController();
	var homeController 				= new HomeController(model, stateController);
	var dinnerPreparationController = new DinnerOverviewController(dinnerOverviewView, model, stateController);
	var selectDishViewController 	= new SelectDishViewController(selectDishView, model, stateController);
	var sidebarViewController 	 	= new SidebarViewController(sidebarView, model, stateController);
	var dinnerPreparationController = new DinnerPreparationController(dinnerPreparationView, model, stateController);
	var previewDishController 		= new PreviewDishController(previewDishView, model, stateController);

	stateController.showHomeScreen();

});