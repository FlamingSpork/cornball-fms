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
    "Welcome to Cornball FMS!\n"
    "WARNING: This is not officially supported by the Foundation for\n"
    "Inspiration and Recognition of Science and Technology.\n"
    "Any use of FIRST(R) branding is merely a suggested use and does\n"
    "not imply any form of endorsement.\n"
    "\n\n\n"
    "Please enter your event filename or type none.\n"
    "Filename: ";
    //std::string filename;
    std::cin >> eFileName;
    if (eFileName == "none")
    {
        std::cout <<
        "If you choose to proceed without a event file, the system may behave\n"
        "erratically.  Please press Ctrl-C now to exit and create a schedule file.\n";
        exit(0);
    }

    std::cout<<"Parsing file, please wait...\n";
    //Parse event file
    parseEventFile(eFileName);
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
    char command[300], teamNumberC[15];
    bool istItOpen;
    int i; //counter
    for ( i=0; i < numTeams; i++)
    {
        //i is also the index for the teams list
    	teamNumber = teamArray[i].TeamNumber;
        std::sprintf (command, "curl -o %d.team --header 'X-TBA-App-Id: frc3003:cornball-fms:v0.01' http://www.thebluealliance.com/api/v2/team/frc%d", teamNumber, teamNumber);
    	//command = "curl -o test www.google.com";
        system(command);

    }
    std::ifstream filein;
    //dataIn >> completeFile;

    for (i=0; i < numTeams; i++)
    {
    	std::sprintf (teamNumberC, "%d.team", teamArray[i].TeamNumber);
    	filein.open(teamNumberC);
    	istItOpen = filein.is_open();

    	std::stringstream sStream;
    	sStream << filein.rdbuf();

    	boost::property_tree::ptree pTree;
    	boost::property_tree::read_json(sStream, pTree);

    	teamArray[i].fullName = pTree.get<std::string>("name");
    	teamArray[i].location = pTree.get<std::string>("location");
    	teamArray[i].nickname = pTree.get<std::string>("nickname");

    	teamArray[i].matchesWon = 0;
    	teamArray[i].sumScores = 0;
    	teamArray[i].numMatches = 0;
    	teamArray[i].rank = i;

        filein.close();
    }
}

