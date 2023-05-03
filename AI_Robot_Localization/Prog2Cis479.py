import numpy as np
import math
import copy

# First initialize the variables of the program that will be constant
# What the actual location of the robot is, random location (the robot doesn't know its location)
# and the number of rows, columns, barriers/obstacles, and empty squares
robot_Location = [3,4]
num_Colmns = 7
num_Rows = 6
barrier = 4
empty_Sqr = (num_Colmns*num_Rows) - barrier  


# Create the Windy Maze the robot will be located in, 7x6
# the "0" values represent the availble, empty squares while the
# "#" are the obstacles
maze_forRobot = [[0,0,0,0,0,0,0],
              [0,'#',0,0,'#',0,0],
              [0,0,0,0,0,0,0],
              [0,'#',0,0,'#',0,0],
              [0,0,0,0,0,0,0],
              [0,0,0,0,0,0,0]]

#checkSurrounding = 0
#evid = 0

# Implements Filtering for the robot in terms of evidence conditional probability
def filtering (maze, evid):
    # allows the spaces in the maze to pass to function
    # Connected to function P(Zt,w,n,e,s|St) for all the spaces
    prior_maze = copy.deepcopy(maze)
    evidence_maze = evidence(maze, evid)

    # check if the total of all spaces is 1 
    z = []
    summation = 0

    # Using normalization by finding the total of all space probabilities
    for i in range(0, num_Rows):
        for j in range (0, num_Colmns):
            # If the space in the maze is not '#' or obstacle
            if maze [i][j] != '#':
                summation += evidence_maze[i][j]          
    summation = summation/empty_Sqr   # 38 empty squares
    
    for i in range(0, num_Rows):
        for j in range(0, num_Colmns):
            num = 0
            normalization = 0

            # Probabilties are then calculated
            if maze[i][j] != '#':
                num = evidence_maze[i][j]*prior_maze[i][j]
                normalization = (num/summation) 
                maze[i][j] = normalization
                # Puts normalization values into a list
                z.append(normalization)
    #c = sum (z)
    # Prints out the sum of the filteration
    #print ("Sum of Filter ", c)
    return maze

# This implements the evidence of the maze, checking if the evidence is actually 
# true or not then giving probabilites for each space
def evidence (maze, evid):
    for x in range (0, num_Rows):
        for y in range (0,num_Colmns):

            if maze [x][y] != '#':
                sight = checkSurrounding([x,y])
                prod = 0
                array = []

                # The robot is sensing the maze, and the different outcomes are
                # initilized by p
                for p in range (0, len(sight)):

                        # For if the robot sensor thinks a space is empty and it is empty
                        if sight[p] == evid[p] and sight [p] == 0:
                            # 85% probability, given
                            t = 0.85
                        
                        # For if the robot sensor thinks a space is blocked and it is blocked
                        if sight[p] == evid[p] and sight[p] == 1:
                            # 80% probability, given
                            t = 0.80
                        
                        # For if the robot sensor thinks a space is blocked but its empty
                        if sight[p] != evid[p] and sight[p] == 0:
                            # 15% probabilty, given
                            t = 0.15

                        # For if the robot sensor thinks a space is empty but its blocked
                        if sight[p] != evid[p] and sight[p] == 1:
                            # 20% probability, given
                            t = 0.20
                        # Puts probability values in a list
                        array.append(t)
                        p += 1
                prod = math.prod(array)
                maze[x][y] = prod

            else: continue
    return maze

