/*
Apothecary class - Represents an Apothecary in the RPG game. Apothecary shops can be found throughout the realm and 
can take potion orders, which go into an order queue (potionOrders). The shops then periodically gets serviced and 
orders and then made into actual potions. Made potions are placed on shop's shelf (potionShelf) where the newest potion
is always placed in front. The front potion on the shelf can then be bought by the player.
Author: Nhan Tran
Date: 2/8/12
Sources:
*/

#ifndef APOTHECARY_H
#define APOTHECARY_H

#include "main.h" 
#include "Potion.h"
#include "queue.h"
#include "stack.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Apothecary
{
public:
	Apothecary(int orders, int shelf);
	~Apothecary();

	bool OrderPotion(PotionType potion);
	int MakePotions();
	bool BuyPotion(Potion& potion);
	
private:
	int maxOrders;
	int maxShelf;
	int cntOrders;
	int cntShelf;


	queue* potionOrders;
	stack* potionShelf;

};


#endif