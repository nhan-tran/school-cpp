/*
CIS162 Lab 2: Scheduler (nt_taskScheduler.cpp)
Description: Schedule program that manages school tasks. Program loads data file taskData.txt
on start then provides options to add, display and search tasks. On exit program writes all tasks
including newly added tasks back to data file.
Author: Nhan Tran
Date: 10/17/2011
Sources: Li Liang - AddressBook2.cpp
		 http://www.cplusplus.com/reference/clibrary/cstring/strcmp/
*/

#include <iostream>                 //Required if your program does any I/O
#include <string>					//Required for string type
#include <iomanip>					//Needed for setprecision
#include <fstream>					//for i/o streaming, opening files

using namespace std;


const int MAX_CHAR = 100;
const int MAX_STORAGE = 100;


//define a new data type 'task'
struct task
{
	char course[MAX_CHAR];
	char detail[MAX_CHAR];
	char date[MAX_CHAR];
};

void showMenu();
char getSelection();
void doSelection(task pList[], int& pCount, bool& pQuit);
void addTask( task pList[], int& pCount);
void displayAll(task pList[], int& pCount);
void searchCourse(task pList[], int& pCount);
void getString(char prompt[], char inputStr[], int maxChar);

void loadData(const char pFileName[], task pList[], int& pCount);  
void saveData(const char pFileName[], task pList[], int& pCount);


int main()
{
	ofstream outputFile;
	task list[MAX_STORAGE];
	int count;
	bool quit;
	char fileName[] = "taskData.txt";
	
	quit = false;
	count = 0;	
	loadData(fileName, list, count);

	cout << "---------Nhan's Task Manager---------" << endl;
	
	//loop UI till quit
	while (!quit)
	{
		//display menu
		showMenu();
		//getSelection, doSelection
		doSelection(list, count, quit);
	}
	saveData(fileName, list, count);

	return 0;
}


///////FUNCTIONS START HERE///////////

//Name: showMenu
//Desc: prints menu for users to see the options
void showMenu()
{
	cout << '\n';
	cout << "(A) Add a new task." << endl;
	cout << "(D) Display all tasks." << endl;
	cout << "(S) Search tasks by course." << endl;
	cout << "(Q) Quit." << endl;
	cout << "\nPlease select an option: " ;
}


//Name: getSelection
//Desc: grabs an input char.
char getSelection()
{
	char input[2];

	cin.get(input, 2, '\n');
	if (!cin)	//if input is bad just clear and assign a space ' ' to input.
	{
		cin.clear();
		cin.ignore(100, '\n');
		return input[0] = ' ';
	}
	cin.ignore(100, '\n');
	return input[0];
}

//Name: doSelection
//Desc: calls getSelection to get a char then if char is valid run the menu option for it.
void doSelection(task pList[], int& pCount, bool& pQuit)
{
	char q;

	switch (getSelection())		//test the value returned by getSelection
	{
		case 'a':
		case 'A':
			cout << endl;
			addTask(pList, pCount);
			break;		
		case 'd':
		case 'D':
			cout << endl;
			displayAll(pList, pCount);
			break;		
		case 's':
		case 'S':
			cout << endl;
			searchCourse(pList, pCount);
			break;
		case 'q':
		case 'Q':
			cout << endl << "All tasks will be saved. Press Enter to continue . . ." << endl;
			cin.get(q);
			pQuit = true;
			break;
		default:
			cout << endl << "Error invalid input." << endl; 			
	}

}

//count is the current empty array, but the actually number reflects how many elements there really are. eg: count is 5 means list[0-4] is filled and store the next one in 5.
//Name: addTask
//Desc: 
void addTask( task pList[], int& pCount)	
{
	getString("Enter course: ", pList[pCount].course, 100);
	getString("Enter date: ", pList[pCount].date, 100);
	getString("Enter detail: ", pList[pCount].detail, 100);
	pCount++;	
}

//Name: getString
//Desc: takes in reference cstring[], if input did not start with a null (someone pressed entered, no input) then store it.
void getString(char prompt[], char inputStr[], int maxChar)
{
	cout << prompt;
	cin.get(inputStr, maxChar, '\n');
	while (!cin)		//error if user pressed 'enter' then [0] is null
		{	
			cin.clear();
			cin.ignore(100, '\n');
			cout << prompt ;
			cin.get(inputStr, maxChar, '\n');
		}
	cin.ignore(100, '\n');
}

//Name: displayAll
//Desc: goes through all elements in actual parameter task list[] and displays each member.
void displayAll(task pList[], int& pCount)
{
	int i;

	for (i = 0; i < pCount; i++)
	{
		cout << "Course: " << left << setw(25) << pList[i].course << ' ' << "Date: " << setw(20) << pList[i].date << endl;
		cout << "Detail: " << pList[i].detail << '\n' << endl;
	}
}


//Name: searchCourse
//Desc: takes in a search term then searches for any matches and prints out results if match is found.
void searchCourse(task pList[], int& pCount)
{
	char search[MAX_CHAR];
	int i, found = 0;
	
	cout << "Enter course name: ";
	cin.get(search, 100, '\n');
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Enter course name: ";
		cin.get(search, 100, '\n');
	}
	cin.ignore(100, '\n');

	for (i = 0; i < pCount; i++) //for every element
	{
		//if (search == pList[i].course) <---- this does not compare the cstrings
		//strcmp compares two strings and if they are equal returns a value of 0
		if (strcmp(search, pList[i].course) == 0)
		{			
			cout << endl;	
			cout << "Course: " << left << setw(25) << pList[i].course << ' ' << "Date: " << setw(20) << pList[i].date << endl;
			cout << "Detail: " << pList[i].detail << '\n' << endl;
			found++;
		}
	}

	if (found == 0)
	{
		cout << endl;
		cout << "0 results for '" << search << "'." << endl;
	}
	else
	{
		cout << endl;
		cout << found << " results for '" << search << "'." << endl;
	}	
}


//Name: loadData
//Desc: opens the data file, reads each input and stores it in the reference task list array passed down.
void loadData (const char pFileName[], task pList[], int& pCount) //reference variable counter = tCount
{
	ifstream inputFile;
	
	inputFile.open(pFileName);	//converting string to be used with the open command
	if (!inputFile.is_open())
	{
		cout << "taskData.txt cannot be opened." << endl;
		cout << "Press enter to exit...";
		cin.get();
		exit (1);					//exits because of invalid file
	}
	while (inputFile.peek() != EOF)
	{
		inputFile.get(pList[pCount].course, 100, '\n');
		inputFile.ignore(100, '\n');
		inputFile.get(pList[pCount].date, 100, '\n');
		inputFile.ignore(100, '\n');
		inputFile.get(pList[pCount].detail, 100, '\n');
		inputFile.ignore(100, '\n');
		pCount++;
	}			
	inputFile.close();
}

//Name: saveData
//Desc: writes all tasks to the data file.
void saveData(const char pFileName[], task pList[], int& pCount)
{
	ofstream outputFile;
	int i;

	outputFile.open (pFileName);
	if(!outputFile)
	{
		outputFile.clear();
	}

	//write/overwrite all taks to outputfile
	for (i = 0; i < pCount; i++)
	{
		outputFile << pList[i].course << endl;
		outputFile << pList[i].date << endl;
		outputFile << pList[i].detail << endl;
	}

	//close outfile
	outputFile.close();
}