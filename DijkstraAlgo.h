#pragma once
#include "PathAlgo.h"
using namespace std;

struct DjkNode
{
	float g;
	SDL_Point parent;
};

class DijkstraAlgo : public PathAlgo
{
public:
	DijkstraAlgo(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc);
	bool step();
	void reset();
	void drawAll(SDL_Renderer* renderer);
private:
	map<SDL_Point, DjkNode, compare_points> openList;
	map<SDL_Point, DjkNode, compare_points> closedList;
	DjkNode endLNode;
	DjkNode startLNode;
};
