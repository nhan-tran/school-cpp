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


12/03/11 - implemented linear linked list to take the place of the array of pointers of Task.
		   this change includes creating a 'struct Node' and Node* varibles of head and last.
		   3 add functions were also added. The program uses addSorted to create a list sorted
		   by course name.
*/

#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "Task.h"
#include <iostream>
using namespace std;

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
	void addSorted(const Task &aTask);
	void addAtTop(const Task &aTask);
	void addAtBottom(const Task &aTask);

	void loadTaskScheduler(const char fileName[]);

private:

//here you first define a struct, a new type of data called Node
//in a node you have a variable of type Task named "data" and a pointer variable
//of type Node called "next", so "next" points to another Node... hence linked list.

//the Node(xxxx) is the constructor which everytime a Node is created it fires...

	struct Node
	{
		Task	data;
		Node *	next;

		
		//a node contains a reference to a Task
		Node(const Task& aTask)
		{
			char course[MAX_CHAR];	//declares 3 local variables inside the constructor
			char date[MAX_CHAR];	
			char detail[MAX_CHAR];
			
			aTask.getCourse(course);  //aTask is the passed in task..
			aTask.getDate(date);
			aTask.getDetail(detail);
			
			data.setCourse(course);
			data.setDate(date);
			data.setDetail(detail);

			next = NULL;
		}	
	};	//end of struct definition

	Node*	head;
	// pointer to the last Node. 
	Node*	last;
	int		size;
};
#endif