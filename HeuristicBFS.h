#include "PathAlgo.h"
using namespace std;

struct Node
{
	float f;
	float g;
	SDL_Point parent;
};

class HeuristicBFS : public PathAlgo
{
public:
	HeuristicBFS (bool** newBars,
			SDL_Point* newSLoc,
			SDL_Point* newELoc,
			float (*newHeur)(SDL_Point, SDL_Point),
			bool newDiag = true);
	bool step();
	void reset();
	void drawAll(SDL_Renderer* renderer);
protected:
	bool diagonal;
	float (*heuristic)(SDL_Point pos, SDL_Point endLoc);
	map<SDL_Point, Node, compare_points> openList;
	map<SDL_Point, Node, compare_points> closedList;
	Node endLNode;
	Node startLNode;
};
