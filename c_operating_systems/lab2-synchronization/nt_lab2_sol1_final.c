
/*
CST352 Lab2: nt_lab2_sol1_final.c
Author: Nhan Tran
Desc: An implemenation to the Producer and Consumer problem solution using a spin lock.
The producer will generate a random number and store in a warehouse (int array) while the
consumer will grab items in the warehouse and print them to the screen. A spin lock is used
to ensure producers can't store items in a warehouse that is full and also consumers can't
grab items in a warehouse that is empty.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void putInWarehouse(int item, int size, int* wh, int* itemCount);
int produceItem();
int consumeItem(int size, int* wh);


struct thread_args
{
	int size;
	int* ptr_wh;	//pointer to the warehouse
	int* ptr_itemCount;	//itemCount
};


//producer
void* producer(void* arg)
{
	/* Cast the cookie pointer to the right type.  */
	struct thread_args* p = (struct thread_args*) arg;
	int x = (*p->ptr_itemCount);
	int y = p->size;
	
	int i = 0;
	int item;
	
	printf("Producer Entered\n");

	printf("itemCount: %d\n", x); // (*itemCount));
	printf("size: %d\n", p->size);

	while (1) //do a while (true) for continous or while (n) to limit number of times ran
	{
		item = produceItem();
		//printf("Item created: %d\n", item);	

		while ((*p->ptr_itemCount) == p->size);	//spin lock: continously spins when itemCount is equal to size meaning buffer full.
		//{ printf("producer spinning. . .[%d]\n", i); }		

		putInWarehouse(item, p->size, p->ptr_wh, p->ptr_itemCount);
		i++;

		//printf("itemCount: %d\n", (*p->ptr_itemCount));
	}
}

void putInWarehouse(int item, int size, int* wh, int* itemCount)
{
	int i;
	
	//printf("putInWarehouse entered\n");

	//iterate through array to find empty slot to insert item	
	for (i = 0; i < size; ++i)
	{
		//printf("itemCount: %d\n", (*itemCount));	

		//printf("wh[%d] %d\n", i, (*itemCount));

		if (wh[i] == 0)		//if empty(0) then insert
		{
			wh[i] = item;
			(*itemCount) += 1;
			printf("Produced wh[%d]: %d\n", i, wh[i]);		
			break;		
		}
	}
}


int produceItem()
{
	return rand() % 100 + 1;	//return a number in range 1-100
}


int consumeItem(int size, int* wh)
{
	int i;
	int item;	//item value to return	
	int found = 0;

	for (i = 0; i < size; i++)
	{
		if (wh[i] != 0)	//if slot is not empty
		{
			item = wh[i];	//get item
			wh[i] = 0;		//clear slot
			found = 1;			
			break;		
		}
	}
	
	if (found)		//item was found (true)
		printf("consumeItem: wh[%d] %d\n", i, item);	//item found in [i]			
	//else					//some how item was not found
		//printf("consumeItem: cannot find an item\n");

	return found;
}


//consumer
void* consumer(void* arg)
{
	int item;

	/* Cast the cookie pointer to the right type.  */
	struct thread_args* p = (struct thread_args*) arg;
	int x = (*p->ptr_itemCount);
	int y = p->size;

	printf("Consumer entered.\n");

	while (1)
	{
		while ((*p->ptr_itemCount) == 0);	//spin if empty
		//{printf("consumer spinning...\n");}
		
		if (consumeItem(p->size, p->ptr_wh))	//if item was found
			(*p->ptr_itemCount) -= 1;		
	}
}



void init_warehouse(int limit, int* wh)
{
	int i;
	
	for (i = 0; i < limit; ++i)
	{	
		wh[i] = 0;
	}
}



int main(int argc, char* argv[])
{
	
	int size = 10;	
	int warehouse[size];	
	int i;
	int itemCount = 0;
	pthread_t thread_producer;
	pthread_t thread_consumer;
	struct thread_args pc_args;

	init_warehouse(size, warehouse);

	//set thread args
	pc_args.size = size;
	pc_args.ptr_wh = &warehouse[0];
	pc_args.ptr_itemCount = &itemCount;

	//start producer thread
	
	pthread_create (&thread_producer, NULL, &producer, &pc_args);

	pthread_create (&thread_consumer, NULL, &consumer, &pc_args);

	pthread_join (thread_producer, NULL);
	pthread_join (thread_consumer, NULL);
	
	printf("Producer ended.\n");
	printf("Consumer ended.\n");

	return 0;
}
