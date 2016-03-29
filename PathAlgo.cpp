#include "PathAlgo.h"

PathAlgo::PathAlgo(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc)
{
  barriers = newBars;
  startLoc = newSLoc;
  endLoc = newELoc;
  blocked = false;
  complete = false;
}

bool PathAlgo::boundsCheck(SDL_Point node)
{
	if (node.x < 0 || node.x >= CELLX_SIZE || node.y < 0 || node.y >= CELLY_SIZE)
		return false;
	return true;
}
