/*
TaskList is a class representing a list of tasks. An array of tasks and functions for the list is stored here.
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project.

Modifications:
11/25/11 - added expandList()
		   added ~TaskList()
		   added int capacity
		   added int initialCap
		   modified listOfTasks to be dynamic array of Task.
*/

#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "Task.h"

const int TASK_LIST_CAPACITY = 100;
const int COURSE_COL_WIDTH = 10;
const int DATE_COL_WIDTH = 20;
const int DETAIL_COL_WIDTH = 30;

class TaskList
{
public:	
	TaskList();
	TaskList(const int initialCap, const char fileName[]);

	//destructor
	~TaskList();

	bool get(int index, Task &aTask) const;
	int searchTask(const char course[], Task& match) const;
	int getSize() const;
	void saveTaskScheduler(const char fileName[]) const;
	void printAll() const;

	//mutator functions
	void addTask(const Task& aTask);
	void loadTaskScheduler(const char fileName[]);

private:
	Task*	listOfTasks;
	int		size;
	int		capacity;	//holds the capacity of the list and can be changed during run-time unlike a constant variable.

	void expandList();	//expand the list if list is full

};
#endif