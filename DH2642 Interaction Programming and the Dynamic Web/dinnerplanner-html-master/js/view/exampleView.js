//ExampleView Object constructor
var ExampleView = function (container,model) {

	// Get all the relevant elements of the view (ones that show data
	// and/or ones that responded to interaction)
	this.numberOfGuests = container.find("#numberOfGuests");
	this.plusButton = container.find("#plusGuest");
	this.minusButton = container.find("#minusGuest");

	this.courselist = container.find("#courselist");

	this.numberOfGuests.html(model.getNumberOfGuests());

	
	model.getAllDishes("starter").forEach(function (starter) {
	     $('<div/>', {
	         class: "course",
	         html: starter.name
	     }).appendTo(this.courselist);
	});

	

}