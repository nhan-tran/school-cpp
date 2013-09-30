/*
CIS260 Lab 1: Inventory List
Description: Purpose of main is to test out the inventory class which is a linked list 
that keeps track of item objects from class item. This program tests inventory by making an
inventory list called 'inv' then adds and removes items to it.
Author: Nhan Tran (main.cpp Mike Noel)
Date: 1/25/12
Sources: Mike Noel - linkedListADT project.
*/
#include <iostream>
#include "item.h"
#include "inventory.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace std;

void AddItem(inventory& inv,char* name,double weight)
{
	cout << "Adding " << name << " with a weight of " << weight << "." << endl;
	inv.AddItem(item(name,weight));
}

void RemoveItem(inventory& inv,char* name)
{
	cout << "Removing " << name << "." << endl;
	inv.RemoveItem(name);
}

void doTest() 
{
	inventory inv;

	// Make sure printing an empty inventory works
	inv.PrintInventory();

	// Make sure adding the first one works
	AddItem(inv,"helmet",5);
	inv.PrintInventory();

	// Add some more items
	AddItem(inv,"braclet of power",1);
	AddItem(inv,"red potion",2);
	inv.PrintInventory();

	// Add some duplicates
	AddItem(inv,"braclet of power",1);
	inv.PrintInventory();

	// Add some heavy stuff
	AddItem(inv,"bag of gold coins",50);
	AddItem(inv,"bag of gold coins",50);

	// Now some removes
	RemoveItem(inv,"short sword");
	RemoveItem(inv,"helmet");
	RemoveItem(inv,"braclet of power");
	inv.PrintInventory();

	RemoveItem(inv,"braclet of power");
	RemoveItem(inv,"red potion");
	inv.PrintInventory();
}

int main() {

	doTest();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}