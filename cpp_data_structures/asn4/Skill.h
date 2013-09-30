/*
Skill class - Represents a skill that players of the RPG game can obtain. A skill consists of the name of the skill,
the description of what it does, and the level of the skill.
Author: Nhan Tran
Date: 3/14/12
Sources: Mike Noel - binarySearchTree project
*/


#ifndef SKILL_H
#define SKILL_H
#include <iostream>
using namespace std;

class Skill
{
public:
	Skill();
	Skill(char* name, char* description, int level);
	Skill(const Skill& aSkill);
	~Skill();

	char* getName() const;
	char* getDescription() const;
	int getLevel() const;

	void setName(char* name);
	void setDescription(char* description);
	void setLevel(int level);
	void Skill::Display(ostream& out);

	const Skill& Skill::operator=(const Skill& aSkill); //overloading assignment operator
	friend ostream& operator<<(ostream& out, const Skill& aSkill); //overloading ostream operator

private:
	char*		name;
	char*		description;
	int			level;

};

#endif