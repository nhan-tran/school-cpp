
/*
CST352 Lab2: nt_lab2_sol3_final.c
Author: Nhan Tran
Desc: An implemenation to the Producer and Consumer problem solution using a spin lock.
The producer will generate a random number and store in a warehouse (int array) while the
consumer will grab items in the warehouse and print them to the screen. 
In solution 3, two semaphores are used to ensure producers can't store items in a warehouse
that is full and also consumers can't grab items in a warehouse that is empty. One semaphore
keeps count of the number of items placed in the warehouse and the other keeps count of the 
number of items taken from the warehouse. A mutex has also been put to use to make sure that
multiple producers and consumers cannot access the buffer at the same time which can cause
data loss and overwrites.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t fillCount;
sem_t emptyCount;
pthread_mutex_t thread_flag_mutex;


void putInWarehouse(int item, int size, int* wh, int* itemCount);
int produceItem();
void consumeItem(int size, int* wh);


void initialize_flag ()
{
  /* Initialize the mutex and condition variable.  */
	//printf("init mutex entered\n");
  pthread_mutex_init (&thread_flag_mutex, NULL);
}


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
					pthread_mutex_lock (&thread_flag_mutex);
						putInWarehouse(item, p->size, p->ptr_wh, p->ptr_itemCount);
					pthread_mutex_unlock(&thread_flag_mutex);
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
			pthread_mutex_lock(&thread_flag_mutex);
				consumeItem(p->size, p->ptr_wh);	//if item was found
			pthread_mutex_unlock(&thread_flag_mutex);
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
	
	int size = 100;	
	int warehouse[size];	
	int i;
	int itemCount = 0;
	pthread_t thread_producer1;
	pthread_t thread_producer2;
	pthread_t thread_producer3;
	pthread_t thread_producer4;
	pthread_t thread_consumer1;
	pthread_t thread_consumer2;
	pthread_t thread_consumer3;
	pthread_t thread_consumer4;

	struct thread_args pc_args;


	sem_init(&fillCount, 0, 0);		//initial value of fillCount is zero since 0 items in buffer

	/*initial value of emptyCount is the size, emptyCount keeps track of the 'open' slots in the buffer. 
	As items are put in emtpyCount will be decremented.*/
	sem_init(&emptyCount, 0, size);

	init_warehouse(size, warehouse);	
	initialize_flag();

	//set thread args
	pc_args.size = size;
	pc_args.ptr_wh = &warehouse[0];
	pc_args.ptr_itemCount = &itemCount;

	//start producer thread
	
	pthread_create (&thread_producer1, NULL, &producer, &pc_args);
	pthread_create (&thread_producer2, NULL, &producer, &pc_args);
	pthread_create (&thread_producer3, NULL, &producer, &pc_args);
	pthread_create (&thread_producer4, NULL, &producer, &pc_args);

	pthread_create (&thread_consumer1, NULL, &consumer, &pc_args);
	pthread_create (&thread_consumer2, NULL, &consumer, &pc_args);
	pthread_create (&thread_consumer3, NULL, &consumer, &pc_args);
	pthread_create (&thread_consumer4, NULL, &consumer, &pc_args);

	pthread_join (thread_producer1, NULL);
	pthread_join (thread_producer2, NULL);
	pthread_join (thread_producer3, NULL);
	pthread_join (thread_producer4, NULL);

	pthread_join (thread_consumer1, NULL);
	pthread_join (thread_consumer2, NULL);
	pthread_join (thread_consumer3, NULL);
	pthread_join (thread_consumer4, NULL);
	
	printf("Producer ended.\n");
	printf("Consumer ended.\n");

	return 0;
}
