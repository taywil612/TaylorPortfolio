This project is made to be a reflection of a traffic control system. The goal of this project is to implement this system with pthread lock(s) and semaphores. 
What was known about this traffic control system is that it controls traffic at an intersection where cars can come from the North, South, East, or West. 
This was implemented in the project through semaphores and pthreads where each car, which can come from any direction, has its own thread (screenshot #1).

From any direction, the car has the ability to three different tasks, drive through the intersection(int drive_through), which in the output is denoted as “crossing”, 
turn left (int turning_left) from their position, denoted as “Turning Left(<)” in the output, or turn right (int turning_right) from their position, denoted as 
“Turning Right(>)” in the output. However, in no way could the cars perform any U-turns. 

Each of these possible actions the cars can take were made into functions, where within have a switch function that takes each car’s original direction (dir_original)
and sorts by different cases of whatever way the car decides to go (North, South, East, West), an example is shown from the drive_through function in screenshot #2. 
here are also different functions made to account for the car’s location, when the car has entered the intersection and is performing its action (int enter_intersection)
(screenshot #3) and for when the car arrives at the intersection (void *arrive_intersection) and exits, a usleep function is present for when the car is waiting to 
arrive as well (screenshot #4).


The layout of this project is a little different in terms of format, and the time at which each car arrives and exits. I set it to have each car randomly pick an action 
to take at the intersection to save time on having to create each car's individual actions. I did this so that when testing I can pick out however many cars I want to 
go through the intersection and see if they perform the actions required within a reasonable time frame (as seen in outputs screenshots). Overall, the output is not 
identical, but cars from different directions are able to pass through the intersections in a reasonable amount of time, going either straightforward, turning left or 
right, then exiting. The output displays the car ID, the car’s original direction, the car’s target direction, the actions they perform in order, and the time in double.


