/*
CIS162 Lab 4: Task Scheduler (nt_TaskScheduler2.cpp)
Description: Schedule program that manages school tasks. Program loads data file taskData.txt
on start then provides options to add, display and search tasks. On exit program writes all tasks
including newly added tasks back to data file. 
Notes: Program is based on Object Oriented Design using classes.
Author: Nhan Tran
Date: 11/25/2011
Sources: Li Liang - AddressBookC program

Modifications:
11/25/2011 - Program now uses pointer variables and dynamic arrays in Task and TaskList.
			 In using pointers and dynamic arrays, Task and TaskList objects are created during run time
			 instead of at compile time. Ex: before the size of TaskList was always a constant 100, now it
			 can be expanded while the program is running.
			 Memory leak detection is also enabled in this version of TaskScheduler.

*/

//memory leak detection tool headers
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <cctype>

#include "InputTools.h"
#include "Task.h"
#include "TaskList.h"
using namespace std;

void showMenu();
char getCommand();
void doCommand(char command, TaskList& listOfTasks);
void getTask(Task& aTask);
void getCourse(char course[]);

int main()
{
	//enable memory leak detection tools
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	char command;
	char fileName[] = "taskData.txt";
	TaskList listOfTasks(1, fileName);
	
	cout << "Nhan's Task Scheduler" << endl;
	showMenu();
	command = getCommand();
	while(command != 'q')
	{
		doCommand(command, listOfTasks);
		showMenu();
		command = getCommand();
	}
	listOfTasks.saveTaskScheduler(fileName);

	return 0;
}

void showMenu()
{
	cout << endl << "-----Main Menu----" << endl;
	cout << "(a) Add a Task" << endl
		 << "(d) Display All Tasks" << endl
		 << "(s) Search Tasks" << endl
		 << "(q) Save & Quit" << endl << endl;
}

char getCommand()
{
	char cmd;
	cmd = getChar("Please make a selection: ");
	return tolower(cmd);
}

void doCommand(char command, TaskList &listOfTasks)
{
	Task myTask;
	char course[MAX_CHAR];
	//char date[MAX_CHAR];		//not needed because modified case s getCourse
	//char detail[MAX_CHAR];	//not needed because modified case s getCourse
	int found;	//added

	switch(command)
	{
	case 'a': getTask(myTask);		//goes to getTask for Task info, a Task instance is passed back
				listOfTasks.addTask(myTask);	//then that task instance is added to List with addTask
				break;
	case 'd': listOfTasks.printAll();
				break;
	case 's': getCourse(course);
				cout << endl;
				found = listOfTasks.searchTask(course, myTask);
				cout << endl << found << " results found." << endl << endl;
				break;
	default: cout << endl << "Invalid selection." << endl;
			 break;
	}
}

void getTask(Task &aTask)
{
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	getString("Enter course: ", course, MAX_CHAR);
	getString("Enter date: ", date, MAX_CHAR);
	getString("Enter detail: ", detail, MAX_CHAR);

	aTask.setCourse(course);
	aTask.setDate(date);
	aTask.setDetail(detail);
}

void getCourse(char course[])
{
	getString("Enter course name: ", course, MAX_CHAR);
}