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
#include <thread>
#include <string.h>
#include <stdlib.h>
#include "Admin.h"

class my_hello_world : public cppcms::application {
public:
    my_hello_world(cppcms::service &srv) :
        cppcms::application(srv)
    {
        dispatcher().assign("/smile",&my_hello_world::smile,this);
        mapper().assign("smile","/smile");
        
        dispatcher().assign("/number/(\\d+)",&my_hello_world::number,this,1);
        mapper().assign("number","/number/{1}");

        dispatcher().assign("/increment",&my_hello_world::increment,this);
        mapper().assign("increment","/increment");

        dispatcher().assign("/jquery.min.js",&my_hello_world::jQuery,this);
        mapper().assign("jquery.min.js","/jquery.min.js");

        //Blue Scoring code
        dispatcher().assign("/score/blue/inc",&my_hello_world::blueInc,this);
        mapper().assign("blueinc","/score/blue/inc");
        dispatcher().assign("/score/blue/get",&my_hello_world::blueGet,this);
        mapper().assign("blueget","/score/blue/get");
        dispatcher().assign("/score/blue/dec",&my_hello_world::blueDec,this);
        mapper().assign("bluedec","/score/blue/dec");

        //Red Scoring code
        dispatcher().assign("/score/red/inc",&my_hello_world::redInc,this);
        mapper().assign("redinc","/score/red/inc");
        dispatcher().assign("/score/red/get",&my_hello_world::redGet,this);
        mapper().assign("redget","/score/red/get");
        dispatcher().assign("/score/red/dec",&my_hello_world::redDec,this);
        mapper().assign("reddec","/score/red/dec");

        //Yellow Scoring Code
        dispatcher().assign("/score/yellow/inc",&my_hello_world::yellowInc,this);
        mapper().assign("yellowinc","/score/yellow/inc");
        dispatcher().assign("/score/yellow/get",&my_hello_world::yellowGet,this);
        mapper().assign("yellowget","/score/yellow/get");
        dispatcher().assign("/score/yellow/dec",&my_hello_world::yellowDec,this);
        mapper().assign("yellowdec","/score/yellow/dec");

        //Green Scoring Code
        dispatcher().assign("/score/green/inc",&my_hello_world::greenInc,this);
        mapper().assign("greeninc","/score/green/inc");
        dispatcher().assign("/score/green/get",&my_hello_world::greenGet,this);
        mapper().assign("greenget","/score/green/get");
        dispatcher().assign("/score/green/dec",&my_hello_world::greenDec,this);
        mapper().assign("greendec","/score/green/dec");



        dispatcher().assign("/score/buttons.html",&my_hello_world::buttons,this);
        mapper().assign("buttons.html","/score/buttons.html");

        dispatcher().assign("/score/buttons.js",&my_hello_world::buttonsjs,this);
        mapper().assign("buttons.js","/score/buttons.js");

        dispatcher().assign("/sporks",&my_hello_world::sporks,this);
        mapper().assign("sporks","/sporks");

        dispatcher().assign("",&my_hello_world::root,this);
        mapper().assign("");

        mapper().root("/server");

        dispatcher().assign("/audience/logo.png",&my_hello_world::logopng,this);
        mapper().assign("logo.png","/audience/logo.png");
        dispatcher().assign("/audience/audience.html",&my_hello_world::audiencehtml,this);
        mapper().assign("audience.html","/audience/audience.html");
        dispatcher().assign("/audience/audience.js",&my_hello_world::audiencejs,this);
        mapper().assign("audience.js","/audience/audience.js");
        dispatcher().assign("/audience/timer",&my_hello_world::getTimer,this);
        mapper().assign("timer","/audience/timer");

        dispatcher().assign("/admin/teamlist.html",&my_hello_world::teamlist,this);
        mapper().assign("teamlist.html", "/admin/teamlist.html");
        dispatcher().assign("/admin/pdfGen.js",&my_hello_world::pdfGen,this);
        mapper().assign("pdfGen.js", "/admin/pdfGen.js");
        dispatcher().assign("/admin/schedule.html",&my_hello_world::printSchedule,this);
        mapper().assign("schedule.html", "/admin/schedule.html");
        dispatcher().assign("/admin/schedule/(\\d+)",&my_hello_world::printHighlightedSchedule,this,1);
        mapper().assign("schedule","/admin/schedule/{1}");

        dispatcher().assign("/match/start",&my_hello_world::startMatchTimer,this);
        mapper().assign("matchstart","/match/start");
        dispatcher().assign("/match/scoring.html",&my_hello_world::matchScoring,this);
        mapper().assign("matchscoring","/match/scoring.html");
        dispatcher().assign("/match/final-scores",&my_hello_world::dispFinalScores,this);
        mapper().assign("final-scores","/match/final-scores");

        my_hello_world::redCounter = 0;
        my_hello_world::blueCounter = 0;
        my_hello_world::yellowCounter = 0;
        my_hello_world::greenCounter = 0;

    }
    //virtual void main(std::string url);

