CMD = g++ -std=c++1y -I/usr/local/include -I/usr/include/SDL2 -w -O0 -g3 -Wall -c -fmessage-length=0 

all: Pathviz-2

Pathviz-2: main Timer PathAlgo SimUtils AStarAlgo DijkstraAlgo MazeGeneratorDepth
	g++ -L/usr/lib -L/usr/local/lib -Xlinker -lSDL2 -lSDL2_image -o "Pathviz-2" main.o Timer.o AStarAlgo.o DijkstraAlgo.o MazeGeneratorDepth.o PathAlgo.o SimUtils.o
main: main.cpp
	$(CMD) main.cpp
Timer: Timer.h Timer.cpp
	$(CMD) Timer.cpp
AStarAlgo: PathAlgo AStarAlgo.h AStarAlgo.cpp
	$(CMD) AStarAlgo.cpp
DijkstraAlgo: PathAlgo DijkstraAlgo.h DijkstraAlgo.cpp
	$(CMD) DijkstraAlgo.cpp
MazeGeneratorDepth: PathAlgo MazeGeneratorDepth.h MazeGeneratorDepth.cpp
	$(CMD) MazeGeneratorDepth.cpp
PathAlgo: SimUtils PathAlgo.h PathAlgo.cpp
	$(CMD) PathAlgo.cpp
SimUtils: SimUtils.h SimUtils.cpp
	$(CMD) SimUtils.cpp

clean:
	rm -f *.o
	rm -f Pathviz-2