# Implements the Robot's prediction for a move, in terms of the prediction function P(St+ 1| Zt)
# Determined after filtering
def prediction (maze, move):
    # allows the spaces in the maze to pass to function after filtering (filtered maze)
    fil = copy.deepcopy(maze)
    # move command
    g = move.index(1)

    array = []
    for i in range(0, num_Rows):
        for j in range(0, num_Colmns):
            # Conected to the maze just filtered by the robot
            # Values for the space that are not obstacles
            if fil[i][j] != '#':
                # This is where the transitional are initialized, but only north and west will be tested
                w = 0 # westward
                n = 0 # northward
                e = 0 # eastward
                s = 0 # southward
                v = 0 # for the probaility of the robot not moving
                r = 0 # the total

                # Moving westward
                if g == 0:
                   if i + 1 < num_Rows:
                      # 10% going south
                      if fil[i+1][j] != '#' : s = fil[i+1][j]*0.10
                      else: v == 0.0 
                   else: v += 0.0 

                   if j + 1 < num_Colmns:
                      # 80% going east
                      if fil[i][j+1] != '#' : e = fil[i][j+1]*0.0 #was 0.80
                      else: v += 0.0 
                   else: v += 0.0

                   if i - 1 > -1:
                      # 10% going north
                      if fil[i-1][j] != '#' : n = fil[i-1][j]*0.10
                      else: v += 0.10 
                   else: v += 0.10

                   if j - 1 > -1:
                      # 80% going west
                      if fil[i][j-1] != '#' : w = fil[i][j-1]*0.80
                      else: v += 0.80 
                   else: v += 0.80

                   v = v*fil[i][j]
                   # the total 
                   r = s + e + n + w + v
                   maze[i][j] = r
                   array.append(r)

                # Moving northward
                if g == 0:
                    if i + 1 < num_Rows:
                        # 80% going south
                        if fil[i+1][j] != '#' : s = fil[i+1][j]*0.80 
                        else: v += 0.0
                    else: v += 0.0

                    if j + 1 < num_Colmns:
                        # 10% going east
                        if fil[i][j+1] != '#' : e = fil[i][j+1]*0.10
                        else: v += 0.10
                    else: v += 0.10

                    if i - 1 > -1:
                        # 80% going north
                        if fil[i-1][j] != '#' : n = fil[i-1][j]*0.0 
                        else: v += 0.80 
                    else: v += 0.80

                    if j - 1 > -1:
                        # 10%  going west
                        if fil[i][j-1] != '#' : w = fil[i][j-1]*0.10
                        else: v += 0.10 
                    else: v += 0.10

                    v = v*fil[i][j]
                    # the total
                    r = s + e + n + w + v
                    maze[i][j] = r
                    array.append(r)

    # the probabilty equals the sum of all the values put into the array
    #t = sum(array)
    #print ("Sum of Prediction", t)        

                
# Implement the transitional probabilities, 
# (Westward, Northward, Eastward, Southward), where "0" is 
# no obstacle was observed and "1" is where an obstacle was observed
def transitional (maze,move):
    global robot_Location
    g = move.index(1)
    sight = checkSurrounding(robot_Location)

    # Initializes array for maze
    for i in maze:
        c = 0
        for j in i:
            # for obstacle in column
            if j == '#':
                c += 1
                continue
            else:
                i[c] = 0.0
                c += 1
    i = robot_Location[0]
    j = robot_Location[1]

    # Transtion matrix for northward annd westward
    # Moving west
    if g == 0:
        # when the obstacle is westward
        if sight[0] == 1:
            # [s, e, n, w, v]
            t = [0.0, 0.10, 0.80, 0.10, 0.80]
            if sight[1] == 0: maze[i-1][j] = t[1] # northward
            if sight[2] == 0: maze[i][j+1] = t[2] # eastward
            if sight[3] == 0: maze[i+1][j] = t[3] # southward
            maze[i][j] = t[4] # robot's location

        else:
            # with probability west
            t = [0.80, 0.10, 0.80, 0.10, 0.0]
            if sight[0] == 0: maze[i][j-1] = t[0] # westward
            if sight[1] == 0: maze[i-1][j] = t[1] 
            if sight[2] == 0: maze[i][j+1] = t[2] 
            if sight[3] == 0: maze[i+1][j] = t[3] 
            maze[i][j] = t[4] 

    # Moving north
    if g == 1:
        # when the obstacle is northward
        if sight[1] == 1:
            # [s, e, n, w, v]
            t = [0.10, 0.0, 0.10, 0.80, 0.80] 
            if sight[0] == 0: maze[i][j-1] = t[0] # westward
            if sight[2] == 0: maze[i][j+1] = t[2] # eastward
            if sight[3] == 0: maze[i+1][j] = t[3] # southward
            maze[i][j] = t[4] # robot's location

        else:
            # with probability north
            t = [0.10, 0.80, 0.10, 0.80, 0.0] 
            if sight[0] == 0: maze[i][j-1] = t[0] 
            if sight[1] == 0: maze[i-1][j] = t[1] # northward
            if sight[2] == 0: maze[i][j+1] = t[2]
            if sight[3] == 0: maze[i+1][j] = t[3]
            maze[i][j] = t[4]

    return maze

# Implements an array for all the ways the spaces in the maze can be stated
def ways():
    way = []
    for a in range(0,4): #north
        for b in range(0,4): #west
            for c in range(0,4): #south
                for d in range(0,4): #east
                    way.append((a,b,c,d))
    return way