    void smile();
    void sporks();
    void root();
    void number(std::string num);
    void increment();
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

    void logopng();
    void audiencehtml();
    void audiencejs();
    void getTimer();

    void teamlist();
    void pdfGen();
    void printSchedule();
    void printHighlightedSchedule(std::string num);

    void startMatchTimer();
    void matchScoring();
    void dispFinalScores();


private:
    int counter;
    int redCounter;
    int blueCounter;
    int yellowCounter;
    int greenCounter;
};

//void my_hello_world::main(std::string /*url*/)
/*{
    response().out()<<
        "<html>\n"
        "<body>\n"
        "  <h1>Hello World</h1>\n"
        "Hello Papa!\n"
        "</body>\n"sporks
        "</html>\n";
}*/
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
        srv.applications_pool().mount(cppcms::applications_factory<my_hello_world>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
    std::cout<<"Exiting now..."<< std::endl;
}

void my_hello_world::smile()
{
    response().out()<< 
    "<html>\n"
    "<body>\n"
    "<h1>:)!</h1>\n"
    "<p> Love, Philo\n"
    "</body>\n"
    "</html>\n";
}

void my_hello_world::sporks()
{
    response().out()<<
    "<html>\n"
    "<body>\n"
    "<center><h1>Sporks!</h1></center>\n"
    "<p>A spork.\n"
    "<p><img src=\"http://quibbler.host22.com/spork/NYCapitol.jpg\">\n"
    "</body>\n"
    "</html>\n";

}

void my_hello_world::root()
{
    response().out()<<
    "<html>\n"
    "<body>\n"
    "<h1>Philo's Web Server</h1>\n"
    "<p><a href=\"/sporks\">Sporks!</a>\n"
    "<p><a href=\"/smile\">Smile!</a>\n"
    "</body>\n"
    "</html>\n";
}

void my_hello_world::number(std::string num)
{
int no = atoi(num.c_str());  
    response().out() << "The number is " << no << "<br/>\n";  
    response().out() << "<a href='" << url("/") << "'>Go back</a>"; 
}

void my_hello_world::increment()
{
    counter++;
    response().out() << "The counter is now " << counter << ".\n";
}

void my_hello_world::redInc()
{
    redCounter++;
    response().out() << redCounter;
}

void my_hello_world::redGet()
{
    response().out() << redCounter;
}

void my_hello_world::redDec()
{
    redCounter--;
    response().out() << redCounter;
}

void my_hello_world::blueInc()
{
    blueCounter++;
    response().out() << blueCounter;
}

void my_hello_world::blueGet()
{
    response().out() << blueCounter;
}

void my_hello_world::blueDec()
{
    blueCounter--;
    response().out() << blueCounter;
}

void my_hello_world::yellowInc()
{
    yellowCounter++;
    response().out() << yellowCounter;
}

void my_hello_world::yellowGet()
{
    response().out() << yellowCounter;
}

void my_hello_world::yellowDec()
{
    yellowCounter--;
    response().out() << yellowCounter;
}

void my_hello_world::greenInc()
{
    greenCounter++;
    response().out() << greenCounter;
}

void my_hello_world::greenGet()
{
    response().out() << greenCounter;
}

