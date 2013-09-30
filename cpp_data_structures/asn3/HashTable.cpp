/*
Implementation file for HashTable.h
Author: Nhan Tran
Date: 2/29/12
Sources: Mike Noel - hashTable project
*/

#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/**************************
private:
		node ** table;
		int capacity;
		int size;
*****************************/

HashTable::HashTable(int capacity):
	size(0), capacity(capacity), table(new node*[capacity])
	//table is a ptr to a node ptr array, makes 11 heads ptr heads [0..1..2..3..]
{
	//initialize each headd of the individual linked list
	for (int i = 0; i < capacity; i++)
		table[i] = NULL;
}

void HashTable::destroyTable()
{
	//delete each chain in the table
	for(int i = 0; i < capacity; i++)
	{
		node * head = table[i];
		node * curr;
		while(head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}

	//delete the pointer array 'table'
	delete[] table;
}

HashTable::~HashTable()
{
	destroyTable();
}

void HashTable::insert(Player& aPlayer)
{
	char* key;		//NEED TO DESTROY??
	//key = new char[strlen(aPlayer.getName())];	//get the name and use it as the key
	key = aPlayer.getName();

	//calculate the insertion position (the index of the array)
	size_t index = calculatedIndex(key);	
	
	//check if player exists already
	if(retrieve(key) != NULL)	//if player already exists
	{
		cout << "Attempting to add player " << '"' << key << '"' << " to the database -- Failed." << endl;
	}
	else
	{
		//create new node to hold the data
		node * newNode = new node(aPlayer);		//NEED TO DESTROY??

		//insert the new node at the beginning of the linked list
		newNode->next = table[index];	//set what the newNode points to, which is the table index (or rather what table[index] points to
									//the index will be a number within capacity once it goes through the calculatedIndex function
		table[index] = newNode;		//set table[index] to point to the newNode so it's the first node now
		size++;						//for every node increment size
		cout << "Attempting to add player " << '"' << key << '"' << " to the database -- Success!" << endl;
	}
	key = NULL;
	delete key;
}

size_t HashTable::calculatedIndex(char const * const key) const
{
	size_t length = strlen(key);
	size_t hashValue = 0;

	//hashing based on Horner's rule
	hashValue = key[0];
	for(size_t i = 1; i < length; i++)
	{
		hashValue = hashValue * 32;
		hashValue = hashValue + key[i];
	}
	hashValue = hashValue % 3;
	return hashValue;
}

bool HashTable::remove(char const * key)
{
		//calculate the removal position (the index of the array)
		size_t index = calculatedIndex(key);	//find the 'index' from the key. with the 'index' it makes getting to the node a lot faster!

		//search for the date to be removed in the chain (linked list)
		node * curr = table[index];		//once you get to the right table[index] traverse the linked nodes to find exact match
		node * prev = NULL;
		
		char* p_name = NULL;
		bool ret = false;

		while (curr)	//while curr pointer is true/is not null
		{
			p_name = curr->person.getName();
			if (strcmp(key, p_name) == 0)	//if key matches player name
			{
				//remove the node
				if(!prev)		//if it's the first node make table[index] point to the next node
						table[index] = curr->next;
				else			//it's not the first node, make the last node point to the next node, skipping this one in the middle
					prev->next = curr->next;

				curr->next = NULL;	//remove pointer of curr next
				delete curr;		//delete the node that was found, the Player object will go through its destructor 
				curr = NULL;
				size--;
				ret = true;
			}
			else	//key does not match with name, move on to the next node
			{
				prev = curr;
				curr = curr->next;
			}
		}

		p_name = NULL;
		delete p_name;

		return ret;
}

Player* HashTable::retrieve(char const * const key)
{
		//calculate the removal position (the index of the array)
		size_t index = calculatedIndex(key);	//find the 'index' from the key. with the 'index' it makes getting to the node a lot faster!

		//search for the node to be retrieved in the chain (linked list)
		node * curr = table[index];		//once you get to the right table[index] traverse the linked nodes to find exact match
		node * prev = NULL;
		char* p_name = NULL;
		Player* currPlayer = NULL; 

		while (curr)	//while curr pointer is true/is not null
		{
			p_name = curr->person.getName();

			if (strcmp(key, p_name) == 0)	//if key matches player name
			{
				currPlayer = &curr->person;	//return the address of the Player person object that ptr curr is pointing to
				break;
			}
			else	//key does not match with name, move on to the next node
				curr = curr->next;
		}
		
		p_name = NULL; //char* ptr p_name could be pointing to something, make NULL first then delete
		delete p_name;

		//key cannot be found
		return currPlayer;	//if key was found then Player* currPlayer has address else NULL;
}

void HashTable::PrintTable()
{

	cout << "====================" << endl;
	cout << "Hash Table Diagnostics" << endl << endl;
	cout << "Table Size: " << capacity << endl;
	cout << "Number of Entries: " << size << endl;

	for(int i = 0; i < capacity; i++)
	{
		node * curr = table[i];		
		cout << "Slot[" << i << "]:" << endl;

		if (!curr)
			cout << setw(7) << "EMPTY" << endl;
		else
		{
			while (curr)	//while curr pointer is true/is not null
			{
				cout << curr->person;
				curr = curr->next;		
			}
		}
	}
	cout << "====================" << endl;
}

int HashTable::getSize() const
{
	return size;
}

