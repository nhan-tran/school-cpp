/*
Implementation file for InputTools.h
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project InputTools.cp
*/

#include "InputTools.h"
#include <iostream>
using namespace std;


int getInt(const char prompt[])
{
	int  number;
	
	cout << endl << prompt;
	cin >> number;

	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid number. Please try again: ";
		cin >> number;
	}

	cin.ignore(100, '\n');
	return number;
}

double getDouble(const char prompt[])
{
	double	doubleNum;

	cout << endl << prompt;
	cin >> doubleNum;

	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid value. Please try again: ";
		cin >> doubleNum;
	}

	cin.ignore(100, '\n');
	return doubleNum;
}

char getChar(const char prompt[])
{
	char aChar;

	cout << endl << prompt;

	cin >> aChar;
	cin.ignore(100, '\n');

	return aChar;
}

//This function is to get a string from cstrings array and return the string
//up to a set max number.
void getString(const char prompt[], char inputStr[], int maxChar)
{
	cout << endl << prompt;
	cin.get(inputStr, maxChar, '\n');
	while (!cin)	//cin is bad only if 'Enter' is pushed
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << endl << prompt;		//enter was pushed, prompt again
		cin.get(inputStr, maxChar, '\n');
	}
	
	cin.ignore(100, '\n');
}


