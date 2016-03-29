CXXFLAGS = -std=c++1y -w -O0 -g3 -Wall

all: Pathviz-2

Pathviz-2: main.o Timer.o PathAlgo.o SimUtils.o AStarAlgo.o DijkstraAlgo.o MazeGeneratorDepth.o
	g++ -Xlinker -lSDL2 -o "Pathviz-2" main.o Timer.o AStarAlgo.o DijkstraAlgo.o MazeGeneratorDepth.o PathAlgo.o SimUtils.o
main.o: Timer.o main.cpp
Timer.o: Timer.h Timer.cpp
AStarAlgo.o: PathAlgo.o AStarAlgo.h AStarAlgo.cpp
DijkstraAlgo.o: PathAlgo.o DijkstraAlgo.h DijkstraAlgo.cpp
MazeGeneratorDepth.o: PathAlgo.o MazeGeneratorDepth.h MazeGeneratorDepth.cpp
PathAlgo.o: SimUtils.o PathAlgo.h PathAlgo.cpp
SimUtils.o: SimUtils.h SimUtils.cpp

clean:
	rm -f *.o
