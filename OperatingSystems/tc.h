//header to define the functions that will be used for the
//traffic control system test file tc.c
#include "support.h"

//defines the intersections coming from North, South, East or West
#define XSECT_NW 0
#define XSECT_NE 1
#define XSECT_SE 2
#define XSECT_SW 3


//for the number of cars threads that will go through the traffic control system
//which can be determined by user in an Ubuntu command line
int num_cars = 0;

//the minimum, maximum and total time a car spent in the sytem
double min_time = -1.0;
double max_time = -1.0;
double total_time = 0;

//tracks the start and end times for each car
struct timeval per_thread_start_timer[1000];
struct timeval per_thread_end_timer[1000];

//Semaphores to lock each quadrant North, South, East and West
semaphore_t NW;
semaphore_t NE;
semaphore_t SW;
semaphore_t SE;

//limit of 3 cars in the intersection that aren't exiting
semaphore_t XX;


//parse command line
int parse_args(int argc, char **argv);


//This function is for when a car goess straight through the intersection
//from any direction. Has arguments for each Car's ID (car_id) and the original
//direction the car arrives from (dir_original) and its target direction (dir_target)
int drive_through(car_direction_t dir_original, car_direction_t dir_target, int car_id);


//This function is for when a car in any direction decides to turn left
int turning_left(car_direction_t dir_original, car_direction_t dir_target, int car_id);


//This function is for when a car in any direction decides to turn right
int turning_right(car_direction_t dir_original, car_direction_t dir_target, int car_id);


//This function is for when a car is in the intersection, it decides if a car
//is going to turn left, right, or drive through
int enter_intersection(car_direction_t dir_original, car_direction_t dir_target, int car_id);


//This main thread function is for when a car arrives to the intersection
void *arrive_intersection(void *param);
