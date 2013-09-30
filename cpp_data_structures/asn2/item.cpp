/*
Implementation file for item.h
Author: Nhan Tran
Date: 1/25/12
Sources: Mike Noel - linkedListADT project
*/

#include "item.h"
#include <iostream>
#include <iomanip>

using namespace std;
#pragma warning(disable:4996)		//disable warning from strcpy

/***************
private:
		char* name;
		double weight;
****************/

item::item(): name(NULL), weight(NULL)
{
}

item::item(char* name, double weight): name(NULL), weight(weight)
{
	setName(name);
	setWeight(weight);
}

item::item(const item& anItem) : name(NULL), weight(0)
{
	setName(anItem.name);
	setWeight(anItem.weight);
}

//overloading the = operator
const item& item::operator=(const item& anItem)
{
	if(this == &anItem)		//if this and anItem are equal then nothing else is needed
			return *this;
	else					//otherwise copy anItem into *this and return *this
	{
		setName(anItem.name);
		setWeight(anItem.weight);
		return *this;
	}
}


item::~item()	//destructor
{
	if(name)	//if name is true, which is if name is not false/NULL then
		delete[] name;
}

void item::getName(char * name) const	//char * name is a reference variable so any changes to it will be felt outside the block
{
	//copies this->name into name. strcpy(dest*, source*).
	strcpy(name, this->name);
}

double item::getWeight(void) const
{
	return weight;
}

void item::setName(char * name)
{
	//if this instance of item had a name then delete the existing name first
	if(this->name)	//if this item's name is true which is not false/NULL then
		delete[] this->name;

	//set new name
	this->name = new char[strlen(name)+1]; //declare this->name as new char array of lenght formal variable name + 1
	strcpy(this->name, name);	//copies over name into this->name
}

void item::setWeight(double weight)
{
	this->weight = weight;
}

//compares two "item" type objects. first gets the names, then if name1 is less than name2 returns true
//since the operator is < "less than".
bool operator<(const item& d1, const item& d2)
{
	char name1[100];
	char name2[100];

	d1.getName(name1);
	d2.getName(name2);

	if(strcmp(name1, name2) < 0)	//if name1 is less than name2 strcmp will give a value of less than 0
		return true;
	else
		return false;
}

//compares two item names since item names are also their identifiers, if names are equal/the same then reuturns true.
bool operator==(const item& d1, const item& d2)
{
	char id1[100];
	char id2[100];

	d1.getName(id1);
	d2.getName(id2);

	if (strcmp(id1, id2) == 0)
		return true;
	else
		return false;
}

//overloads the << operator so when you go cout << 'item' it will call this and print the following block?
ostream& operator<<(ostream& out, const item& anItem)
{
	out << anItem.name;
	return out;
}
