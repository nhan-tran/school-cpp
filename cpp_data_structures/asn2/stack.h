/*
Stack class - Represents a stack ADT and is represented as a shelf in the RPG game. Potions go on the shelf and as new ones are added
the Potion items are pushed back.
Author: Nhan Tran
Date: 2/8/12
Sources: Mike Noel - linkedstack project
*/

#ifndef STACK_H
#define STACK_H

#include "Potion.h"
#include "main.h"

using namespace std;

class stack 
{
public:
	stack(); 
	stack(const stack& aStack);
	~stack();

	bool push(Potion&);
	bool pop(Potion&);

	bool peek(Potion&)const;
	bool isEmpty(void)const;

private:	
	struct s_node
	{
		Potion item;
		s_node * next;
	};
	s_node * head;
};
#endif