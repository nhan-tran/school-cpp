/*
Queue class - Represents a queue ADT and is implemented as a order queue in the RPG game. PotionType orders are requested and added to
the order queue and as orders are added they go to the back of the queue.
Author: Nhan Tran
Date: 2/8/12
Sources: Mike Noel - linkedqueue project
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "Potion.h"

class queue 
{
public:
	queue(); 
	~queue();

	const queue& operator= (const queue& aQueue);

	bool enqueue(const PotionType& aType);
	bool dequeue(PotionType& aType);

	bool peek(PotionType& aType)const;
	bool isEmpty(void)const;

private:
	struct q_node
	{
		PotionType	item;
		q_node *		next;
	};
	q_node * head;
	q_node * tail;
};
#endif