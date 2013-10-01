/*
Implementation file for Task.h
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project.
*/

#include "Task.h"
#include <iostream>
using namespace std;

//default constructor
Task::Task()
{
	strcpy(course, "N/A");
	strcpy(date, "N/A");
	strcpy(detail, "N/A");
}

Task::Task(const char course[], const char date[], const char detail[])
	 {
		strcpy(this->course, course);	//this-> refers to the instance variable course WITHIN the block
		strcpy(this->date, date);		//think that you could name the variable course1 which is different than
		strcpy(this->detail, detail);	//the formal parameter 'course'.
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
	strcpy(this->course, course);
}

void Task::setDate(const char date[])
{
	strcpy(this->date, date);
}

void Task::setDetail(const char detail[])
{
	strcpy(this->detail, detail);
}

//end