/*
Implementation file for Task.h
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project.

Modifications:
11/25/11 -	added destructor ~Task().
			modified course/date/detail to be char pointer variables.


*/

#include "Task.h"
#include <iostream>
using namespace std;

//default constructor
Task::Task()
{
	course = new char[strlen("N/A") + 1];	//set course pointer variable as a new char pointer containing lenght of N/A + 1 elements.
	strcpy(course, "N/A");					//copy "N/A" into course, which was setup before to hold the exact number of chars.
	date = new char[strlen("N/A") + 1];
	strcpy(date, "N/A");
	detail = new char[strlen("N/A") + 1];
	strcpy(detail, "N/A");
}

Task::Task(const char course[], const char date[], const char detail[])
	 {
		this->course = new char[strlen(course) + 1];
		strcpy(this->course, course);	//this-> refers to the instance variable course of the current instance of Task.
		this->date = new char[strlen(date) + 1];
		strcpy(this->date, date);		//this->course = the same as task.course, in case of a pointer than it is like (*task).course
		this->detail = new char[strlen(detail) + 1];
		strcpy(this->detail, detail);	//think that you could name the variable course1 which is different than the formal parameter 'course'.
	 }

//destructor
//deletes the pointer variables to release memory allocated to them.
Task::~Task()
{
	if(course != NULL)
		delete [] course;
	if(date != NULL)
		delete [] date;
	if(detail != NULL)
		delete [] detail;
}

void Task::getCourse(char course[]) const
{
	strcpy(course, this->course);
}

void Task::getDate(char date[]) const
{
	strcpy(date, this->date);
}

void Task::getDetail(char detail[]) const
{
	strcpy(detail, this->detail);
}

void Task::print() const
{
	cout << course; //print all
}

void Task::setCourse(const char course[])
{
	if (this->course != NULL)
		delete [] this->course;
	this->course = new char[strlen(course) + 1];
	strcpy(this->course, course);
}

void Task::setDate(const char date[])
{
	if(this->date != NULL)
		delete [] this->date;
	this->date = new char[strlen(date) + 1];
	strcpy(this->date, date);
}

void Task::setDetail(const char detail[])
{
	if(this->detail != NULL)
		delete [] this->detail;
	this->detail = new char[strlen(detail) + 1];
	strcpy(this->detail, detail);
}

//end