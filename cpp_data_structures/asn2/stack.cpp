/*
Implementation file for stack.h
Author: Nhan Tran
Date: 2/8/12
*/

#include "stack.h"
#include <fstream>
#include <cassert>

/*********************
private:
	s_node * head;
*********************/

stack::stack():head(NULL)
{
}

stack::~stack()
{
	s_node * curr = head;
	while(head)
	{
		curr = head->next;
		delete head;
		head = curr;
	}
	head = NULL;
}

bool stack::push(Potion& aPotion)
{
	//create new s_node
	s_node * newNode = new s_node;
	newNode->item = aPotion;
	newNode->next = NULL;

	//make the new s_node the head
	newNode->next = head;
	head = newNode;

	return true;
}

bool stack::pop (Potion& aPotion)
{
	//empty stack, has nothing to pop
	s_node * temp;
	if(isEmpty())
		return false;
	else
	{
		aPotion = head->item;
		temp = head;
		head = head->next;
		delete temp;
		return true;
	}
}

bool stack::isEmpty () const
{
	return head==NULL;
}

bool stack::peek (Potion& aPotion)const
{
	if(isEmpty())
		return false;
	else
	{
		aPotion = head->item;
		return true;
	}
}

