/*
TaskList is a class representing a list of tasks. An array of tasks and functions for the list is stored here.
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project.
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
	TaskList(const char fileName[]);

	bool get(int index, Task &aTask) const;
	int searchTask(const char course[], Task& match) const;
	int getSize() const;
	void saveTaskScheduler(const char fileName[]) const;
	void printAll() const;

	//mutator functions
	void addTask(const Task& aTask);
	void loadTaskScheduler(const char fileName[]);

private:
	Task	listOfTasks[TASK_LIST_CAPACITY];
	int		size;
};
#endif