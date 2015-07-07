var redScore;
var redGet = function() {
$.ajax({
	url:"/score/red/get",
	success: function(datar) {
		redScore = datar;
	},
	asynch:false
});
document.getElementById("red-score").innerHTML = redScore;
}

var blueScore;
var blueGet = function() {
$.ajax({
	url:"/score/blue/get",
	success: function(datab) {
		blueScore = datab;
	},
	asynch:false
});
document.getElementById("blue-score").innerHTML = blueScore;
}

var yellowScore;
var yellowGet = function() {
$.ajax({
	url:"/score/yellow/get",
	success: function(datay) {
		yellowScore = datay;
	},
	asynch:false
});
document.getElementById("yellow-score").innerHTML = yellowScore;
}

var greenScore;
var greenGet = function() {
$.ajax({
	url:"/score/green/get",
	success: function(datag) {
		greenScore = datag;
	},
	asynch:false
});
document.getElementById("green-score").innerHTML = greenScore;
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
document.getElementById("timer-display").innerHTML = timer;
}

var finalScoresHTML;
var finalScoresGet = function() {
$.ajax({
	url:"/match/final-scores",
	success: function(datas) {
		finalScoresHTML = datas;
	},
	asynch:false
});
if (finalScoresHTML)
{
	document.getElementById("final-scores").style.display = "block";
	document.getElementById("final-scores").innerHTML = finalScoresHTML;
}


if (finalScoresHTML === "")
{
	document.getElementById("final-scores").style.display = "none";
	document.getElementById("final-scores").innerHTML = "";
	//console.log("Setting to no display.");
}

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

var rTimer=setInterval( function () {redGet()}, 500);
var bTimer=setInterval( function () {blueGet()}, 500);
var yTimer=setInterval( function () {yellowGet()}, 500);
var gTimer=setInterval( function () {greenGet()}, 500);
var tTimer=setInterval( function () {timerGet()}, 500);
var sTimer=setInterval( function () {finalScoresGet()}, 1000);
var mTimer=setInterval( function () {matchGet()}, 1000);
