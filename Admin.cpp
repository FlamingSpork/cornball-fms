/*
 * Admin.cpp
 * 	Contains code for setup and scorekeeping.
 *
 *  Created on: Jun 10, 2015
 *      Author: FlamingSpork
 */

#include "Admin.h"

Admin::Admin() {
	//Auto-generated constructor stub
	teamArray = NULL;
	matchArray = NULL;

	isTimerRunning = 0;
	isMatchOngoing = 0;

}

Admin::~Admin() {
	//Auto-generated destructor stub
	if(teamArray) {
		delete [] teamArray;
	}

	if(matchArray) {
		delete [] matchArray;
	}
}

void Admin::initFMS()
{
    std::cout <<
    "Welcome to Tanx FMS!\n"
    "WARNING: This is not officially supported by the Foundation for\n"
    "Inspiration and Recognition of Science and Technology.\n"
    "Any use of FIRST(R) branding is merely a suggested use and does\n"
    "not imply any form of endorsement.\n"
    "\n\n\n"
    "Please enter your event filename or type none.\n"
    "Filename: ";
    std::string filename;
    std::cin >> filename;
    if (filename == "none")
    {
        std::cout <<
        "If you choose to proceed without a event file, the system may behave\n"
        "erratically.  Please press Ctrl-C now to exit and create a schedule file.\n";
        exit(0);
    }

    std::cout<<"Parsing file, please wait...\n";
    //Parse event file
    parseEventFile(filename);
    std::cout.flush();
    //std::cout<<"Reading schedule, please wait...\n"<< std::endl;
    printf("Reading schedule, please wait....\n");
    parseScheduleFile(scheduleFile);
    teamlistFetchData();
}
void Admin::teamlistFetchData()
{
    //And now::  Pseudocode();
    //Fetch list of teams
    //Determine number of teams
    int teamNumber;
    std::string fileBufferS;
    char command[300], teamNumberC[5];
    bool istItOpen;
    int i; //counter
    for ( i=0; i < numTeams; i++)
    {
        //i is also the index for the teams list
    	teamNumber = teamArray[i].TeamNumber;
        std::sprintf (command, "curl -o %d --header 'X-TBA-App-Id: frc3003:cornball-fms:v0.01' http://www.thebluealliance.com/api/v2/team/frc%d", teamNumber, teamNumber);
    	//command = "curl -o test www.google.com";
        system(command);

    }
    std::ifstream filein;
    //dataIn >> completeFile;

    for (i=0; i < numTeams; i++)
    {
    	std::sprintf (teamNumberC, "%d", teamArray[i].TeamNumber);
    	filein.open(teamNumberC);
    	istItOpen = filein.is_open();

    	std::stringstream sStream;
    	sStream << filein.rdbuf();

    	boost::property_tree::ptree pTree;
    	boost::property_tree::read_json(sStream, pTree);

    	//Will this even work?
    	teamArray[i].fullName = pTree.get<std::string>("name");
    	teamArray[i].location = pTree.get<std::string>("location");
    	teamArray[i].nickname = pTree.get<std::string>("nickname");
        /*std::getline(filein, fileBufferS); //The entire file
        fileBufferC = fileBufferS.c_str();
        charBuffer = strtok(fileBufferC, ","); //"website"
        charBuffer = strtok(NULL, ","); //"name"
        teamArray[i].fullName = charBuffer;
        charBuffer = strtok(NULL, ","); //"locality"
        charBuffer = strtok(NULL, ","); //"rookie_year"
        charBuffer = strtok(NULL, ","); //"region"
        charBuffer = strtok(NULL, ","); //"team_number"
        charBuffer = strtok(NULL, ","); //"location"
        strcpy(charBuffer1, charBuffer); // Let the madness begin...
        charBuffer = strtok(NULL, ",");
        strcpy(charBuffer2, charBuffer);
        charBuffer = strtok(NULL, ",");
        strcpy(charBuffer3, charBuffer);
        std::sprintf(charBuffer, "%s,%s,%s", charBuffer1, charBuffer2, charBuffer3);
        teamArray[i].location = charBuffer;
        charBuffer4 = strtok(NULL, ","); //"key"
        charBuffer4 = strtok(NULL, ","); //Let's see...
        charBuffer4 = strtok(NULL, ",");
        charBuffer4 = strtok(NULL, ","); //"country_name"
        charBuffer = strtok(NULL, ","); //"nickname"
        teamArray[i].nickname = charBuffer;*/

        filein.close();
    }
}

