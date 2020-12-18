# WillieTheJanitor
Pathfinding simulation for lunch-stealing janitor with some consumptive tendencies...

FINAL PROJECT INTRO PROGRAMMING CLASS (Summer 2020)

Willie has a drinking problem. And when he falls off the wagon, it's almost always 30 days before he cleans up again. Everyday during that time he will get drunk at work and usually end up in a hedge or a closet or a basement sleeping it off. Here, I have created a program to help Willie simulate his behavior for a day.

Big Picture: the main function will loop on a call to a simulation() function for the specified number of days (one simulation per day).  A simulation runs until either the janitor object dies of bac poisoning or he catches the lunch or he falls out a window. It will collect stats and report
  1. percentage of window exits (which does not kill the janitor, he just sleeps it off in bushes and start fresh the next day)
  2. percentage of successes in catching the lunch
  3. average number of bruises incurred during a day of chasing the lunch
  4. average bac when the day is done

A day (that's one simulation run) finishes if
  1. the janitor falls out a window
  2. catches the lunch
  3. dies of alcohol poisoning

Janitor Notes:
  1. steps "into" a wall: he doesn't move but receives a bruise. (He doesn't actually step into a wall, he tries to but bonks his head.)
  2. steps into a window: he falls out (and sleeps in the bushes).
  3. steps into a cell where the lunch is, he wins for the day .
  4. steps on a cell where there is a drink, he will then consume that drink and "suffer" the effect (his bac is adjusted accordingly). That drink is removed from the grid.

The lunch (a.k.a. "the sandwich") will move about the floor at random. The janitor and lunch take turns stepping. The lunch will always move randomly. But the new janitor in this program will have two modes of moving: one is random; and one is semi-intelligent. As the janitor moves, he loses and gains bac "points". His bac will determine his method of movement. After the simulation runs to completion, the stats are reported and the program ends.

Legend of Map Entities:
'--' Upper / Lower Wall
'|' Side Wall
' ' When flanked by wall, a window. Else, freely movable space.
'J' Janitor
'L' Lunch
'D' Drink
'T' Trap

Note: This simulation output will be seen in console. A small "rest" period between each new update is established with a usleep() function. The current input parameter of 20000 was set based on my own system settings, but may need to be adjusted for other setups for smooth/readable transitions.


This simulation relies on five classes:

school class:
--------------
member variables:
a 2-dim array of chars statically declared for MAX size of 25 x 25
a short integer describing the actual size of the school ( <= MAX).  The grid is square.

member functions:
a constructor that allows you to pass in a grid (array) size and defaults to MAX. This constructor will call private functions that will clear() the grid, then a build() function that will place walls and windows as described below.
an overloaded insertion operator
appropriate accessor/mutator (set/get) functions.

Notes on School:
  1. Windows declared every n spaces. Windows cannot be in corners.
  2. "School" is built on some subset of statically-cast 25x25 grid square. This is to avoid complexity of dynamic array allocation. 

Example School Representation:

  ---- ---- ---- ---- ----
  |                      |
  |                      |
  |                      |
  |                      |
  
  |                      |
  |                      |
  |                      |
  ---- ---- ---- ---- ----

janitor class:
--------------
member variables:
a member for the janitor's blood alcohol content (bac).
a member for the number of bruises.
appropriate variable(s) for his location on the grid (in the school).
a char for how he/she is to be represented.  J seems like a good choice.
state variable(s) to represent whether he/she is sober, drunk, or dead.
a string for his/her name.
a bool for whether janitor is drunk or not.

member functions:
a constructor that takes arguments for character to represent the janitor and defaults it to 'J', and name. His/her bac will always start at .05, bruises at 0, and he'll/she'll be (alive and) sober. Default the start position to (-1,-1).
a place_me() function that has a reference parameter of type school. It will determine the dimensions of the school, and from that will place the janitor in the school's grid and change the janitor's (private) coordinates. The program will attempt to place Willie as close to center as possible.
a rand_walk function() that has a reference to a school parameter. It will pick a random direction in which to take a step, and it will change its own coordinates and the location it occupies in the school passed to it. Willie uses this walking function when drunk.
a smart_walk function() that has a reference to a school parameter and a lunch position parameter. Based on the lunch parameter, the janitor will pick the shortest possible single-step move he/she can take towards the lunch regardless of drink or trap.
a print() function or overloaded insertion operator.

lunch class:
------------
member variables:
a member for location.
a char member for its representation.
a "trapped" bool. When trapped, the lunch will be unable to move.

member functions:
a constructor that initializes the location variable(s) to (-1, -1).
a place_me() function to which you pass a school (by ref). It will place the lunch in the school at a random location in the school based on the dimensions of the school and not on top of anything else.
a random_move() function much like that for janitor. Yes, the lunch is soo moldy that it has grown legs.

drink class:
------------
member variables:
a member string for description (whiskey or coffee)
a float member for "effect". The value of this member will be determined for each object by the constructor. It will be interpreted this way: if the value is negative, it is coffee; if it is positive, it is whiskey. Zero is an unacceptable value. This value will affect its consumer by increasing or decreasing his (the janitor) bac by that amount.

member function:
A constructor that will assign to its "effect" variable at random from the following intervals: [-.010, -0.001] and [0.05, 0.10]. This will determine the name of the drink, too.

trap class:
-----------
member variables:
char representation
