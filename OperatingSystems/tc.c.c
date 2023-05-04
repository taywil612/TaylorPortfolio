//C file to test the traffic control system, mimicking an intersection sequence of events.
#include "stoplight.h"

int main(int argc, char * argv[]) {
    int ret, i;
	//Each car has its own thread, initialized to NULL
    pthread_t *car_threads = NULL;

	semaphore_create(&NW, 1);
	semaphore_create(&NE, 1);
	semaphore_create(&SW, 1);
	semaphore_create(&SE, 1);
	
	semaphore_create(&XX, 3);

    //parse command line
    if( 0 != (ret = parse_args(argc, argv)) ) {
        return -1;
    }

    //generates random numbers
    srandom(time(NULL));
	
    // This implements the car threads with pthreads
    car_threads = (pthread_t*)malloc(sizeof(pthread_t) * num_cars);
    for(i = 0; i < num_cars; ++i ) {
        if( 0 != (ret = pthread_create(&(car_threads[i]), NULL, arrive_intersection, (void*)(intptr_t)i)) ) {
            fprintf(stderr, "Error: Failed to create a car thread! Ret = %d\n", ret);
            return -1;
        }
    }
	
    //This joins all of the car threads together
    for(i = 0; i < num_cars; ++i ) {
        pthread_join(car_threads[i], NULL);
    }

    //prints the timing information of the traffic control system
    print_footer(1000 * min_time, 1000 * max_time, 1000 * total_time, num_cars);

    if( NULL != car_threads ) {
        free(car_threads);
        car_threads = NULL;
    }

    support_finalize();
	
	semaphore_destroy(&NW);
	semaphore_destroy(&NE);
	semaphore_destroy(&SW);
	semaphore_destroy(&SE);

    return 0;
}

//This function is for the user to input the number of cars that will enter
// (through Ubuntu command line) when throught the traffick contrl system, which has to be greater than zero 
//for the system to work properly, this helps to keep track of all the cars
int parse_args(int argc, char **argv)
{
    if( argc < 2 ) {
        printf("Usage: %s NumCars\n", argv[0]);
        return -1;
    }

	//for the number of cars to pass through the intersection, which cannot be 0
    num_cars = atoi(argv[1]);
    if( num_cars <= 0 ) {
        printf("Error: The number of cars threads must be greater than 0\n");
        return -1;
    }

    support_init();

    //prints the number of cars that will pass the intersection
    printf("Number of Cars: %3d\n", num_cars);
    print_header();

    return 0;
}


 //function that accounts for the car driving through (crossing)
int drive_through(car_direction_t dir_original, car_direction_t dir_target, int car_id)
{
	semaphore_wait(&XX);
	
	//prints Crossing if the car is crossing the intersection
	print_state(car_id, dir_original, dir_target,
			"Crossing(^)",
			get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
	
	//switch function for different directions cars can approach from
	switch(dir_original)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_wait(&SW);
			semaphore_post(&XX);
			semaphore_post(&NW);
			semaphore_post(&SW);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_wait(&SE);
			semaphore_post(&XX);
			semaphore_post(&SW);
			semaphore_post(&SE);
			break;
		case EAST:
			semaphore_wait(&NE);
			semaphore_wait(&NW);
			semaphore_post(&XX);
			semaphore_post(&NE);
			semaphore_post(&NW);
			break;
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_wait(&NE);
			semaphore_post(&XX);
			semaphore_post(&SE);
			semaphore_post(&NE);
	}

    return 0;
}

//Function that accounts for when a car is turning left
int turning_left(car_direction_t dir_original, car_direction_t dir_target, int car_id)
{
	semaphore_wait(&XX);
	
	//prints Turning Left for when a car is crossing but also turning left
    print_state(car_id, dir_original , dir_target,
                "Turning Left(<)",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
	
	//switch function for different directions cars can approach from before turning left
	switch(dir_original)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_wait(&SW);
			semaphore_post(&NW);
			semaphore_wait(&SE);
			semaphore_post(&XX);
			semaphore_post(&SW);
			semaphore_post(&SE);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_wait(&SE);
			semaphore_post(&SW);
			semaphore_wait(&NE);
			semaphore_post(&XX);
			semaphore_post(&SE);
			semaphore_post(&NE);
			break;
		
		case EAST:
			semaphore_wait(&NE);
			semaphore_wait(&NW);
			semaphore_post(&NE);
			semaphore_wait(&SW);
			semaphore_post(&XX);
			semaphore_post(&NW);
			semaphore_post(&SW);
			break;
		
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_wait(&NE);
			semaphore_post(&SE);
			semaphore_wait(&NW);
			semaphore_post(&XX);
			semaphore_post(&NE);
			semaphore_post(&NW);
	}

    return 0;
}


