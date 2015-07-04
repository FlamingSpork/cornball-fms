var startMatch = function() {
$.ajax({
	url:"/match/start",
	success: function(datar) {
		//redScore = datar;
	},
	asynch:false
});
}

var stopMatch = function() {
$.ajax({
	url:"/match/stop",
	success: function(datar) {
		//redScore = datar;
	},
	asynch:false
});
}

var teamNumber
var hSchedule = function()
{
	teamNumber = document.getElementById("teamNumber").value;
	window.location.href = "/admin/schedule/" + teamNumber;
}
