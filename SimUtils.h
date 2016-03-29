#pragma once
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <map>
using std::map;

//General simulation parameters.
#define WINX_SIZE 	1280
#define WINY_SIZE 	680
#define BORD_SIZE 	2
#define CELL_SIZE 	8
#define CELLX_SIZE (WINX_SIZE / (BORD_SIZE + CELL_SIZE))
#define CELLY_SIZE (WINY_SIZE / (BORD_SIZE + CELL_SIZE))

enum colorTypes {BLANK, BARRIER, CLOSED, OPEN, PATH, START, END};

void drawCell(SDL_Renderer* renderer, int cellXPos, int cellYPos, colorTypes color);

//Heuristic functions
float euclidHeuristic(SDL_Point pos, SDL_Point endLoc);
float manhattanHeuristic(SDL_Point pos, SDL_Point endLoc);
float chebyshevHeuristic(SDL_Point pos, SDL_Point endLoc);

class compare_points
{ // simple comparison function
public:
	bool operator()(const SDL_Point& val1, const SDL_Point& val2) const;
};


//Stupid triplet struct for colors, because ColorRGB won't work like that.
struct TripleInt
{
	int first;
	int second;
	int third;
};

const TripleInt colors[] =
{
	{0, 0, 255},		//Blank, blue
	{255, 128, 0},		//Barrier, orange
	{153, 0, 0},		//Closed, dark red
	{0, 153, 0},		//Open, green
	{3, 92, 12},		//Path, dark green
	{0, 255, 0},		//Start, pure green
	{255, 0, 0}			//Red, pure end
};
