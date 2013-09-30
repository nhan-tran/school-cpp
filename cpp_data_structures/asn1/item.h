/*
Item class - Represents a type of item object in a RPG game. Each item has a name and weight.
Author: Nhan Tran
Date: 1/25/12
Sources: Mike Noel - linkedListADT project
*/


#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;
class item
{
public:
	item();
	item(char* name, double weight);
	item(const item& anItem);	//copy constructor use as itemPtr = new item(anItem)
	~item();	//destructor

	void getName(char* name) const;
	double getWeight(void) const;
	void setName(char* name);
	void setWeight(double weight);
	const item& operator=(const item& anItem);
	friend ostream& operator <<(ostream& out, const item& anItem);

private:
	char* name;
	double weight;

};

bool operator< (const item& d1, const item& d2);
bool operator== (const item& d1, const item& d2);

#endif