void Admin::parseEventFile(std::string filename)
{
	std::ifstream filein(filename);
	std::string fileBufferS;
	char * fileBufferC, * charBuffer;
	//bool istItOpen; //File I/O debug
	//istItOpen = filein.is_open();

	//fileAll = filein.rdbuf();
	//fileBufferS = "";


	std::getline(filein, fileBufferS);
	fileBufferC = fileBufferS.c_str();
	charBuffer = strtok(fileBufferC, "=");
	charBuffer = strtok(NULL, "=");
	strcpy(eName, charBuffer);
	//std::cout<<eName<<"\n";

	//istItOpen = filein.is_open();

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
	char teamListBuffer[100];
	strcpy(teamListBuffer, teamList);
	teamArray = new TeamInfo [numTeams];
	teamArray[i].TeamNumber = atoi(strtok(teamListBuffer, ","));
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
		if (diff == 120)
		{
			currentSound = "m-end";
			isTimerRunning = 0;
			//isMatchOngoing = 0;
			return 0;
		}
		if (!(diff > 120))
		{
		return 120 - diff;
		}

		if(diff > 120)
		{
			return 0;
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

void Admin::postMatchCleanup(int matchId)
{
	//Run cleanup operations on the specified match number.
	//This is executed after the scores are submitted.
	int i, j;

	for (i=0; i < numTeams; i++)
	{
		for (j=0; j < 4; j++)
		{
		if (teamArray[i].TeamNumber == matchArray[matchId].TeamNumber[j])
		{
			teamArray[i].sumScores += matchArray[matchId].score[j];
			teamArray[i].numMatches++;
			if (teamArray[i].numMatches <= 0)
			{
				teamArray[i].numMatches = 1;
			}
			teamArray[i].average = (teamArray[i].sumScores / teamArray[i].numMatches);

			if (j == 0)
			{
			if ((matchArray[matchId].score[0] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[0] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[0] > matchArray[matchIndex - 1].score[3]))
			{
				//This code is executed if the team won the match
				teamArray[i].matchesWon++;
			}
			}

			if (j == 1)
			{
			if ((matchArray[matchId].score[1] > matchArray[matchIndex - 1].score[0]) && (matchArray[matchIndex - 1].score[1] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[1] > matchArray[matchIndex - 1].score[3]))
			{
				//This code is executed if the team won the match
				teamArray[i].matchesWon++;
			}
			}

			if (j == 2)
			{
			if ((matchArray[matchId].score[2] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[2] > matchArray[matchIndex - 1].score[0]) && (matchArray[matchIndex - 1].score[2] > matchArray[matchIndex - 1].score[3]))
			{
				//This code is executed if the team won the match
				teamArray[i].matchesWon++;
			}
			}

			if (j == 3)
			{
			if ((matchArray[matchId].score[3] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[3] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[3] > matchArray[matchIndex - 1].score[0]))
			{
				//This code is executed if the team won the match
				teamArray[i].matchesWon++;
			}
			}
		}


		}
	}

	sortTeams();
}

void Admin::sortTeams()
{
	int i, j, flag = 1;
	TeamInfo temp;
	for (i=1; (i <= numTeams) && flag; i++)
	{
		flag = 0;

		for (j=0; j < (numTeams - 1); j++)
		{
			if (teamArray[j + 1].matchesWon > teamArray[j].matchesWon)
			{
				temp = teamArray[j];
				teamArray[j] = teamArray[j+1];
				teamArray[j+1] = temp;
				teamArray[j].rank = j+1;
				teamArray[j+1].rank = j+2;
				flag = 1;
			}
		}
	}


}

bool Admin::saveEventFile()
{
	std::ofstream fileout(eFileName);

	fileout <<
			"eventName="
			<< eName <<
			"\nscheduleFile="
			<< scheduleFile <<
			"\nteams="
			<< teamList <<
			"\ncurrentMatchIndex="
			<< matchIndex <<
			"\nrankingsFile="
			<< rankingsFile <<
			"\nnumPracticeMatches="
			<< numPractice <<
			"\nnumQualMatches="
			<< numQual <<
			"\nnumElimMatches="
			<< numElim <<
			"\nnumFinalMatches="
			<< numFinal <<
			"\nnumTeams="
			<< numTeams;

	return fileout.is_open();
}

void Admin::saveScoreFile()
{
	char filename [55];
	int i, numMatches;
	numMatches = numPractice + numQual + numElim + numFinal;

	std::sprintf (filename, "%s.scores.csv", eName);

	std::ofstream fileout(filename);

	fileout << "\"Match Number\",1,2,3,4,\"Number Meaning\",\"Match Type\"\n";

	for (i=0; i < numMatches; i++)
	{
		fileout <<
				i+1 <<
				","
				<< matchArray[i].TeamNumber[0] <<
				","
				<< matchArray[i].TeamNumber[1] <<
				","
				<< matchArray[i].TeamNumber[2] <<
				","
				<< matchArray[i].TeamNumber[3] <<
				",\"Team Numbers\",";

		if (matchArray[i].matchtype == Admin::practice_match)
		{
			fileout << "\"Practice\"\n";
		}
		if (matchArray[i].matchtype == Admin::qual_match)
		{
			fileout << "\"Qualification\"\n";
		}
		if (matchArray[i].matchtype == Admin::elim_match)
		{
			fileout << "\"Elimination\"\n";
		}
		if (matchArray[i].matchtype == Admin::final_match)
		{
			fileout << "\"Final\"\n";
		}

		fileout <<
				i+1 <<
				","
				<< matchArray[i].score[0] <<
				","
				<< matchArray[i].score[1] <<
				","
				<< matchArray[i].score[2] <<
				","
				<< matchArray[i].score[3] <<
				",\"Scores\",";

		if (matchArray[i].matchtype == Admin::practice_match)
		{
			fileout << "\"Practice\"\n";
		}
		if (matchArray[i].matchtype == Admin::qual_match)
		{
			fileout << "\"Qualification\"\n";
		}
		if (matchArray[i].matchtype == Admin::elim_match)
		{
			fileout << "\"Elimination\"\n";
		}
		if (matchArray[i].matchtype == Admin::final_match)
		{
			fileout << "\"Final\"\n";
		}
	}
}

void Admin::loadScoreFile()
{
	char filename [55];
	int i, numTotalMatches, numMatches;
	std::string fileBufferS;
	char * charBuffer, * charBuffer1;
	numTotalMatches = numPractice + numQual + numElim + numFinal;
	numMatches = numTotalMatches - matchIndex;

	std::sprintf (filename, "%s.scores.csv", eName);

	std::ifstream filein(filename);

	std::getline(filein, fileBufferS); //Take and dispose of first line

	for(i=0; i < numMatches; i++)
	{
		std::getline(filein, fileBufferS); //Dispose of team numbers
		std::getline(filein, fileBufferS); //Get scores

		charBuffer = fileBufferS.c_str();
		charBuffer1 = strtok(charBuffer, ",");
		matchArray[i].score[0] = atoi(strtok(NULL,",;"));
		matchArray[i].score[1] = atoi(strtok(NULL,",;"));
		matchArray[i].score[2] = atoi(strtok(NULL,",;"));
		matchArray[i].score[3] = atoi(strtok(NULL,",;"));

	}
}

void Admin::removeMatchData(int matchId)
{
	//This clears the data of a given match from the teams' data.
	int i, j;

	for (i=0; i < numTeams; i++)
	{
		for (j=0; j < 4; j++)
		{
		if (teamArray[i].TeamNumber == matchArray[matchId].TeamNumber[j])
		{
			teamArray[i].sumScores -= matchArray[matchId].score[j];
			teamArray[i].numMatches--;
			teamArray[i].average = (teamArray[i].sumScores / teamArray[i].numMatches);

			if (j == 0)
			{
			if ((matchArray[matchId].score[0] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[0] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[0] > matchArray[matchIndex - 1].score[3]))
			{

				teamArray[i].matchesWon--;
			}
			}

			if (j == 1)
			{
			if ((matchArray[matchId].score[1] > matchArray[matchIndex - 1].score[0]) && (matchArray[matchIndex - 1].score[1] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[1] > matchArray[matchIndex - 1].score[3]))
			{

				teamArray[i].matchesWon--;
			}
			}

			if (j == 2)
			{
			if ((matchArray[matchId].score[2] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[2] > matchArray[matchIndex - 1].score[0]) && (matchArray[matchIndex - 1].score[2] > matchArray[matchIndex - 1].score[3]))
			{

				teamArray[i].matchesWon--;
			}
			}

			if (j == 3)
			{
			if ((matchArray[matchId].score[3] > matchArray[matchIndex - 1].score[1]) && (matchArray[matchIndex - 1].score[3] > matchArray[matchIndex - 1].score[2]) && (matchArray[matchIndex - 1].score[3] > matchArray[matchIndex - 1].score[0]))
			{

				teamArray[i].matchesWon--;
			}
			}
		}


		}
	}
}
