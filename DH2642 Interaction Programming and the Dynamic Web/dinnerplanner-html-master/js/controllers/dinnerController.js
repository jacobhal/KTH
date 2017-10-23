//DinnerController Object Construction
var DinnerController = function(container, model, view) {
	// ------------------TEST------------------
	// Decrease guests
	$("#minusGuest").click(function() {
		var guests = model.getNumberOfGuests();
		model.setNumberOfGuests(guests - 1);
		$('#numberOfGuests').html(model.getNumberOfGuests());
	});

	// Increase guests
	$("#plusGuest").click(function() {
		var guests = model.getNumberOfGuests();
		model.setNumberOfGuests(guests + 1);
		$('#numberOfGuests').html(model.getNumberOfGuests());
	});
	// -----------------------------------------


	$("input#people").change(function() {
		model.setNumberOfGuests($(this).val());
	});
}