
/** intersection.c -- demonstrate the use of designing a lock strategy
 *
 * pthread_mutex_init()
 * pthread_mutex_lock()
 * pthread_mutex_unlock()
 *

Modified
Author: Nhan Tran
Date: 12/1/12
Desc: file modified to use mutexes and to make sure there are no deadlocks.
A car will always try to secure all the quadrant locks needed before entering the
intersection. If all the locks cannot be secured then the car will not hold the 
locks it has. This means cars enter the intersection only if they know their 
path is safe and they do not need to wait on any other cars.

 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "intersection.h"

#define NUMCARS 30

#define lock_NW(CAR) lock(CAR, NW_mutex)
#define lock_NE(CAR) lock(CAR, NE_mutex)
#define lock_SW(CAR) lock(CAR, SW_mutex)
#define lock_SE(CAR) lock(CAR, SE_mutex)

#define unlock_NW(CAR) unlock(CAR, NW_mutex)
#define unlock_NE(CAR) unlock(CAR, NE_mutex)
#define unlock_SW(CAR) unlock(CAR, SW_mutex)
#define unlock_SE(CAR) unlock(CAR, SE_mutex)

/*
  cardirection - The direction the car is pointing.  If it is pointing NORTH,
  it is starting from the South-Eastern corner of the intersection
  and "going straight" means it wants to move SOUTH to NORTH.

  valid options: NORTH, SOUTH, EAST, WEST
					
  carnumber -	The car identifier
*/
static void gostraight(orientation_t cardirection, unsigned int carnumber){
  /*
    UPDATE THE CODE SO NO LINE IS PRINTED UNLESS THE NECESSARY INTERSECTION
    QUADRANTS HAVE BEEN LOCKED.
  */
  switch(cardirection){
  case NORTH:
		//lockGoStraight will continue to spin until it is able to grab all quadrants
		lockGoStraight(carnumber, SE_mutex, NE_mutex);
    		printf("Car %d, Moving South-North\n", carnumber);
   	unlock_SE(carnumber);
		unlock_NE(carnumber);
		break;

  case SOUTH:
		//lockGoStraight will continue to spin until it is able to grab all quadrants
		lockGoStraight(carnumber, NW_mutex, SW_mutex);
    		printf("Car %d, Moving North-South\n", carnumber);
   	unlock_NW(carnumber);
		unlock_SW(carnumber);
		break;

  case EAST:
		//lockGoStraight will continue to spin until it is able to grab all quadrants
		lockGoStraight(carnumber, SW_mutex, SE_mutex);
    		printf("Car %d, Moving West-East\n", carnumber);
   	unlock_SW(carnumber);
		unlock_SE(carnumber);
		break;

  case WEST:
		lockGoStraight(carnumber, NE_mutex, NW_mutex);
    		printf("Car %d, Moving East-West\n", carnumber);
   	unlock_NE(carnumber);
		unlock_NW(carnumber);
		break;
  }
}

static void turnleft(orientation_t cardirection, unsigned int carnumber){
  /*
    UPDATE THE CODE SO NO LINE IS PRINTED UNLESS THE NECESSARY INTERSECTION
    QUADRANTS HAVE BEEN LOCKED.
  */
  switch(cardirection){
  case NORTH:
		lockLeftTurn(carnumber, SE_mutex, NE_mutex, NW_mutex);
 			printf("Car %d, Moving South-West\n", carnumber);
		unlock_SE(carnumber);
		unlock_NE(carnumber);
		unlock_NW(carnumber);
    	break;
  case SOUTH:
		lockLeftTurn(carnumber, NW_mutex, SW_mutex, SE_mutex);
 			printf("Car %d, Moving North-East\n", carnumber);
		unlock_NW(carnumber);
		unlock_SW(carnumber);
		unlock_SE(carnumber);
    	break;
  case EAST:
		lockLeftTurn(carnumber, SW_mutex, SE_mutex, NE_mutex);
		 printf("Car %d, Moving West-North\n", carnumber);
		unlock_SW(carnumber);
		unlock_SE(carnumber);
		unlock_NE(carnumber);
    	break;
  case WEST:
		lockLeftTurn(carnumber, NE_mutex, NW_mutex, SW_mutex);
			printf("Car %d, Moving East-South\n", carnumber);
		unlock_NE(carnumber);
		unlock_NW(carnumber);
		unlock_SW(carnumber);
		break;
  }
}

static void turnright(orientation_t cardirection, unsigned int carnumber){
  /*
    UPDATE THE CODE SO NO LINE IS PRINTED UNLESS THE NECESSARY INTERSECTION
    QUADRANTS HAVE BEEN LOCKED.
  */
  switch(cardirection){
  case NORTH:
	lock_SE(carnumber);
    printf("Car %d, Moving South-East\n", carnumber);
	unlock_SE(carnumber);
    break;
  case SOUTH:
	lock_NW(carnumber);
    printf("Car %d, Moving North-West\n", carnumber);
	unlock_NW(carnumber);
    break;
  case EAST:
	lock_SW(carnumber);
    printf("Car %d, Moving West-South\n", carnumber);
	unlock_SW(carnumber);
    break;
  case WEST:
	lock_NE(carnumber);
    printf("Car %d, Moving East-North\n", carnumber);
	unlock_NE(carnumber);
    break;
  }
}


/*
  Car approaches intersection from one of directions (North, south, east, west),
  picks a random direction (straight, left right) and calls the
  associated function to move in that direction through the intersection.
*/
static void * approachintersection(void* arg){
  unsigned int * carnumberptr;
  unsigned int carnumber;
  orientation_t cardir = (orientation_t)random()%4;
  unsigned long turn = random()%3;
	
  carnumberptr = (unsigned int*) arg;
  carnumber = (unsigned int) *carnumberptr;
	
  if(turn==LEFT){
    turnleft(cardir, carnumber);
  } else if(turn==RIGHT){
    turnright(cardir, carnumber);
  } else {//straight
    gostraight(cardir, carnumber);
  }
	
  return (void*)carnumberptr;
}

int main(int argc, char **argv){
  /* Initial variables*/
  int index, tid;
  unsigned int carids[NUMCARS];
  pthread_t carthreads[NUMCARS];

  /* Start up a thread for each car*/	
  for(index = 0; index <NUMCARS; index++){
    carids[index] = index;
    tid = pthread_create(&carthreads[index], NULL, approachintersection, (void*)&carids[index]);
  }
	
  /* Wait for every car thread to finish */
  for(index = 0; index <NUMCARS; index++){
    pthread_join(carthreads[index], NULL);
  }
  printf("Done\n");
  return 1;
}
