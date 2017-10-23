//StateController Object Construction
var StateController = function() {
	var $selectDish 		= $('#selectDish');
	var $previewDish 		= $('#previewDish');
	var $dinnerOverview 	= $('#dinnerOverview');
	var $dinnerPreparation  = $('#dinnerPreparation');
	var $sidebar 			= $('#sidebar');
	var $navbarMain 		= $('#navbarMain');
	var $navbarHome 		= $('#navbarHome');
	var $jumbo 				= $('#jumbo');
	var $bg					= $('#bg');

	this.showSelectDishScreen = function() {
		this.hideAll();
		$navbarMain.show();
		$selectDish.show();
		$sidebar.show();
		$('#pendingPrice').html('0.00');

	};

	this.showPreviewDishScreen = function(id) {
		this.hideAll();
		$navbarMain.show();
		$previewDish.show();
		$sidebar.show();
	};

	this.showDinnerOverviewScreen = function() {
		this.hideAll();
		$navbarMain.show();
		$dinnerOverview.show();
	};

	this.showDinnerPreparationScreen = function() {
		this.hideAll();
		$navbarMain.show();
		$dinnerPreparation.show();
	};

	this.showHomeScreen = function() {
		this.hideAll();
		$navbarHome.show();
		$jumbo.show();
		$bg.show();
	};

	this.hideAll = function() {
		$selectDish.hide();
		$previewDish.hide();
		$dinnerOverview.hide();
		$dinnerPreparation.hide();
		$sidebar.hide();
		$navbarMain.hide();
		$navbarHome.hide();
		$jumbo.hide();
		$bg.hide();
	};
	
}