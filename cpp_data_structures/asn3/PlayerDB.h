/*
PlayerDB class - Represents a player database that holds the information of all players in
the RPG game. The database uses a hash table to store the players.
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/


#ifndef PLAYERDB_H
#define PLAYERDB_H

#include "HashTable.h"
#include "Player.h"
#include <iomanip>
#include <iostream>

class PlayerDB
{
public:
	PlayerDB();
	PlayerDB(ostream& output);
	~PlayerDB();

	const PlayerDB& operator= (const PlayerDB& db);

	void AddPlayer(Player& aPlayer);
	bool RemovePlayer(char const * key);
	Player* FetchPlayer(char const * const key);
	int getSize(void) const;
	void PrintDiagnostics();

private:
	
	HashTable* db;	//a pointer to a node pointer OR read table is a pointer to a pointer that points to a node type
	int capacity;
	const static int DEFAULT_CAPACITY = 3;
};
#endif