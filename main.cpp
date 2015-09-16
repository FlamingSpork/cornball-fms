/*  Maize Craze Field Management System
    by FlamingSpork, FRC team 3003
*/
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Admin.h"

class fms : public cppcms::application {
public:
    fms(cppcms::service &srv) :
        cppcms::application(srv)
    {

        dispatcher().assign("/jquery.min.js",&fms::jQuery,this);
        mapper().assign("jquery.min.js","/jquery.min.js");

        //Blue Scoring code
        dispatcher().assign("/score/blue/inc",&fms::blueInc,this);
        mapper().assign("blueinc","/score/blue/inc");
        dispatcher().assign("/score/blue/get",&fms::blueGet,this);
        mapper().assign("blueget","/score/blue/get");
        dispatcher().assign("/score/blue/dec",&fms::blueDec,this);
        mapper().assign("bluedec","/score/blue/dec");

        //Red Scoring code
        dispatcher().assign("/score/red/inc",&fms::redInc,this);
        mapper().assign("redinc","/score/red/inc");
        dispatcher().assign("/score/red/get",&fms::redGet,this);
        mapper().assign("redget","/score/red/get");
        dispatcher().assign("/score/red/dec",&fms::redDec,this);
        mapper().assign("reddec","/score/red/dec");

        //Yellow Scoring Code
        dispatcher().assign("/score/yellow/inc",&fms::yellowInc,this);
        mapper().assign("yellowinc","/score/yellow/inc");
        dispatcher().assign("/score/yellow/get",&fms::yellowGet,this);
        mapper().assign("yellowget","/score/yellow/get");
        dispatcher().assign("/score/yellow/dec",&fms::yellowDec,this);
        mapper().assign("yellowdec","/score/yellow/dec");

        //Green Scoring Code
        dispatcher().assign("/score/green/inc",&fms::greenInc,this);
        mapper().assign("greeninc","/score/green/inc");
        dispatcher().assign("/score/green/get",&fms::greenGet,this);
        mapper().assign("greenget","/score/green/get");
        dispatcher().assign("/score/green/dec",&fms::greenDec,this);
        mapper().assign("greendec","/score/green/dec");



        dispatcher().assign("/score/buttons.html",&fms::buttons,this);
        mapper().assign("buttons.html","/score/buttons.html");

        dispatcher().assign("/score/buttons.js",&fms::buttonsjs,this);
        mapper().assign("buttons.js","/score/buttons.js");
        dispatcher().assign("/score/overlay.png",&fms::overlay,this);
        mapper().assign("overlay.png","/score/overlay.png");

        dispatcher().assign("",&fms::root,this);
        mapper().assign("");

        mapper().root("/server");

        dispatcher().assign("/audience/logo.png",&fms::logopng,this);
        mapper().assign("logo.png","/audience/logo.png");
        dispatcher().assign("/audience/audience.html",&fms::audiencehtml,this);
        mapper().assign("audience.html","/audience/audience.html");
        dispatcher().assign("/audience/audience.js",&fms::audiencejs,this);
        mapper().assign("audience.js","/audience/audience.js");
        dispatcher().assign("/audience/timer",&fms::getTimer,this);
        mapper().assign("timer","/audience/timer");
        dispatcher().assign("/audience/sound.html",&fms::soundhtml,this);
        mapper().assign("sound.html","/audience/sound.html");
        dispatcher().assign("/audience/sound.js",&fms::soundjs,this);
        mapper().assign("sound.js","/audience/sound.js");
        dispatcher().assign("/audience/current-sound",&fms::currentSound,this);
        mapper().assign("current-sound","/audience/current-sound");
        dispatcher().assign("/audience/leaderboard",&fms::leaderboard,this);
        mapper().assign("leaderboard","/audience/leaderboard");
        dispatcher().assign("/audience/center-display",&fms::audienceCenter,this);
        mapper().assign("center-display","/audience/center-display");

        dispatcher().assign("/audience/match-number",&fms::matchNumber,this);
        mapper().assign("match-number","/audience/match-number");

        dispatcher().assign("/admin/teamlist.html",&fms::teamlist,this);
        mapper().assign("teamlist.html", "/admin/teamlist.html");
        dispatcher().assign("/admin/pdfGen.js",&fms::pdfGen,this);
        mapper().assign("pdfGen.js", "/admin/pdfGen.js");
        dispatcher().assign("/admin/schedule.html",&fms::printSchedule,this);
        mapper().assign("schedule.html", "/admin/schedule.html");
        dispatcher().assign("/admin/schedule/(\\d+)",&fms::printHighlightedSchedule,this,1);
        mapper().assign("schedule","/admin/schedule/{1}");
        dispatcher().assign("/admin/control-center.html",&fms::controlCenter,this);
        mapper().assign("control-center.html","/admin/control-center.html");
        dispatcher().assign("/admin/control-center.js",&fms::controlCenterjs,this);
        mapper().assign("control-center.js","/admin/control-center.js");
        dispatcher().assign("/admin/save",&fms::saveEventFile,this);
        mapper().assign("save","/admin/save");

        dispatcher().assign("/match/start",&fms::startMatchTimer,this);
        mapper().assign("matchstart","/match/start");
        dispatcher().assign("/match/scoring.html",&fms::matchScoring,this);
        mapper().assign("matchscoring","/match/scoring.html");
        dispatcher().assign("/match/final-scores",&fms::dispFinalScores,this);
        mapper().assign("final-scores","/match/final-scores");
        dispatcher().assign("/match/stop",&fms::stopMatchTimer,this);
        mapper().assign("matchstop","/match/stop");

        fms::redCounter = 0;
        fms::blueCounter = 0;
        fms::yellowCounter = 0;
        fms::greenCounter = 0;

    }
    //virtual void main(std::string url);

