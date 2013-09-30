/*
Implementation file for Player.h
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/

#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/*************************
private:
	GenderType	gender;
	char*		name;
	int			level;
**************************/

Player::Player():name(NULL), gender(UNKNOWN), level(0)
{
}

Player::Player(char* name, GenderType gender):name(NULL), gender(gender), level(0)
{
	setName(name);
}

Player::Player(const Player& aPlayer):name(NULL)
{
	setName(aPlayer.name);
	setGender(aPlayer.gender);
	setLevel(aPlayer.level);
}

const Player& Player::operator=(const Player& aPlayer)
{
	//if it is a self copy, don't do anything
	if(this == &aPlayer)
		return *this;
	//make current object *this a copy of the passed in object aPlayer
	else
	{
		setName(aPlayer.name);
		setGender(aPlayer.gender);
		setLevel(aPlayer.level);
		return *this;
	}
}


Player::~Player()
{
	if(name)
		delete[] name;
}

char* Player::getName() const
{
	//strcpy(name, this->name);
	return name;
}

GenderType Player::getGender(void) const
{
	return gender;
}

int Player::getLevel(void) const
{
	return level;
}

void Player::setName(char* name)
{
	//release the exisisting memory if there is any
	if(this->name)
		delete [] this->name;

	//set new name
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

void Player::setGender(GenderType gender)
{
	this->gender = gender;
}
	
void Player::setLevel(int level)
{
	this->level = level;
}

ostream& operator<<(ostream& out, const Player& aPlayer)
{
	out << right << setw(strlen(aPlayer.name) + 2) << aPlayer.name << setw(2) << '[' << aPlayer.level << ']' << endl;
	return out;
}

void Player::LevelUp()
{
	level += 1;
}
