/*
Implementation file for queue.h
Author: Nhan Tran
Date: 2/8/12
*/

#include "queue.h"
#include <fstream>
#include <cassert>

/*********************
private:
	q_node * head;
	q_node * tail;
*********************/

queue::queue():head(NULL), tail(NULL)
{
}


//Desc: creates a deep copy of a queue when queue_a = queue_b is used
const queue& queue::operator= (const queue& aQueue)
{
	if(this == &aQueue)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		q_node * curr = head;
		while(head)
		{
			curr = head->next;
			delete head;
			head = curr;
		}

		//make a deep copy of aQueue
		if(aQueue.head == NULL) 
		{
			head = tail = NULL;
		}
		else
		{
			//copy first q_node
			head = new q_node;
			assert(head != NULL); //If this expression evaluates to 0, this causes an assertion failure that terminates the program.
			head->item = aQueue.head->item;

			//copy the rest of the queue
			q_node * destNode = head;				//points to the last q_node in new queue
			q_node * srcNode = aQueue.head->next;    //points to q_node in aQueue
			while(srcNode != NULL)
			{
				destNode->next = new q_node;
				assert(destNode->next != NULL);
				destNode = destNode->next;
				destNode->item = srcNode->item;

				srcNode = srcNode->next;
			}
			destNode->next = NULL;

			//set tail pointr
			tail = destNode;
		}	
		return *this;
	}
}

queue::~queue()
{
	q_node * curr = head;
	while(head)
	{
		curr = head->next;
		delete head;
		head = curr;
	}
	head = tail = NULL;
}

bool queue::enqueue(const PotionType& aType)
{	
	//add to the tail 	
	q_node * newNode = new q_node;
	assert(newNode);
	newNode->item = aType;
	newNode->next = NULL;

	if(tail == NULL)	//if tail, which points to the last Node, is null it means queue is empty
		head = tail = newNode;
	else
	{
		tail->next = newNode;	//make the tail (last q_node) ->next point to latest addition
		tail = newNode;			//then make that latest addition the new last q_node
	}

	return true;
}

bool queue::dequeue (PotionType& aType)
{
	//empty stack, has nothing to pop
	if(isEmpty())
		return false;
	else
	{
		q_node * temp = head;
		if(head == tail) //the only q_node
			head = tail = NULL;
		else
			head = head->next;

		temp->next = NULL;
		aType = temp->item;
		delete temp;
		return true;
	}
}

bool queue::isEmpty () const
{
	return head == NULL;
}

bool queue::peek (PotionType& aType)const
{
	if(isEmpty())
		return false;
	else
	{
		aType = head->item;
		return true;
	}
}