    void root();
    void jQuery();

    void blueInc();
    void blueGet();
    void blueDec();

    void redInc();
    void redGet();
    void redDec();

    void yellowInc();
    void yellowGet();
    void yellowDec();

    void greenInc();
    void greenGet();
    void greenDec();

    void buttons();
    void buttonsjs();
    void overlay();

    void logopng();
    void audiencehtml();
    void audiencejs();
    void getTimer();
    void soundhtml();
    void soundjs();
    void currentSound();
    void leaderboard();
    void audienceCenter();

    void matchNumber();

    void teamlist();
    void pdfGen();
    void printSchedule();
    void printHighlightedSchedule(std::string num);
    void controlCenter();
    void controlCenterjs();
    void saveEventFile();

    void startMatchTimer();
    void matchScoring();
    void dispFinalScores();
    void stopMatchTimer();


private:
    int redCounter;
    int blueCounter;
    int yellowCounter;
    int greenCounter;
};

Admin instance;
void runFMS()
{
	instance.initFMS();
}
int main(int argc,char ** argv)
{

    runFMS();
    std::cout<<"FMS is Ready!"<< std::endl;
    try {
        //Initial functions
        //my_hello_world::initFMS();
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<fms>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
        std::cerr<<"Launching webserver portion failed."<<std::endl;
    }
    std::cout<<"Exiting now..."<< std::endl;
}


void fms::root()
{
    response().out()<<
    "<html>\n"
    "<body>\n"
    "</body>\n"
    "</html>\n";
}

//TODO: Move all inc and dec functions into one.
//http://<ip>:8080/score/update?colour=<colour>&change=<+|->
void fms::redInc()
{
    redCounter++;
    response().out() << redCounter;
}

void fms::redGet()
{
    response().out() << redCounter;
}

void fms::redDec()
{
    redCounter--;
    response().out() << redCounter;
}

void fms::blueInc()
{
    blueCounter++;
    response().out() << blueCounter;
}

void fms::blueGet()
{
    response().out() << blueCounter;
}

void fms::blueDec()
{
    blueCounter--;
    response().out() << blueCounter;
}

void fms::yellowInc()
{
    yellowCounter++;
    response().out() << yellowCounter;
}

void fms::yellowGet()
{
    response().out() << yellowCounter;
}

void fms::yellowDec()
{
    yellowCounter--;
    response().out() << yellowCounter;
}

void fms::greenInc()
{
    greenCounter++;
    response().out() << greenCounter;
}

void fms::greenGet()
{
    response().out() << greenCounter;
}

