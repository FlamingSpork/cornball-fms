var playStart = function() {
var start = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_start.wav");
start.play();
}

//data:audio/x-wave;base64,

var endPlay = function() {
var end = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_end.wav");
end.play();
}

var abortPlay = function() {
var abort = new Audio("https://github.com/Team254/cheesy-arena/raw/master/static/audio/match_abort.mp3");
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
