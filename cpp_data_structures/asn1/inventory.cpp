/*
Implementation file for inventory.h
Author: Nhan Tran
Date: 1/25/12
Sources: Mike Noel - linkedListADT project
*/

#include "inventory.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
using namespace std;

/*********************
private:
		node * head;
**********************/

//default constructor set maxWeight to 100
inventory::inventory(): head(NULL), size(0), maxWeight(100), totWeight(0)
{
}

inventory::inventory(int weight): head(NULL), size(0), maxWeight(0), totWeight(0)
{
	if (weight > 0)
		maxWeight = weight;
	else
		maxWeight = 100;
}


inventory::~inventory()
{
	node* curr = head;
	while (head)	//while head is true
	{
		curr = head->next; //set curr equals to what head points to next
		delete head;		//delete head
		head = curr;		//set what head was pointing to into the new head
	}
}

bool inventory::AddItem(const item& anItem)
{
	node * prev = NULL;
	node * curr = head;
	char   name[100];

	anItem.getName(name);
	if (totWeight + anItem.getWeight() > maxWeight)
	{	
		cout << "You're not strong enough to pick up the " << name << " with everything else you're carrying." << endl;
		return false;
	}
	else
	{
		cout << "You picked up a " << name << '.' << endl;		
	}

	//first find the right position to insert by traversing inventory list
	//this compares if curr is not NULL and curr->Item is less than anItem, exits when not true
	//in comparing type item the < operator is overloaded in item class to check on item.name
	while (curr!=NULL && curr->item < anItem)
	{
		prev = curr;
		curr = curr->next;
	}
	//after exiting this loop anItem should either be equals to (==) or greater than (>) curr->item
	
	//if it equals than the item matches and already exist (OLD ITEM) in the inventory list
	if(curr && curr->item == anItem)
	{
		curr->itemCount += 1;
		size++;
		totWeight += anItem.getWeight();
		return true;
	}	
	//if doesn't equal then it is a NEW ITEM. add it to the inventory list at curr position
	else
	{
		//make new node
		node* newNode = new node;
		newNode->item = anItem;
		newNode->next = NULL;
		newNode->itemCount = 1;

		//put/link new node into inventory list
		newNode->next = curr;
		if(prev == NULL)	
			head = newNode;
		else
			prev->next = newNode;
		size++;
		totWeight += anItem.getWeight();
		return true;	//needed? because currently it's a bool method
	}

	return false;
}

bool inventory::RemoveItem(char * key)
{
	char id[100];
	double itemWeight = 0;

	//uses key to search for the item to remove
	node * prev = NULL;
	node * curr = head;
	while (curr)
	{
		curr->item.getName(id);	//get name of current item and store in id
		itemWeight = curr->item.getWeight();
		if (strcmp(key, id) == 0) //for curr record if key and id is the same
		{
			if (curr->itemCount > 1)	//if item count is more than 1 then just subtract the count
			{
				curr->itemCount -= 1;
				totWeight -= itemWeight;
				size --;
				cout << "You dropped a " << key << '.' << endl;
				return true;
			}
			else						//otherwise itemCount is 1 so delete the entire item from list
			{
				if(!prev)	//if prev is false/NULL curr item to be deleted is the head
					head = curr->next; //reassign curr->next to be head since head will be deleted
				else
					prev->next = curr->next; //make prev point to what curr is pointing to so it skips curr in the middle
				
				delete curr;
				curr = curr->next;
				totWeight -= itemWeight;
				size --;
				cout << "You dropped a " << key << '.' << endl;
				return true;
			}
		}
		prev = curr;
		curr = curr->next;
	}
	//key not in list
	cout << "You don't have a " << key << " in your inventory." << endl;
	return false;
}

int inventory::getSize() const
{
	return size;
}

void inventory::PrintInventory()
{	
	node* curr = head;
	
	cout << endl <<"Current inventory:" << endl;
	
	if (curr == NULL)							//if curr is null then inv has no items
	{
		cout << setw(20) << "(no items)" << endl << endl;
	}
	else	//list has items, go through items and call the overloaded << to print from item class 
	{		
		for(curr = head; curr; curr = curr->next) //from curr go while curr is true, increment to curr->next each time
		{
			cout << setw(10) << '[' << curr->itemCount << ']' << ' ' << curr->item << endl;
		}
		cout << "Total items:  " << size << endl;
		cout << "Total weight: " << totWeight << endl << endl;
	}
}