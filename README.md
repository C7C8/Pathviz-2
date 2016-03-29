#Pathviz-2

Pathviz-2 is a small visualizer for pathfinding algorithms. Upon starting, the
selected algorithm will try to find its way from the bright green tile (start) 
to the bright red tile (end), showing progress. If a path is found, it will be
highlighted in dark green, and if not the algorithm will alt until reset.

Progress is visualized using red and green squares. Two distinct algorithms are
currently implemented, A* and Dijkstra's, so tiles on the open list are shown as
green and tiles on the closed list are shown as red. 

At the moment the program builds and runs on Linux (tested on Debian) but a
version for windows is planned.

##Algorithms/Modes
To switch modes, press keys 1-8:

1. Dijkstra's
2. A* with euclidean heuristic
3. A* with euclidean heuristic, no diagonals.
4. A* with manhattan heuristic
5. A* with manhattan heuristic, no diagonals
6. A* with Chebyshev heuristic
7. A* with Chebyshev heuristic, no diagonals
8. Maze generator, depth-first


##Controls
To draw barriers (orange) in free space (blue), left-click and drag. To erase
barriers, right-click and drag.

Keys:
* Enter - start/pause algorithm.
* R - reset everything
* A - reset algorithm only, preserving barriers
* F - toggle framerate cap (speeds simulation up)
* S - place the start tile at the mouse's position
* E - place the end tile at the mouse's position
* PGUP - Increase barrier brush size
* PGDN - Decrease barrier brush size

###Maze generator
The maze generator does not behave like the other algorithms. It still starts
at the green start tile, but when selected the screen is filled with orange
barriers that are not truly there; thus any changes you make to barriers will
not appear. When started, the maze generator will use a depth-first algorithm
to generate a random maze for you, but it will not be written to the barrier
map until complete.


##Compiling
You will need to install libsdl2-dev and libsdl2. Then simply extract the
source files to a folder and run "make" to compile.
