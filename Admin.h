/*
 * Admin.h
 *
 *  Created on: Jun 10, 2015
 *      Author: FlamingSpork
 *
 *      Let's see how many include lines we need.....
 *
 *      A class for administration and related tasks.
 */
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <thread>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <time.h>

#include "boost/boost/property_tree/ptree.hpp"
#include "boost/boost/property_tree/json_parser.hpp"

#ifndef ADMIN_H_
#define ADMIN_H_

class Admin {
public:
	Admin();
	virtual ~Admin();


    void initFMS();
    //void teamlist();
    void teamlistFetchData();
    void parseEventFile(std::string filename);
    void parseScheduleFile(char scheduleFile [50]);

    int getCurrentTimer();
    void startTimer();

    void postMatchCleanup();
    void sortTeams();

    enum MatchType {practice_match, qual_match, elim_match, final_match};
    enum TeamColour {red_team = 0, blue_team = 1, yellow_team = 2, green_team = 3};
    struct MatchInfo {
        int TeamNumber [ 4 ];
        MatchType matchtype;
        int score [ 4 ];
    };
    struct TeamInfo {
        int TeamNumber;
        std::string fullName;
        std::string location;
        std::string nickname;
        int rank, matchesWon, sumScores, numMatches, average;
    };
    TeamInfo * teamArray; //Will be initialized in code
    MatchInfo * matchArray;

    char eName [20], scheduleFile [50], teamList [100], rankingsFile [50]; //Important stuff
    int matchIndex, numPractice, numQual, numElim, numFinal, numTeams;

    time_t startTime;
    bool isTimerRunning;

    bool isMatchOngoing;

    std::string currentSound;
    std::string currentCenter;

};

#endif /* ADMIN_H_ */
