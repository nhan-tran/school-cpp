/*
Potion class - Represents a type of Potion object in a RPG game. Each Potion has a type with a eum PotionType value
Author: Nhan Tran
Date: 2/8/12
Sources: Mike Noel - linkedListADT project
*/


#ifndef POTION_H	
#define POTION_H

#include "main.h"
#include <iostream>
using namespace std;
class Potion
{
public:
	Potion();
	Potion(PotionType type);
	Potion(const Potion& aPotion);	//copy constructor use as PotionPtr = new Potion(aPotion)
	~Potion();	//destructor

	PotionType GetType();
	void setType(PotionType& type);
	const Potion& operator=(const Potion& aPotion);	//overloading assignment = operator
	friend ostream& operator <<(ostream& out, const Potion& aPotion);

private:
	PotionType type;
};

#endif