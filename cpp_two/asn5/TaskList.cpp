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
12/03/11 - added addSorted()
		   added addToTop()
		   added addToBottom()
*/

#include "TaskList.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//default constructor
TaskList::TaskList()
{
	head = NULL;
	last = NULL;
	size = 0;
}

TaskList::TaskList(const int initialCap, const char fileName[])
{
	head = NULL;
	last = NULL;
	size = 0;
	loadTaskScheduler(fileName);
}

TaskList::~TaskList()
{
	Node* current = head;

	while(head !=NULL)	//while head is pointing to something
	{
		current = head->next;	//set current to the next pointer

		delete head;	//head points to a Node which inlcudes a Task, delete that Task memory
		
		head = current; //reset head to the next item (now the top item on the list)
	}
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

	//traverse the list to have current Node point to the right index
	int		i;
	Node*	current = head;
	for(i = 0; i < index; i++)
	{
		current = current->next;
	}

	current->data.getCourse(course);	//this goes into current.data grabs the course info and puts it into 'course' variable. 
	current->data.getDate(date);
	current->data.getDetail(detail);
	aTask.setCourse(course);			//this uses the data in the 'course' variable that we just got back and sets it in the aTask variable.
	aTask.setDate(date);				//the aTask variable is a reference variable so this will actually set the course of a Task type variable
	aTask.setDetail(detail);			//that is being passed into the get() function.
	return true;
}

int TaskList::searchTask(const char course[], Task &match) const
{
	Node* current;
	int found = 0;
	char currentCourse[MAX_CHAR];
	char currentDate[MAX_CHAR];
	char currentDetail[MAX_CHAR];

	for(current = head; current!=NULL; current = current->next)
	{
		current->data.getCourse(currentCourse);
		current->data.getDate(currentDate);
		current->data.getDetail(currentDetail);
		if(strcmp(course, currentCourse) == 0)
		{
			cout << endl << "Course: " << currentCourse << endl;
			cout << "Date:   " << currentDate << endl;
			cout << "Detail: " << currentDetail << endl;
			found++;
		}	
	}
	
	return found;
}

void TaskList::printAll() const
{
	Node* current;		//pointer of Node type, this will be used to traverse the link list.
	char course[MAX_CHAR];
	char date[MAX_CHAR];
	char detail[MAX_CHAR];

	//cout << setw(COURSE_COL_WIDTH) << "Course" << setw(DATE_COL_WIDTH) << "Date" << setw(DETAIL_COL_WIDTH) << "Detail" << endl;
	
	//current equals head, while current is not null (continue), update current to current->next (points to next Node)
	//while current means: while current is true, because current is false when it is null so loop wil stop since condition is false
	for(current = head; current; current = current->next)
	{
		current->data.getCourse(course);
		current->data.getDate(date);
		current->data.getDetail(detail);
		cout << endl << "Course: " << course << endl;
		cout << "Date:   " << date << endl;
		cout << "Detail: " << detail << endl;
	}
}

void TaskList::saveTaskScheduler(const char fileName[]) const
{
	ofstream out;
	Node * current;
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
	for(current = head; current; current = current->next)
	{
		current->data.getCourse(course);
		current->data.getDate(date);
		current->data.getDetail(detail);
		out << course << ';' << date << ';' << detail << endl;
	}
	out.close();
}

void TaskList::addTask(const Task &aTask) //aTask is the local name for the pass in value of a 'Task' instance
{
	addSorted(aTask);
}

void TaskList::addSorted(const Task &aTask)
{
	char	course[MAX_CHAR];
	char	currentCourse[MAX_CHAR];

	aTask.getCourse(course);

	Node* newNode = new Node(aTask); //make new Node with aTask data
	Node* prev = NULL;	//Node pointer to store previous Node
	Node* current = head;	//Node pointer to store current Node

	while(current) //while current is true enter loop, if current is false/null don't enter
	{
		current->data.getCourse(currentCourse); //get the currentCourse of the current Node
		if(strcmp(course, currentCourse) < 0) //if course comes before currentCourse exit loop
			break;

		prev = current;	//otherwise make this current Node the previous
		current = current->next; //and make current Node the next node... and loop again
		if(!current) //if this new current points to a Null then we are at the last Node
			last = newNode;	//loop will exit because current is false, this newNode will be the last
							//node. Set 'last' to point to this newNode.
	}

	//after loop exits it means we are in the correct position in the list
	//make the next of the newNode point to current(the next Node) and 
	//prev(the previous Node) point to newNode. newNode is inserted between the two.
	newNode->next = current;

	if(!prev) //if prev is still null afer going through loop then head is still null, this is 1st Node.
	{
		head = newNode;
		last = newNode;
	}
	else
	{
		prev->next = newNode; //repoint the next of the previous Node to newNode
	}
	size++;
}

//function adds entries at the top of the list
void TaskList::addAtTop(const Task &aTask) 
{
	//make a new Node pointer
	Node* newNode = new Node(aTask);	//this new Node is made with the aTask parameter that was passed in.

	//At the 1st Node head will be NULL, later Nodes added will be added on top of this Node so this Node is 'last' Node
	if (!head)
		last = newNode;
	//put the newly made Node at the begining of the list
	//by saying the newNode 'next' pointer is equal to 'head'. 'head' currently points to the 1st item in list
	//the newNode 'next' now points to where 'head' points to.
	//Then reassign 'head' to point to this newNode's address, the newNode is now the first item in the list because
	//'head' points to it.
	newNode->next = head;
	head = newNode;
	size++;   
}

//function adds entries at the bottom of the list
void TaskList::addAtBottom(const Task &aTask)
{
	Node* newNode = new Node(aTask);

	if(!head)
	{
		head = newNode;
		last = newNode;
	}
	else
	{
		last->next = newNode; //the 'last' will now point to the newNode because it is no longer the 'last'
		last = newNode;		//set last to point to the newNode
	}

	size++;
}