void fms::greenDec()
{
    greenCounter--;
    response().out() << greenCounter;
}
void fms::buttons()
{
    std::ifstream file ("buttons.html");
    response().out() << file.rdbuf();
}

void fms::buttonsjs()
{
    std::ifstream file ("buttons.js");
    response().out() << file.rdbuf();
}

void fms::logopng()
{
    std::ifstream file ("MaizeLogo.png");
    response().content_type("image/png");
    response().out() << file.rdbuf();
}

void fms::audiencehtml()
{
    std::ifstream file ("audience.html");
    response().out() << file.rdbuf();
}

void fms::audiencejs()
{
    std::ifstream file ("audience.js");
    response().out() << file.rdbuf();
}

void fms::teamlist()
{
    //Use the array filled from teamlistFetchData()
    int l_numTeams, i;
    //char tbl_teamNum [5], tbl_nickname[30], tbl_location[35], tbl_fullName[200];
    //Determine number of teams
    l_numTeams = instance.numTeams;

    //HTML stuff
    response().out() <<
    "<html>\n"
    "<head>\n"
    "<style>\n"
    "table, th, td {  border: 1px solid black;  border-collapse: collapse; }\n"
    "</style>\n"
    "<body>\n"
    "<script src=\"pdfGen.js\"></script>\n"
    "<script src=\"/jquery.min.js\"></script>\n"
    "<p><a href=\"#\" onclick=\"return xepOnline.Formatter.Format('list');\">PDF/Printable Version</a>"
    "<div id=\"list\">\n"
    "<table style=\"border: 1px solid black;\">\n"
    "<tr>\n"
    "<th>Team Number</th>\n"
    "<th>Team Name</th>\n"
    "<th>Location</th>\n"
    "<th>Full Team Name</th>\n"
    "</tr>\n";
    //Include PDF generation javascript
    for ( i=0; i < l_numTeams; i++)
    {
    	//tbl_teamNum = instance.teamArray[i].TeamNumber;
        response().out() <<
        "<tr>"
        "<th>"
        "<a href=\"http://www.thebluealliance.com/team/"
        << instance.teamArray[i].TeamNumber <<
		"\">"
        << instance.teamArray[i].TeamNumber<<
		"</a></th>\n"
		"<th>"
		<< instance.teamArray[i].nickname <<
		"</th>\n"
		"<th>"
		<< instance.teamArray[i].location <<
		"</th>\n"
		"<th>"
		<< instance.teamArray[i].fullName <<
		"</th>\n"
		"</tr>\n";
        //Team information from the array (i is array index)
    }
}

void fms::pdfGen()
{
	std::ifstream filein("pdfGen.js");
	response().out() << filein.rdbuf();
}

void fms::printSchedule()
{
	int l_numMatches, i;
	l_numMatches = instance.numPractice + instance.numElim + instance.numQual + instance.numFinal;
	response().out() <<
	   "<html>\n"
	    "<head>\n"
	    "<style>\n"
	    "table, th, td {  border: 1px solid black;  border-collapse: collapse; }\n"
	    "</style>\n"
	    "<body>\n"
	    "<script src=\"pdfGen.js\"></script>\n"
	    "<script src=\"/jquery.min.js\"></script>\n"
	    "<p><a href=\"#\" onclick=\"return xepOnline.Formatter.Format('list');\">PDF/Printable Version</a>"
	    "<div id=\"list\">\n"
	    "<table style=\"border: 1px solid black;\">\n"
	    "<tr>\n"
		"<th>Match Number</th>\n"
		"<th>Red Team</th>\n"
		"<th>Blue Team</th>\n"
		"<th>Yellow Team</th>\n"
		"<th>Green Team</th>\n"
		"</tr>\n";
	for (i=0; i<l_numMatches; i++)
	{
		if (i == 0)
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Practice Matches</th>\n"
					"</tr>\n";
		}

		if (i == instance.numPractice)
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Qualification Matches</th>\n"
					"</tr>\n";
		}

		if (i == (instance.numPractice + instance.numQual))
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Elimination Matches</th>\n"
					"</tr>\n";
		}

		if (i == (instance.numPractice + instance.numQual + instance.numElim))
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Final Matches</th>\n"
					"</tr>\n";
		}

		response().out() <<
					"<tr>"
					"<th>"
					<< i +1 <<
					"</th>\n"
					"<th>"
					<< instance.matchArray[i].TeamNumber[0] <<
					"</th>\n"
					"<th>"
					<< instance.matchArray[i].TeamNumber[1] <<
					"</th>\n"
					"<th>"
					<< instance.matchArray[i].TeamNumber[2] <<
					"</th>\n"
					"<th>"
					<< instance.matchArray[i].TeamNumber[3] <<
					"</th>\n";
		}
}

