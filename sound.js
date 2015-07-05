var start = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_start.wav");
var abort = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_abort.mp3");
var end = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_end.wav");

var playStart = function() {

start.play();
}

//data:audio/x-wave;base64,

var endPlay = function() {

end.play();
}

var abortPlay = function() {

abort.play();
}

var currentSound;
var getCurrentSound = function() {
$.get( "/audience/current-sound", function( datas ) {
currentSound = datas;
});

if (currentSound === "start")
{
	playStart();
}

if (currentSound === "end")
{
	endPlay();
}

if (currentSound === "abort")
{
	abortPlay();
}
}

var getTimer=setInterval( function () {getCurrentSound()}, 500);
