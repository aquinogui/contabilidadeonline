$(document).ready(function(){
	$('#hamburger').click(function(){
		$(this).toggleClass('open');
	});
});

$("#hamburger").click(function() {
  $(this).toggleClass("on");
  $("#menu").slideToggle();
});