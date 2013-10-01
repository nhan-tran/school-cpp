/*
Task - A class representing a single instance of a 'task'.
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project.

Modifications:
11/25/11 -	added destructor ~Task().
			modified course/date/detail to be char pointer variables.

*/


#ifndef TASK
#define	TASK

const int MAX_CHAR = 101;

class Task
{
public:
		//constructors
		Task();	// default constuctor
		Task(const char course[], const char date[], const char detail[]);
		
		//destructor
		~Task();

		//accessor functions
		void getCourse(char course[]) const;
		void getDate(char date[]) const;
		void getDetail(char detail[]) const;
		void print() const;

		//mutator functions
		void setCourse(const char course[]);
		void setDate(const char date[]);
		void setDetail(const char detail[]);

private:
		char* course;
		char* date;
		char* detail;
};
#endif