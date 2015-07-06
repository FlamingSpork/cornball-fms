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

var setCode;
var setAudience = function(num) {
if (num === 0)
{
	setCode = "none";
}
if (num === 1)
{
	setCode = "match-scores";
}
if (num === 2)
{
	setCode = "leaderboard";
}
$.ajax({
	url:"/audience/center-display",
	data: { "set": setCode},
	success: function(datar) {
		//redScore = datar;
	},
	asynch:false
});
}

function doc_keyUp(e)
{
// this would test for whichever key is 40 and the ctrl key at the same time
    if (e.keyCode == 32) {
        // call your function to do the thing
        startMatch();
    }
}
// register the handler 
document.addEventListener('keyup', doc_keyUp, false);

var saveEvent = function() {
$.ajax({
	url:"/admin/save",
	success: function(datar) {
		//redScore = datar;
	},
	asynch:false
});
}