//Function that accounts for a car turning right
int turning_right(car_direction_t dir_original, car_direction_t dir_target, int car_id)
{

    print_state(car_id, dir_original, dir_target,
                "Turning Right(>)",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));

	switch(dir_original)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_post(&NW);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_post(&SW);
			break;
		case EAST:
			semaphore_wait(&NE);
			semaphore_post(&NE);
			break;
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_post(&SE);
	}

    return 0;
}

//Function for when a car enters through the intersection
int enter_intersection(car_direction_t dir_original, car_direction_t dir_target, int car_id)
{
	switch(dir_original)
	{
		case NORTH:
			switch(dir_target)
			{
				case NORTH:
					return -1; // Error: Illegal U-Turn!
				case WEST:
					turning_right(dir_original, dir_target, car_id); 
					break;
				case EAST:
					turning_left(dir_original, dir_target, car_id); 
					break;
				case SOUTH:
					drive_through(dir_original, dir_target, car_id);
			}
			break;
		case WEST:
			switch(dir_target)
			{
				case NORTH:
					turning_left(dir_original, dir_target, car_id); 
					break;
				case WEST:
					return -1; // Error: Illegal U-Turn!
				case EAST:
					drive_through(dir_original, dir_target, car_id); 
					break;
				case SOUTH:
					turning_right(dir_original, dir_target, car_id);
			}
			break;
		
		case EAST:
			switch(dir_target)
			{
				case NORTH:
					turning_right(dir_original, dir_target, car_id); 
					break;
				case WEST:
					drive_through(dir_original, dir_target, car_id); 
					break;
				case EAST:
					return -1; // Error: Illegal U-Turn!
				case SOUTH:
					turning_left(dir_original, dir_target,car_id); 
					break;
			}
			break;
		
		case SOUTH:
			switch(dir_target)
			{
				case NORTH:
					drive_through(dir_original, dir_target, car_id); 
					break;
				case WEST:
					turning_left(dir_original, dir_target, car_id); 
					break;
				case EAST:
					turning_right(dir_original, dir_target, car_id);
				case SOUTH:
					return -1; // Error: Illegal U-Turn!
			}
	}

	return 0;
}


//function for when the car arrives at the intersection from whatever
//direction they are coming from
void *arrive_intersection(void *param)
{
    int car_id = (intptr_t)param;
    car_direction_t dir_original;
    car_direction_t dir_target;
	double car_time = 0;

    (void) car_id; 

	//for when a car arrives from any direction
    dir_original    = random()%4;

	//the car changes directions at random to their "target direction"
	//U-turns can't be done
    do {
        dir_target = random()%4;
    } while(dir_target == dir_original);

  
	// usleep function for when the car "sleeps" while waiting their turn at the entersection
    usleep(random()%TIME_TO_SLEEP);

	//keeps track of the time for the car threads
	gettimeofday(&per_thread_start_timer[car_id], NULL);

    //prints aarrving when the car is at the intersection
    print_state(car_id, dir_original, dir_target,
                "arriving",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));


	//once the car has arrived then it musst enter the intersection and complete it's move
	enter_intersection(dir_original, dir_target, car_id);

	gettimeofday(&per_thread_end_timer[car_id], NULL);
	
	//tracks the car's time and updates the system's overall minimum
	//and maximum time
	car_time = get_timeval_diff_as_double(per_thread_start_timer[car_id], &(per_thread_end_timer[car_id]));

    //prints exiting when the car is no longer in the intersection
    print_state(car_id, dir_original, dir_target,
                "exiting",
                car_time );

  
    //Calculates timing, accounting for all cars
	if(car_time < min_time || min_time == -1.0){
		min_time = car_time;
	}
	
	if(car_time > max_time || max_time == -1.0){
		max_time = car_time;
	}
	
	/* Increment total time */
	total_time += car_time;

    pthread_exit((void *) 0);
    return NULL;
}
