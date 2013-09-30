/*
Implementation file for PlayerDB.h
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/

#include "PlayerDB.h"
#include <iostream>
using namespace std;

/**************************
private:
		HashTable db;
		int capacity;
		int size;
		const static int DEFAULT_CAPACITY = 11;
*****************************/

PlayerDB::PlayerDB():
	capacity(DEFAULT_CAPACITY), db(NULL)
{
	////initialize each headd of the individual linked list
	//for (int i = 0; i < capacity; i++)
	//	db[i] = NULL;
}

PlayerDB::PlayerDB(ostream& output):
	capacity(DEFAULT_CAPACITY)
{
	db = new HashTable(capacity);
}

//PlayerDB::PlayerDB(const PlayerDB& db):capacity(db->capacity), size(db->size)
//{
//	db = new node*[capacity];
//
//	//copy array of linked list
//	for(i = 0; i < capacity; i++)	//for every head* in the db
//	{
//		//copy each linked list in the array
//		if (db->db[i] == NULL)
//			db[i] = NULL;
//		else
//		{
//			//copy first node
//			db[i] = new node(db->db[i]->person);
//
//			//copy rest of chain
//			node * srcNode = db->db[i]->next;
//			node * destNode = db[i];
//			while(srcNode)
//			{
//				destNode->next = new node(srcNode->person);
//				destNode = destNode->next;
//				srcNode = srcNode->next;
//			}
//			destNode->next = NULL;
//		}
//	}
//}

//const PlayerDB& PlayerDB::operator= (const PlayerDB& db)
//{
//
//}

PlayerDB::~PlayerDB()
{
	//db->destroyTable();
	if(db)
		delete db;
}

void PlayerDB::AddPlayer(Player& aPlayer)
{
	db->insert(aPlayer);
}

bool PlayerDB::RemovePlayer(char const * key)
{
	bool ret = db->remove(key); //remove key returns true if key was removed
	if (ret)
		cout << "Removing player " << '"' << key << '"' << " from the database -- Success!" << endl;
	
	return ret;
}

Player* PlayerDB::FetchPlayer(char const * const key)
{
	Player* currPlayer = db->retrieve(key);	//if player is found store address
	if(db->retrieve(key))  //if true
		cout << "Fetching player " << '"' << key << '"' << " -- Success!" << endl;
	else
		cout << "Fetching player " << '"' << key << '"' << " -- Failed." << endl;
	
	return currPlayer;
}

void PlayerDB::PrintDiagnostics()
{
	db->PrintTable();
}