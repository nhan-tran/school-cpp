/*
Implementation file for Skill.h
Author: Nhan Tran
Date: 3/14/12
Sources: Mike Noel - binarySearchTree project
*/

#include "Skill.h"
#include <iostream>
#include <iomanip>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/*************************
private:
	char*		name;
	char*		description;
	int			level;
**************************/

Skill::Skill():name(NULL), description(NULL)
{
	level = 0;
}

Skill::Skill(char* name, char* description, int level):name(NULL), description(NULL), level(0)
{
	setName(name);
	setDescription(description);
	setLevel(level);
}

Skill::Skill(const Skill& aSkill):name(NULL), description(NULL)
{
	setName(aSkill.name);
	setDescription(aSkill.description);
	setLevel(aSkill.level);
}

const Skill& Skill::operator=(const Skill& aSkill)	//assignment operator thisSkill = thatSkill
{
	//if it is a self copy, don't do anything
	if(this == &aSkill)
		return *this;
	//make current object *this a copy of the passed in object aSkill
	else
	{
		setName(aSkill.name);
		setDescription(aSkill.description);
		setLevel(aSkill.level);
		return *this;
	}
}


Skill::~Skill()
{
	if(name)
		delete[] name;

	if(description)
		delete[] description;
}

char* Skill::getName() const
{
	return name;
}

char* Skill::getDescription() const
{
	return description;
}

int Skill::getLevel(void) const
{
	return level;
}

void Skill::setName(char* name)
{
	//release the exisisting memory if there is any
	if(this->name)
		delete [] this->name;

	//set new name
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

void Skill::setDescription(char* description)
{
	//release the exisisting memory if there is any
	if(this->description)
		delete [] this->description;

	//set new name
	this->description = new char[strlen(description)+1];
	strcpy(this->description, description);
}
	
void Skill::setLevel(int level)
{
	this->level = level;
}

ostream& operator<<(ostream& out, const Skill& aSkill)	//overloads the << operator. it is used like: cout << SkillObject;
{
	out << aSkill.name << " -- " << aSkill.description << " " << "[Lvl: " << aSkill.level << "]" << endl;
	return out;
}

void Skill::Display(ostream& out)	//display the skill by printing the skill to a referenced ostream variable use as SkillObject.Display(cout)
{									//if cout is referenced ostream variable passed it then when things are printed to 'out' it actually prints to cout and there the screen
	out << name << " -- " << description << " " << "[Lvl: " << level << "]" << endl;
}