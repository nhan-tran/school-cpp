/*
Player class - Represents a player of the RPG game and holds information on the player's name,
gender, and game level.
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/


#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

enum GenderType {MALE, FEMALE, UNKNOWN};

class Player
{
public:
	Player();
	Player(char* name, GenderType gender);
	Player(const Player& aPlayer);	//copy constructor
	~Player();

	char* getName() const;
	GenderType getGender(void) const;
	int getLevel(void) const;
	void LevelUp();

	void setName(char* name);
	void setGender(GenderType gender);
	void setLevel(int level);

	const Player& Player::operator=(const Player& aPlayer); //overloading assignment operator
	friend ostream& operator<<(ostream& out, const Player& aPlayer); //overloading ostream operator

private:
	GenderType	gender;
	char*		name;
	int			level;

};

#endif