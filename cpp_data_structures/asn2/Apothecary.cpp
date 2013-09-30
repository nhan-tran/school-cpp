/*
Implementation file for Apothecary.h
Author: Nhan Tran
Date: 2/8/12
*/

#include "Apothecary.h"

/******************************
private:
		queue* potionOrders;
		stack* potionShelf;
*******************************/

Apothecary::Apothecary(int orders, int shelf): maxOrders (0), maxShelf (0), cntOrders (0), cntShelf(0)
{
	potionOrders = new queue();
	potionShelf = new stack();
	maxOrders = orders;
	maxShelf = shelf;
}

Apothecary::~Apothecary()
{
	if (potionOrders)
		delete potionOrders;
	if (potionShelf)
		delete potionShelf;
}

bool Apothecary::OrderPotion(PotionType potion)
{
	if (cntOrders == maxOrders)
	//return false if full
	{
		return false; //return false;
	}
	else
	potionOrders->enqueue(potion);
	cntOrders += 1;
	return true;
}

int Apothecary::MakePotions()
{
	PotionType aType;
	Potion aPotion;
	int p = 0; //keeps track of how many potions are added.

	if (potionOrders->isEmpty() || cntShelf >= maxShelf)
	{
		cout << "The shelf of potions is full.  You can't make any more until somebody buys some.";
		return 0;
	}

	while (!potionOrders->isEmpty() && cntShelf <= maxShelf)
	{
		//if queue is not empty but shelf is full display message and return.
		//the purpose of this is when shelf is full and queue is empty there is no shelf is full message.
		if (cntShelf == maxShelf) 
		{
			cout << "The shelf of potions is full.  You can't make any more until somebody buys some.";
			return (p);
		}

		potionOrders->dequeue(aType);
		cntOrders -= 1;

		aPotion.setType(aType);

		potionShelf->push(aPotion);
		cntShelf += 1;
		p += 1;
		cout << "Made a " << PotionTypeString(aType) << " potion." << endl;
	}
	return (p);
}

bool Apothecary::BuyPotion(Potion& potion)
{
	//if pop is true then stack is not empty and pop was successful.
	//pop item and minus cntShelf
	if (potionShelf->pop(potion))
	{
		cntShelf -= 1;
		return true;
	}
	else
		return false;

}