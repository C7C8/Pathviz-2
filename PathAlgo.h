#pragma once

#include "SimUtils.h"
#include <map>
using namespace std; //TODO: Remove "using namespace std"

/**
* @brief Pathing algorithm abstract base class.
*/
class PathAlgo
{
public:
  PathAlgo(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc);
  virtual ~PathAlgo() {};				//STOP YELLING AT ME, ECLIPSE
  virtual bool step() = 0;				//!< Update the path algorithm ONCE
  bool isComplete() {return complete;}			//!< Has the algorithm completed?
  bool isBlocked() {return blocked;}			//!< Is the path to the target blocked?
  virtual void reset() = 0;				//!< Reset this pathing algorithm.
  virtual void drawAll(SDL_Renderer* renderer) = 0;	//!< Draw all graphics
protected:
  bool boundsCheck(SDL_Point node);			//Make sure maze boundaries are not exceeded.

  bool complete;
  bool blocked;

  bool** barriers;
  SDL_Point* startLoc;
  SDL_Point* endLoc;

};
