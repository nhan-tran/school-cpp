/*
Implementation file for Potion.h
Author: Nhan Tran
Date: 2/8/12
*/

#include "Potion.h"
#include <iostream>
#include <iomanip>

using namespace std;

/***************************
private:
		PotionTYpe type;
****************************/

Potion::Potion(): type(UNKNOWN)
{
}

Potion::Potion(PotionType type): type(UNKNOWN)
{
	setType(type);
}

Potion::~Potion()	//destructor. no ptrs to delete
{
}


PotionType Potion::GetType()
{
	return type;
}

//overloading = opeartor to copy over Potion types
const Potion& Potion::operator=(const Potion& aPotion)
{
	if(this == &aPotion)
		return *this;
	else
	{
		this->type = aPotion.type;
		return *this;	
	}
}

void Potion::setType(PotionType& type)
{
	this->type = type;
}
	
//overloads the << operator so when you go cout << 'Potion' it will call this and print the following
ostream& operator<<(ostream& out, const Potion& aPotion)
{
	out << "Potion of " << PotionTypeString(aPotion.type) << endl;
	return out;
}
