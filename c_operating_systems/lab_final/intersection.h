
/** intersection.h
 *  See intersection.c for modified notes 12/1/12.
 */


//turn directions
typedef enum {
	LEFT=0,
	RIGHT,
	STRAIGHT
} turn_direction_t;

//car direction
typedef enum {
	NORTH=0,
	SOUTH,
	EAST,
	WEST
} orientation_t;

//fucntion declarations
static void gostraight(orientation_t, unsigned int);
static void turnleft(orientation_t, unsigned int);
static void turnright(orientation_t, unsigned int);
static void * approachintersection(void*);
int createcars(int, char**);

//mutexes
pthread_mutex_t NW_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t NE_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SE_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SW_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
	Optional additional code here.
*/

#define lock(CAR, MUTEX) {	      \
    if (pthread_mutex_lock(&MUTEX)) { \
      fprintf(stderr, "pthread_mutex_lock error %d\n", CAR);	\
      exit(-1); \
    } \
  }

#define unlock(CAR, MUTEX) {		\
    if (pthread_mutex_unlock(&MUTEX)) { \
      fprintf(stderr, "pthread_mutex_unlock error %d\n", CAR);	\
      exit(-1); \
    } \
  }

//make sure both quadrants are locked before going straight
#define lockGoStraight(CAR, MUTEX_1, MUTEX_2) { \
	while(1) \
	{					\
	 pthread_mutex_lock(&MUTEX_1); 		\
	  if (pthread_mutex_trylock(&MUTEX_2)) {	\
    		pthread_mutex_unlock(&MUTEX_1);		\
		   pthread_mutex_unlock(&MUTEX_2);		\
			break;				\
		}	\
	 pthread_mutex_unlock(&MUTEX_1);	\
	} \
}

//make sure three quadrants are locked before going straight
//if all three locks cannot be secured then release any locks held and try again
#define lockLeftTurn(CAR, MUTEX_1, MUTEX_2, MUTEX_3) { \
	while(1) \
	{					\
	 pthread_mutex_lock(&MUTEX_1); 		\
	  if (pthread_mutex_trylock(&MUTEX_2)) {	\
			if (pthread_mutex_trylock(&MUTEX_3)) { \
				pthread_mutex_unlock(&MUTEX_1);		\
		   	pthread_mutex_unlock(&MUTEX_2);		\
				pthread_mutex_unlock(&MUTEX_3);		\
				break; 	\
			} \
	 		pthread_mutex_unlock(&MUTEX_2);  \
		}	\
	 pthread_mutex_unlock(&MUTEX_1);	\
	} \
}





