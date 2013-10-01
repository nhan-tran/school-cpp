/*
Implementation file for TaskList.cpp
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB program.

Modifications:
11/25/11 - added expandList()
		   added ~TaskList()
		   added int capacity
		   added int initialCap
		   modified listOfTasks to be dynamic array of Task.
*/

#include "TaskList.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//default constructor
TaskList::TaskList()
{
	capacity = TASK_LIST_CAPACITY;
	listOfTasks = new Task[capacity];
	size = 0;
}

TaskList::TaskList(const int initialCap, const char fileName[])
{
	capacity = initialCap;
	listOfTasks = new Task[capacity];
	size = 0;
	loadTaskScheduler(fileName);
}

TaskList::~TaskList()
{
	if(listOfTasks != NULL)
		delete [] listOfTasks;
}

void TaskList::loadTaskScheduler(const char fileName[])
{
	ifstream	in;
	char		course[MAX_CHAR];
	char		date[MAX_CHAR];
	char		detail[MAX_CHAR];
	Task		aTask;		//local to this block

	in.open(fileName);
	if(!in)
	{
		in.clear();
		cerr << endl << "Error - cannot open file " << fileName << "." << endl;
		exit(1);
	}

	in.get(course, MAX_CHAR, ';');	//get the first thing up to ';' which is course
	while (!in.eof())				//if not end of file
	{
		in.get();					//get next thing which is the delimiter ';'
		in.get(date, MAX_CHAR, ';');	//get next thing which is date
		in.get();	//gets second ';'
		in.get(detail, MAX_CHAR, '\n');	//get detail up to '\n' (end of line) because it is the last thing on a line
		in.ignore(100, '\n');			//get '\n' new line character
		
		aTask.setCourse(course);	//aTask is the local variable declared at the top. This calls a function to copy the cstring course that we just got
		aTask.setDate(date);		//into the 'course' variable of the aTask instance local to this block.
		aTask.setDetail(detail);

		addTask(aTask);
		in.get(course, MAX_CHAR, ';');	//gets the next name.. if not eof then continues the loop
	}
	in.close();		//close input file
}

void TaskList::addTask(const Task &aTask) //aTask is the local name for the pass in value of a 'Task' instance'
{
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	if(size == capacity)		//if the list/size is full then make the list bigger
	{
		expandList();
	}
	aTask.getCourse(course);	//passes local variable 'course' into getCourse which then getCourse copies the 'name' stored in the instance class aTask into the passed reference cstring 'course'. So now the local course in this block has the value of aTask.course.
	aTask.getDate(date);
	aTask.getDetail(detail);
	listOfTasks[size].setCourse(course);	//goes to the variable listOfTasks array of Task in TaskList class and sets the local variable in this block 'course' into the 'course' variable of type Task in listOfTask[size].
	listOfTasks[size].setDate(date);
	listOfTasks[size].setDetail(detail);

	size++;
}

int TaskList::getSize() const
{
	return size;
}

bool TaskList::get(int index, Task &aTask) const
{
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	if(index < 0 || index >= size)
				return false;
	listOfTasks[index].getCourse(course);
	listOfTasks[index].getDate(date);
	listOfTasks[index].getDetail(detail);
	aTask.setCourse(course);
	aTask.setDate(date);
	aTask.setDetail(detail);
	return true;
}

int TaskList::searchTask(const char course[], Task &match) const
{
	int index;
	int found = 0;
	char currentCourse[MAX_CHAR];
	char currentDate[MAX_CHAR];
	char currentDetail[MAX_CHAR];

	for(index = 0; index < size; index++)
	{
		listOfTasks[index].getCourse(currentCourse);
		listOfTasks[index].getDate(currentDate);
		listOfTasks[index].getDetail(currentDetail);
		if(strcmp(course, currentCourse) == 0)
		{
			//match.setCourse(currentCourse);
			//match.setDate(currentDate);
			//match.setDetail(currentDetail);
			//break;
			cout << endl << "Course: " << currentCourse << endl;
			cout << "Date:   " << currentDate << endl;
			cout << "Detail: " << currentDetail << endl;
			found++;
		}	
	}
	//if (index == size)
	//		return false;
	//else
	//		return true;
	
	return found;
}

void TaskList::printAll() const
{
	int index;
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	//cout << setw(COURSE_COL_WIDTH) << "Course" << setw(DATE_COL_WIDTH) << "Date" << setw(DETAIL_COL_WIDTH) << "Detail" << endl;
	for(index = 0; index < size; index++)
	{
		listOfTasks[index].getCourse(course);
		listOfTasks[index].getDate(date);
		listOfTasks[index].getDetail(detail);
		cout << endl << "Course: " << course << endl;
		cout << "Date:   " << date << endl;
		cout << "Detail: " << detail << endl;
	}
}

void TaskList::saveTaskScheduler(const char fileName[]) const
{
	ofstream out;
	int index;
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	out.open(fileName);
	if(!out)
	{
		out.clear();
		cerr << endl << "Failed to open " << fileName << "." << endl << endl;
		exit(1);
	}
	for(index = 0; index < size; index++)
	{
		listOfTasks[index].getCourse(course);
		listOfTasks[index].getDate(date);
		listOfTasks[index].getDetail(detail);
		out << course << ';' << date << ';' << detail << endl;
	}
	out.close();
}

//expandList
//this function makes a new list double the size of the old then copies the old one over and then makes itself the new list
void TaskList::expandList()
{
	Task*	tempList;
	char	course[MAX_CHAR];
	char	date[MAX_CHAR];
	char	detail[MAX_CHAR];
	int		i;

	capacity = capacity * 2;
	tempList = new Task[capacity];

	for (i = 0; i < size; i++)	//for every task get the course/date/detail and set it in the tempList
	{
		listOfTasks[i].getCourse(course);
		listOfTasks[i].getDate(date);
		listOfTasks[i].getDetail(detail);
		tempList[i].setCourse(course);
		tempList[i].setDate(date);
		tempList[i].setDetail(detail);
	}
	
	//delete pointer address pointing to old List and all the memory addresses in that array
	delete [] listOfTasks;

	//set listOfTasks to now point to the tempList, then set tempList pointer to null so only listOfTasks points to the array.
	listOfTasks = tempList;
	tempList = NULL;
}