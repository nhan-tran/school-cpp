
//
// CST 407 - Assignment #3
//
// Michael Hoffman
//
// File: main.cpp
//
// Race analyzer main program.
//


#pragma  warning( disable : 4786 )


#include  <iostream>
#include  <assert.h>
#include  <stdlib.h>
#include  "mainDisplay.h"



//
// If PROMPT_FILENAME is defined, the user will be prompted to
// enter the names of the stages and riders data files. If
// PROMPT_FILENAME is not defined, the default names specified
// by STAGE_FILENAME and RIDER_FILENAME are used.
//
//#define  PROMPT_FILENAME
#define  STAGE_FILENAME       "stages.txt"
#define  RIDER_FILENAME       "riders.txt"


//testing includes
#include "raceAnalyzer.h"

typedef  pair<Seconds, string>  PairResults;
typedef  list<PairResults>      Results;
    //
    // Used to return stage or race time information for
    // riders.
    //

//testing main
//int main()
//{
//	RaceAnalyzer analyzer(STAGE_FILENAME, RIDER_FILENAME);
//
//	cout << "Number of stages: " << analyzer.numStages() << endl;
//
//	string thisGuy = "BASSO";
//
//	cout << "Team for " + thisGuy << " is: " << analyzer.getTeam(thisGuy) << endl;
//	cout << "Country for " + thisGuy << " is: " << analyzer.getCountry(thisGuy) << endl;
//
//	set<string> allNames = analyzer.riders();
//	set<string> allTeams = analyzer.teams();
//	set<string> allCountries = analyzer.countries();
//
//	//mph
//	cout << "MPH: " << analyzer.calcMPH(4241, 4) << endl;
//	cout << "All Stages MPH: " << analyzer.calcMPH(33300, 0) << endl;
//
//	//Results rider_results = analyzer.riderResults(1, "DSC", "USA");
//	
//	//test sorting
//	Results rider_results2 = analyzer.riderResults(1, "DSC", "");	
//
//	string team = "CSC";
//	unsigned stage = 1;
//	Seconds teamT = analyzer.teamTime(team, stage, 3);
//	cout << "DSC stage 1: " << teamT << endl;
//
//	teamT = analyzer.teamTime(team,0,3);
//	cout << "DSC total time: " << teamT << endl;
//
//	return 0;
//}






//
// Typedef for menu choices
//
enum  MenuChoice
{
  menuDisplaySummary_  =  '1',
  menuDisplayRiders_   =  '2',
  menuDisplayTeams_    =  '3',

  menuMin_  =  menuDisplaySummary_,
  menuMax_  =  menuDisplayTeams_,

  menuQuit_  = 'Q'
};


enum  FileType
{
  stage_,
  rider_
};


//
// Fetch a file name from the user
//
static const  string  getFilename( FileType  type )
{
  string  filename;

#ifndef  PROMPT_FILENAME

  filename  =  (type == stage_  ?  STAGE_FILENAME  :  RIDER_FILENAME);

#else

  cout  <<  "Enter "
        <<  (type == stage_  ?  "stage"  :  "rider")
        <<  " filename: ";

  cin  >>  filename;

#endif

  return  filename;
}


//
// Display the menu
//
static  void  menu()
{
  cout  <<  endl
        <<  "***********************"  <<  endl
        <<  endl
        <<  endl
        <<  "Menu: "  <<  endl
        <<  endl
        <<  "  1. Summary info"   <<  endl
        <<  "  2. Rider results"  <<  endl
        <<  "  3. Team results"   <<  endl
        <<  "  Q. Quit"           <<  endl;
}


//
// Get user's menu choice
//
static MenuChoice  getChoice()
{
  menu();

  char  choice;

  while(true)
  {
    cout  <<  endl
          <<  "Enter choice: ";

    cin  >>  choice;
    cin.ignore();

    choice = toupper(choice);

    if  (choice == menuQuit_)  break;

    if  (choice >= menuMin_  &&  choice <= menuMax_)  break;

    cout  <<  endl
          <<  "  *** Invalid option. Try Again. ***"
          <<  endl;
  }

  return  MenuChoice( choice );
}


//
// Main program
//
int  main()
{
  try
  {
    const string  stageFilename  =  getFilename( stage_ );
    const string  riderFilename  =  getFilename( rider_ );


    //
    // Setup the race data analyzer
    //
    RaceAnalyzer  raceData( stageFilename, riderFilename );

    bool  done  =  false;


    //
    // Loop until the userwants to quite
    //
    while( ! done )
    {
      //
      // Get a process the user's menu choice
      //
      switch( getChoice() )
      {
        case  menuDisplaySummary_  :  displaySummary( raceData );
                                      break;

        case  menuDisplayRiders_   :  displayRiderData( raceData );
                                      break;

        case  menuDisplayTeams_    :  displayTeamData( raceData );
                                      break;

        case  menuQuit_            :  done  =  true;
                                      break;

        default                    :  assert(true);
      }
    }

  }
  catch(...)
  {
    system("pause");
    return  EXIT_FAILURE;
  }

  return  EXIT_SUCCESS;
}