# The robot senses its surroundings, where 0 is no obstacle and 1 is an obstacle
def checkSurrounding(Location):
    sense = []
    i = Location[0]
    j = Location[1]

    # Senses westward
    # outside of the maze
    if j - 1 == -1:
        # if there is an obstacle westward
        obstWest = 1
        sense.append(obstWest)
    # in the maze
    else: 
        if maze_forRobot[i][j-1] == '#':
            obstWest = 1
            sense.append(obstWest)
        else:
            # if there isn't an obstacle westward
            obstWest = 0
            sense.append(obstWest)

    # Senses northward
    # ouside of the maze
    if i - 1 == -1:
        obstNorth = 1
        sense.append(obstNorth)
    # in the maze
    else:
        if maze_forRobot[i-1][j] == '#':
            obstNorth = 1
            sense.append(obstNorth)
        else:
            # if there isn't an obstacle northward
            obstNorth = 0
            sense.append(obstNorth)

    # Senses eastward
    if j + 1 == num_Colmns:
        obstEast = 1
        sense.append(obstEast)
    else:
        if maze_forRobot[i][j+1] == '#':
            obstEast = 1
            sense.append(obstEast)
        else:
            obstEast = 0
            sense.append(obstEast)

    # Senses southward
    if i + 1 == num_Rows:
        obstSouth = 1
        sense.append(obstSouth)
    else:
        if maze_forRobot[i+1][j] == '#':
            obstSouth = 1
            sense.append(obstSouth)
        else:
            obstSouth = 0
            sense.append(obstSouth)

    return sense

# Implements the moving of the robot
def move(move):
    global robot_Location
    # move command
    g = move.index(1)
    i = robot_Location[0]
    j = robot_Location[1]

    # Moving west
    if g == 0:
        j = j - 1

    # Moving north
    if g == 1:
        i = i -1

    robot_Location = [i, j]

# Finds the actual sensed state for each space in maze
def getSpace():
    array = []
    for i in range (0, num_Rows):
        l = []
        for j in range (0, num_Colmns):
            loc = [i,j]
            t = checkSurrounding(loc)
            l.append(t)
        array.append(1)

    return array

# Determines how many other spaces within the maze that have similar
# probabilitees
def countProbabilty(maze, probability):
    count = 0
    probability = np.round(probability, 3)
    for i in range (0, num_Rows):
        for j in range (0, num_Colmns):

            # if the value of the space is not an obstacle then the 
            # function will count the number of spaces in the maze with the prob.
            # to the prob. that already passed then return the count number
            if maze[i][j] != '#':
                element = round(maze[i][j], 3)
                if element == probability:
                    count += 1
    return count

# This counts the spaces in the maze that match the state the robot passed
def countSpace(state):
    l = getSpace()
    count = 0
    for i in l:
        for j in i:
            if state ==  j:
                count += 1
    return count


# Function thats changes the probabilties in terms of the actions the robot made
def changeState(probability_state):
    for i in probability_state:
        # in terms of evidence conditional probabilty (P(Zt|St))
        if i == 0.85: i = 0
        if i == 0.15: i = 0
        if i == 0.80: i = 1
        if i == 0.20: i = 1
    return probability_state


# Prints the state of the robot
def printState (state):
    for i in state:
        for j in i:
            if j == '#':
                print('####', end = "   ")
            else:
                # multiply all by 100, given through evidence conditional probability
                j = j*100
                print('{0:.2f}' .format(j), end = "   ")
        print()

# This computes the beginning state and then returns it,
# The robot goes throught the sequence of actions given, with prior
# and posterior probabilites
def begin_state(maze):
    for i in range (0, num_Rows):
        for j in range (0, num_Colmns):
            # Passes the obstacles
            if maze[i][j] == '#':
                continue
            else: 
                maze[i][j] = 1/empty_Sqr
    return maze

if __name__ == '__main__':
    maze = copy.deepcopy(maze_forRobot)

    # for prior 
    start_prior = 1/empty_Sqr

    # for movements northward and westward in sequence of actions
    # N,N,W,W 
    # Sensing action's done by robot
    move_Sequence = [[0,1,0,0], [0,1,0,0], [1,0,0,0], [1,0,0,0]]
    evid_Sequence = [[0,0,0,0], [1,0,0,0], [0,0,0,0], [0,1,0,1], [1,0,0,0]]
    maze = begin_state(maze)

    # Print out the outcome of the robot's sequence of actions
    # Starting with the first location probabilites
    print('\nInitial Location Probabilities')
    printState(maze)

    # loop for all actions after 
    for i in range (0,len(evid_Sequence)):
        #print('Robot location before action: ', robot_Location)

        # generates filtering
        print ('\nFiltering after Evidence', evid_Sequence[i])
        filtering(maze, evid_Sequence[i])
        printState(maze)

        # generates prediction
        if i < len(move_Sequence):
            direction = move_Sequence[i].index(1)
            #if action of robot is west or north
            if direction == 0:
                direction = 'W'
            else: direction = 'N'

            print('\nPrediction after Action', direction)
            prediction(maze, move_Sequence[i])
            printState(maze)

            # for Moving
            move(move_Sequence[i])

    # for the filtering after evidence for the last action
    #print('\nFiltering after Evidence [1,0,0,0]')
    #printState(filtering(maze, [1,0,0,0]))


