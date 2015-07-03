var redInc = function() {
$.get( "/score/red/inc", function( datar ) {
document.getElementById("redscore").innerHTML = datar;
window.datar = datar;
});
}

var redGet = function() {
$.get( "/score/red/get", function( datar ) {
document.getElementById("redscore").innerHTML = datar;
});
}


var blueInc = function() {
$.get( "/score/blue/inc", function( datab ) {
document.getElementById("bluescore").innerHTML = datab;
window.datab = datab;
});
}

var blueGet = function() {
$.get( "/score/blue/get", function( datab ) {
document.getElementById("bluescore").innerHTML = datab;
});
}

var yellowInc = function() {
$.get( "/score/yellow/inc", function( datay ) {
document.getElementById("yellowscore").innerHTML = datay;
});
}

var yellowGet = function() {
$.get( "/score/yellow/get", function( datay ) {
document.getElementById("yellowscore").innerHTML = datay;
});
}

var greenInc = function() {
$.get( "/score/green/inc", function( datag ) {
document.getElementById("greenscore").innerHTML = datag;
});
}

var greenGet = function() {
$.get( "/score/green/get", function( datag ) {
document.getElementById("greenscore").innerHTML = datag;
});
}

var rTimer=setInterval( function () {redGet()}, 500);
var bTimer=setInterval( function () {blueGet()}, 500);
var yTimer=setInterval( function () {yellowGet()}, 500);
var gTimer=setInterval( function () {greenGet()}, 500);