void my_hello_world::greenDec()
{
    greenCounter--;
    response().out() << greenCounter;
}
void my_hello_world::buttons()
{
   /* response().out() <<
    "<html>\n"
    "<body>\n"
    "<script src=\"http://themagicalnecromancerinvasion.com/spork/jquery.min.js\">\n"
    "<script>\n"
    "var red = function() {\n"
    //"jQuery.get( \"score/red\", function( datar ) {\n"
    "alert( datar + \" points.\");\n"
    "});\n"
    "}\n"
    "var blue = function() {\n"
    "jQuery.get( \"score/blue\", function( datab ) {\n"
    "alert( datab + \" points.\");\n"
    "});\n"
    "}\n"
    "</script>\n"
    "<a onclick=\"alert('Tort!');\" href=\"javascript:void(0)\"><img src=\"http://upload.wikimedia.org/wikipedia/commons/thumb/0/07/Button_Icon_Red.svg/200px-Button_Icon_Red.svg.png\"></a>\n"
    "<a onclick=\"window.blue();\" href=\"javascript:void(0)\"><img src=\"http://upload.wikimedia.org/wikipedia/commons/thumb/3/3f/Button_Icon_Blue.svg/200px-Button_Icon_Blue.svg.png\"></a>\n"
    "</body>\n"
    "</html>\n"; */
    
    std::ifstream file ("buttons.html");
    response().out() << file.rdbuf();
}

void my_hello_world::buttonsjs()
{
    std::ifstream file ("buttons.js");
    response().out() << file.rdbuf();
}

void my_hello_world::logopng()
{
    std::ifstream file ("MaizeLogo.png");
    response().content_type("image/png");
    response().out() << file.rdbuf();
}

void my_hello_world::audiencehtml()
{
    std::ifstream file ("audience.html");
    response().out() << file.rdbuf();
}

void my_hello_world::audiencejs()
{
    std::ifstream file ("audience.js");
    response().out() << file.rdbuf();
}

void my_hello_world::teamlist()
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
    "<script src=\"http://themagicalnecromancerinvasion.com/spork/jquery.min.js\"></script>\n"
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

void my_hello_world::pdfGen()
{
	std::ifstream filein("pdfGen.js");
	response().out() << filein.rdbuf();
}

void my_hello_world::printSchedule()
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
	    "<script src=\"http://themagicalnecromancerinvasion.com/spork/jquery.min.js\"></script>\n"
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

void my_hello_world::printHighlightedSchedule(std::string num)
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
	    "<script src=\"http://themagicalnecromancerinvasion.com/spork/jquery.min.js\"></script>\n"
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

void my_hello_world::jQuery()
{
	std::ifstream filein("jquery.min.js");
	response().out() << filein.rdbuf();
}

void my_hello_world::getTimer()
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

void my_hello_world::startMatchTimer()
{
	if (!instance.isTimerRunning)
	{
	instance.startTimer();
	instance.isMatchOngoing = 1;
	response().out() << "Timer Started.";
	}
	else
	{
		response().out() << "The match timer is already running.";
	}
}

void my_hello_world::matchScoring()
{
	std::string red, blue, yellow, green;
	bool display = 1;
	try
	{
		//It took me *far* too long to find how easy this is.
		red = request().post("red");
		blue = request().post("blue");
		yellow = request().post("yellow");
		green = request().post("green");

		if (!red.empty())
		{
			display = 0;
			instance.matchArray[instance.matchIndex].score[0] = atoi(red.c_str());
			instance.matchArray[instance.matchIndex].score[1] = atoi(blue.c_str());
			instance.matchArray[instance.matchIndex].score[2] = atoi(yellow.c_str());
			instance.matchArray[instance.matchIndex].score[3] = atoi(green.c_str());

			redCounter = 0;
			blueCounter = 0;
			yellowCounter = 0;
			greenCounter = 0;

			instance.matchIndex++; //Increment the match index
			instance.isMatchOngoing = 0;

			//response().set_header("Location", "/score/buttons.html");
			response().out() <<
					"Scores for this match submitted and saved.\n"
					"<p><a href=\"/match/start\">Start Next Match</a>";
		}
	}
	catch (std::exception const &e)
	{
		std::cerr<<e.what();
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
			"\">"
			"<p><p><input type=\"submit\" value=\"Submit Scores\">"
			"</form>";
	}

}

void my_hello_world::dispFinalScores()
{
	if(!instance.isMatchOngoing)
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
		//Make it output team numbers and scores
		//Match index - 1
	}
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
