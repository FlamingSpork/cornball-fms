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

var teamNumber;
var hSchedule = function()
{
	teamNumber = document.getElementById("teamNumber").value;
	window.location.href = "/admin/schedule/" + teamNumber;
}

var matchNumber;
var cScoring = function()
{
	matchNumber = parseInt(document.getElementById("matchNumber").value) - 1;
	window.location.href = "/match/scoring.html?match-number=" + matchNumber;
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

var timer;
var timerGet = function() {
$.ajax({
	url:"/audience/timer",
	success: function(datat) {
		timer = datat;
	},
	asynch:false
});
document.getElementById("timer").innerHTML = timer;
}

var matchNumber;
var matchGet = function() {
$.ajax({
	url:"/audience/match-number",
	success: function(datam) {
		matchNumber = datam;
	},
	asynch:false
});
document.getElementById("match-number").innerHTML = matchNumber;
}

var tTimer=setInterval( function () {timerGet()}, 500);
var mTimer=setInterval( function () {matchGet()}, 1000);
