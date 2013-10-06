
/*
CST352 Lab2: nt_lab2_sol2_final.c
Author: Nhan Tran
Desc: An implemenation to the Producer and Consumer problem solution using a spin lock.
The producer will generate a random number and store in a warehouse (int array) while the
consumer will grab items in the warehouse and print them to the screen. 
In solution 2, two semaphores are used to ensure producers can't store items in a warehouse
that is full and also consumers can't grab items in a warehouse that is empty. One semaphore
keeps count of the number of items placed in the warehouse and the other keeps count of the 
number of items taken from the warehouse
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t fillCount;
sem_t emptyCount;


void putInWarehouse(int item, int size, int* wh, int* itemCount);
int produceItem();
void consumeItem(int size, int* wh);


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
	int item;
	

	while (1) //do a while (true) for continous or while (n) to limit number of times ran
	{
		item = produceItem();	
		
		sem_wait(&emptyCount);	//down (decrement) the emptyCount. when emptyCount is 0 thread will wait...
		
		putInWarehouse(item, p->size, p->ptr_wh, p->ptr_itemCount);

		sem_post(&fillCount);	//up (increment) the fillCount

	}
}

void putInWarehouse(int item, int size, int* wh, int* itemCount)
{
	int i;
	
	//iterate through array to find empty slot to insert item	
	for (i = 0; i < size; ++i)
	{

		if (wh[i] == 0)		//if empty(0) then insert
		{
			wh[i] = item;
			(*itemCount) += 1;
			printf("Produced wh[%d]: %d ItemCount: %d\n", i, wh[i], (*itemCount));		
			break;		
		}
	}
}


int produceItem()
{
	return rand() % 100 + 1;	//return a number in range 1-100
}


void consumeItem(int size, int* wh)
{
	int i;
	int item;	//item value to return	
	int found = 0;

	//go through buffer and grab first empty slot
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
	
}


//consumer
void* consumer(void* arg)
{
	int item;

	/* Cast the cookie pointer to the right type.  */
	struct thread_args* p = (struct thread_args*) arg;

	while (1)
	{
		sem_wait(&fillCount);	//if the fillCount is 0, meaning the buffer is empty then wait...
		
		consumeItem(p->size, p->ptr_wh);	//if item was found

		sem_post(&emptyCount);	//up the emptyCount	
	}
}

//initialize the slots in warehouse to all zeros, indicating it is empty
void init_warehouse(int limit, int* wh)
{
	int i;
	
	for (i = 0; i < limit; ++i)
		wh[i] = 0;

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


	sem_init(&fillCount, 0, 0);		//initial value of fillCount is zero since 0 items in buffer

	/*initial value of emptyCount is the size, emptyCount keeps track of the 'open' slots in the buffer. 
	As items are put in emtpyCount will be decremented.*/
	sem_init(&emptyCount, 0, size);

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
