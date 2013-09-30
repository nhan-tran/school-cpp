/*
Inventory class - Contains all the items a player has in the RPG game. The inventory is implemented
through a linked list sorted by item name. Multiple instances of the same item are kept tracked of
through itemCount.
Author: Nhan Tran
Date: 1/25/12
Sources: Mike Noel - linkedListADT project
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <ostream>
#include "item.h"

class inventory
{
public:
	inventory();			//default constructor
	inventory(int weight);	//constructor to take a specified max weight	
	~inventory();

	bool AddItem(const item& anItem);
	bool RemoveItem(char * key);
	int getSize(void) const;
	int getWeight(); //returns the weight
	void PrintInventory();	//prints all inventory

private:
	struct node
	{
		item	item;
		int		itemCount;
		node*	next;
	};

	node*	head;
	int		size;
	int		maxWeight;
	double	totWeight;
};

#endif