void fms::printHighlightedSchedule(std::string num)
{
	int l_numMatches, i, htNumber;
	htNumber = atoi(num.c_str());
	l_numMatches = instance.numPractice + instance.numElim + instance.numQual + instance.numFinal;
	response().out() <<
	   "<html>\n"
	    "<head>\n"
	    "<style>\n"
	    "table, th, td {  border: 1px solid black;  border-collapse: collapse; }\n"
	    "</style>\n"
	    "<body>\n"
	    "<script src=\"/admin/pdfGen.js\"></script>\n"
	    "<script src=\"/jquery.min.js\"></script>\n"
	    "<p><a href=\"#\" onclick=\"return xepOnline.Formatter.Format('list');\">PDF/Printable Version</a>"
	    "<div id=\"list\">\n"
	    "<table style=\"border: 1px solid black;\">\n"
	    "<tr>\n"
		"<th>Match Number</th>\n"
		"<th>Red Team</th>\n"
		"<th>Blue Team</th>\n"
		"<th>Yellow Team</th>\n"
		"<th>Green Team</th>\n"
		"</tr>\n";
	for (i=0; i<l_numMatches; i++)
	{
		if (i == 0)
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Practice Matches</th>\n"
					"</tr>\n";
		}

		if (i == instance.numPractice)
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Qualification Matches</th>\n"
					"</tr>\n";
		}

		if (i == (instance.numPractice + instance.numQual))
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Elimination Matches</th>\n"
					"</tr>\n";
		}

		if (i == (instance.numPractice + instance.numQual + instance.numElim))
		{
			response().out() <<
					"<tr>\n"
					"<th colspan=\"5\" style=\"font-weight: normal;\">Final Matches</th>\n"
					"</tr>\n";
		}

		response().out() <<
					"<tr>"
					"<th>"
					<< i +1 <<
					"</th>\n";
		if (instance.matchArray[i].TeamNumber[0] == htNumber)
		{
			response().out() <<
					"<th style=\"background-color: #B57EDC\">"
					<< instance.matchArray[i].TeamNumber[0] <<
					"</th>\n";
		}
		else
		{
			response().out() <<
					"<th>"
					<< instance.matchArray[i].TeamNumber[0] <<
					"</th>\n";
		}
		if (instance.matchArray[i].TeamNumber[1] == htNumber)
		{
			response().out() <<
					"<th style=\"background-color: #B57EDC\">"
					<< instance.matchArray[i].TeamNumber[1] <<
					"</th>\n";
		}
		else
		{
			response().out() <<
					"<th>"
					<< instance.matchArray[i].TeamNumber[1] <<
					"</th>\n";
		}
		if (instance.matchArray[i].TeamNumber[2] == htNumber)
		{
			response().out() <<
					"<th style=\"background-color: #B57EDC\">"
					<< instance.matchArray[i].TeamNumber[2] <<
					"</th>\n";
		}
		else
		{
			response().out() <<
					"<th>"
					<< instance.matchArray[i].TeamNumber[2] <<
					"</th>\n";
		}
		if (instance.matchArray[i].TeamNumber[3] == htNumber)
		{
			response().out() <<
					"<th style=\"background-color: #B57EDC\">"
					<< instance.matchArray[i].TeamNumber[3] <<
					"</th>\n";
		}
		else
		{
			response().out() <<
			"<th>"
			<< instance.matchArray[i].TeamNumber[3] <<
			"</th>\n";
		}
	}
}

void fms::jQuery()
{
	std::ifstream filein("jquery.min.js");
	response().out() << filein.rdbuf();
}

