#include "PathAlgo.h"
using namespace std;

struct AStNode
{
	float f;
	float g;
	SDL_Point parent;
};

class AStarAlgo : public PathAlgo
{
public:
	AStarAlgo(bool** newBars,
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
	map<SDL_Point, AStNode, compare_points> openList;
	map<SDL_Point, AStNode, compare_points> closedList;
	AStNode endLNode;
	AStNode startLNode;
};
