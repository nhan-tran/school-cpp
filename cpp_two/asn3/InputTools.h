/*
Input Tools - functions that can be used to take in input
and peform necessary error checking to return a valid input.
Author: Nhan Tran
Date: 11/3/11
Sources: Li Liang addressBookB project InputTools.h
*/

#ifndef INPUT_TOOLS_H
#define INPUT_TOOLS_H

//should only have prototypes in header
int getInt(const char prompt[]);
double getDouble(const char prompt[]);
char getChar(const char prompt[]);
void getString (const char prompt[], char inputStr[], int maxChar);
#endif