void fms::getTimer()
{
	int minutes, seconds, totalTime;
	totalTime = instance.getCurrentTimer();
	minutes = totalTime / 60;
	seconds = totalTime - (minutes * 60);
	response().out() <<
			minutes <<
			":";
	if (seconds < 10)
	{
		response().out() <<
				"0" << seconds;
	}
	else
	{
		response().out() << seconds;
	}
}

void fms::startMatchTimer()
{
	if (!instance.isTimerRunning)
	{
	instance.startTimer();
	instance.isMatchOngoing = 1;
	response().out() << "Timer Started.";
	instance.currentSound = "m-start";
	}
	else
	{
		response().out() << "The match timer is already running.";
	}
}

void fms::stopMatchTimer()
{
	if (instance.isTimerRunning)
	{
		instance.isTimerRunning = 0;
		//instance.isMatchOngoing = 0;
		instance.currentSound = "m-abort"; //This is a match abortion.
	}
}

void fms::matchScoring()
{
	std::string red, blue, yellow, green, matchNumberG, matchNumberP;
	bool display = 1, increment=1;
	int matchInt;
	try
	{
		//It took me *far* too long to find how easy this is.
		red = request().post("red");
		blue = request().post("blue");
		yellow = request().post("yellow");
		green = request().post("green");
		matchNumberP = request().post("match-number");
		matchNumberG = request().get("match-number");

		if (!red.empty())
		{
			if (matchNumberP == "")
			{
				matchInt = instance.matchIndex;
			}
			else
			{
				matchInt = atoi(matchNumberP.c_str());
				increment = 0;
				instance.removeMatchData(matchInt);
			}
			display = 0;
			instance.matchArray[matchInt].score[0] = atoi(red.c_str());
			instance.matchArray[matchInt].score[1] = atoi(blue.c_str());
			instance.matchArray[matchInt].score[2] = atoi(yellow.c_str());
			instance.matchArray[matchInt].score[3] = atoi(green.c_str());

			redCounter = 0;
			blueCounter = 0;
			yellowCounter = 0;
			greenCounter = 0;

			if(increment)
			{
			instance.matchIndex++; //Increment the match index
			}
			instance.isMatchOngoing = 0;
			instance.postMatchCleanup(matchInt);

			//response().set_header("Location", "/score/buttons.html");
			response().out() <<
					"Scores for this match submitted and saved.\n"
					"<p><a href=\"/match/scoring.html\">Score Next Match</a>\n"
					"<p><a href=\"/admin/control-center.html\">Control Center</a>\n";
		}
	}
	catch (std::exception const &e)
	{
		std::cerr<<e.what();
		std::cerr<<"I didn't realize that this would throw.....";
	}

	if (display)
	{
	response().out() <<
			"<html>\n"
			"<body>\n"
			"<h1>Match Scores</h1>\n"
			"<p>Please verify that these scores are correct.\n"
			"<p>Once submitted, there is no going back.\n"
			"<p><form action=\"scoring.html\" method=\"POST\">\n"
			"<p>Red Score:\n"
			"<p><input name=\"red\" type=\"text\" value=\""
			<< redCounter <<
			"\">\n"
			"<p>Blue Score:\n"
			"<p><input name=\"blue\" type=\"text\" value=\""
			<< blueCounter <<
			"\">\n"
			"<p>Yellow Score\n"
			"<p><input name=\"yellow\" type=\"text\" value=\""
			<< yellowCounter <<
			"\">\n"
			"<p>Green Score\n"
			"<p><input name=\"green\" type=\"text\" value=\""
			<< greenCounter <<
			"\">\n"
			"<input type=\"hidden\" name=\"match-number\" value=\""
			<< matchNumberG <<
			"\">\n"
			"<p><p><input type=\"submit\" value=\"Submit Scores\">"
			"</form>";
	}

}