void Admin::parseEventFile(std::string filename)
{
	std::ifstream filein(filename);
	std::string fileBufferS;
	char * fileBufferC, * charBuffer;
	bool istItOpen;
	istItOpen = filein.is_open();

	//fileAll = filein.rdbuf();
	//fileBufferS = "";


	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	strcpy(eName, charBuffer);
	//std::cout<<eName<<"\n";

	istItOpen = filein.is_open();

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	strcpy(scheduleFile, charBuffer);
	//std::cout<<scheduleFile<<"\n";

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	//We'll parse this line later
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	strcpy(teamList, charBuffer);
	//std::cout<<teamList<<"\n";

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	matchIndex = atoi(charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	strcpy(rankingsFile, charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	numPractice = atoi(charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	numQual = atoi(charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	numElim = atoi(charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	numFinal = atoi(charBuffer);

	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	numTeams = atoi(charBuffer);

	//Parse the team list
	int i=0;
	teamArray = new TeamInfo [numTeams];
	teamArray[i].TeamNumber = atoi(strtok(teamList, ","));
	for (i=1; i < numTeams; i++)
	{
		teamArray[i].TeamNumber = atoi(strtok(NULL, ","));
		//std::cout<<teamArray[i].TeamNumber<<"\n";
	}

}

void Admin::parseScheduleFile(char filename [50])
{
	std::ifstream filein(filename);
	std::string fileBufferS;
	char * charBuffer, * charBuffer1, * matchType;
	int numMatches = numPractice + numQual + numElim + numFinal;
	int i=0;

	matchArray = new MatchInfo [ numMatches ];

	std::getline(filein, fileBufferS); //Take and dispose of first line

	for (i=0; i < numMatches; i++)
	{
		std::getline(filein, fileBufferS);
		charBuffer = fileBufferS.c_str();
		charBuffer1 = strtok(charBuffer, ",");
		matchArray[i].TeamNumber[0] = atoi(strtok(NULL,",;"));
		matchArray[i].TeamNumber[1] = atoi(strtok(NULL,",;"));
		matchArray[i].TeamNumber[2] = atoi(strtok(NULL,",;"));
		matchArray[i].TeamNumber[3] = atoi(strtok(NULL,",;"));
		matchType = strtok(NULL, ",;");
		if (!strcmp(matchType, "Practice"))
		{
			matchArray[i].matchtype = MatchType::practice_match;
		}
		if(!strcmp(matchType, "Qualification"))
		{
			matchArray[i].matchtype = MatchType::qual_match;
		}
		if (!strcmp(matchType, "Elimination"))
		{
			matchArray[i].matchtype = MatchType::elim_match;
		}
		if (!strcmp(matchType, "Final"))
		{
			matchArray[i].matchtype = MatchType::final_match;
		}
	}


}

int Admin::getCurrentTimer()
{
	//Take the difference between the current time and the start time
	int diff;
	diff = (int)time(NULL) - (int)startTime;
	if(isTimerRunning)
	{
		if (diff > 120)
		{
			isTimerRunning = 0;
			isMatchOngoing = 0;
			return 0;
		}
		else
		{
		return 120 - diff;
		}
	}
	else
	{
		return 0;
	}

}

void Admin::startTimer()
{
	startTime = time(NULL);
	isTimerRunning = 1;
}
