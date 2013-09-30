/*
HashTable class - A hash table that has the ability to add, remove, and retrieve objects.
Currently the object it stores is of Player type. When objects are placed in the table it is
hashed and is stored within an index of the hashed value. The table is implemented by an 
array of pointers that point to a node pointer, these pointers do not point to nodes but to 
node pointers; the node pointer points to the actual node. ie: an array of 3 has a pointer to 
three heads of linked nodes.
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Player.h"
#include <iomanip>

class HashTable
{
public:
	HashTable();
	HashTable(ostream& dbOut);
	HashTable(int capacity);
	~HashTable();

	const HashTable& operator= (const HashTable& db);

	void insert(Player& aPlayer);
	bool remove(char const * key);
	Player* retrieve(char const * const key);
	int getSize(void) const;
	void PrintTable();
	void destroyTable();	//a method that the destructor calls 

private:
	struct node
	{
		Player person;
		node * next;
		node(const Player& aPlayer) : person(aPlayer), next(NULL) {}	//constructor for a node
	};
	
	node ** table;	//a pointer to a node pointer OR read table is a pointer to a pointer that points to a node type
	int size;
	int capacity;

	size_t calculatedIndex(char const * const key) const;
};
#endif