void fms::dispFinalScores()
{
	if(!instance.isMatchOngoing && (instance.currentCenter == "match-scores"))
	{
		response().out() <<
				"<table>\n"
				"<tr>\n"
				"<th>Color</th>\n"
				"<th style=\"width:150px\">Number</th>\n"
				"<th style=\"width:200px\">Score</th>\n"
				"</tr>\n"
				"<tr>\n<td colspan=\"3\"></td>\n</tr>\n"
				"<tr bgcolor=\"#FF0000\">\n"
				"<td>Red</td>\n"
				"<td style=\"font-size:150%\">"
				<< instance.matchArray[instance.matchIndex - 1].TeamNumber[0] <<
				"</td>\n"
				"<td style=\"font-size:200%\">"
				<< instance.matchArray[instance.matchIndex - 1].score[0] <<
				"</td>\n"
				"</tr>\n"
				"<tr bgcolor=\"#0000FF\">\n"
				"<td>Blue</td>\n"
				"<td style=\"font-size:150%\">"
				<< instance.matchArray[instance.matchIndex - 1].TeamNumber[1] <<
				"</td>\n"
				"<td style=\"font-size:200%\">"
				<< instance.matchArray[instance.matchIndex - 1].score[1] <<
				"</td>\n"
				"</tr>\n"
				"<tr bgcolor=\"#FFFF66\">\n"
				"<td>Yellow</td>\n"
				"<td style=\"font-size:150%\">"
				<< instance.matchArray[instance.matchIndex - 1].TeamNumber[2] <<
				"</td>\n"
				"<td style=\"font-size:200%\">"
				<< instance.matchArray[instance.matchIndex - 1].score[2] <<
				"</td>\n"
				"</tr>\n"
				"<tr bgcolor=\"#009933\">\n"
				"<td>Green</td>\n"
				"<td style=\"font-size:150%\">"
				<< instance.matchArray[instance.matchIndex - 1].TeamNumber[3] <<
				"</td>\n"
				"<td style=\"font-size:200%\">"
				<< instance.matchArray[instance.matchIndex - 1].score[3] <<
				"</td>\n"
				"</tr>\n"
				"</table>\n";
				//Match index - 1
	}
	if (!instance.isMatchOngoing &&(instance.currentCenter == "leaderboard"))
	{
		leaderboard();
	}
}

void fms::controlCenter()
{
	std::ifstream filein("control-center.html");
	response().out() << filein.rdbuf();
}

void fms::controlCenterjs()
{
	std::ifstream filein("control-center.js");
	response().out() << filein.rdbuf();
}

void fms::soundhtml()
{
	std::ifstream filein("sound.html");
	response().out() << filein.rdbuf();
}

void fms::soundjs()
{
	std::ifstream filein("sound.js");
	response().out() << filein.rdbuf();
}

void fms::currentSound()
{
	if(instance.currentSound == "m-start")
	{
		response().out() << "start";
		instance.currentSound = "";
	}

	if(instance.currentSound == "m-end")
	{
		response().out() << "end";
		instance.currentSound = "";
	}

	if(instance.currentSound == "m-abort")
	{
		response().out() << "abort";
		instance.currentSound = "";
	}
}

void fms::leaderboard()
{
	int j;
	//bool flag;

	instance.sortTeams();

	response().out() <<
			"<table>\n"
			"<tr>\n"
			"<th>Rank</th>\n"
			"<th>Number</th>\n"
			"<th>Average Score</th>\n"
			"</tr>\n";

	//Find each rank and then output it
		for (j = 0; j < instance.numTeams; j++)
		{
			//if (instance.teamArray[j].rank == i)
			//{
				response().out() <<
						"<tr>\n"
						"<td>"
						<< instance.teamArray[j].rank <<
						"</td>\n"
						"<td>"
						<< instance.teamArray[j].TeamNumber <<
						"</td>\n"
						"<td>"
						<< instance.teamArray[j].average <<
						"</td>\n"
						"</tr>\n";
		}
}

void fms::audienceCenter()
{
	std::string setCenter;
	setCenter = request().get("set");

	if(setCenter != "")
	{
		instance.currentCenter = setCenter;
	}
}

void fms::saveEventFile()
{
	bool success;
	success = instance.saveEventFile();
	instance.saveScoreFile();

	if (success)
	{
		response().out() <<
				"File successfully saved.";
	}
}

void fms::overlay()
{
	std::string sign;
	sign = request().get("sign");
	std::ifstream filein;

	if (sign == "plus")
	{
		filein.open("plus-overlay.png");
	}

	if (sign == "minus")
	{
		filein.open("minus-overlay.png");
	}

	response().content_type("image/png");
	response().out() << filein.rdbuf();
}

void fms::matchNumber()
{
	response().out() << instance.matchIndex + 1;
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
