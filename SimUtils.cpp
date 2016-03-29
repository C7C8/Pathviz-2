#include "SimUtils.h"

bool compare_points::operator()(const SDL_Point& val1, const SDL_Point& val2) const
{ //BLEEARRRRGGG!
  if(val1.x < val2.x)
    return true;
  if(val1.x > val2.x)
    return false;
  if(val1.y < val2.y)
    return true;
  if(val1.y > val2.y)
    return false;
  return false; //Is the same; is not less than
}

float euclidHeuristic(SDL_Point pos, SDL_Point endLoc)
{
  return sqrt(pow(pos.x - endLoc.x, 2) + pow(pos.y - endLoc.y, 2));
}
float manhattanHeuristic(SDL_Point pos, SDL_Point endLoc)
{
  int dX = abs(pos.x - endLoc.x);
  int dY = abs(pos.y - endLoc.y);
  return dX + dY;
}
float chebyshevHeuristic(SDL_Point pos, SDL_Point endLoc)
{
  int dX = abs(pos.x - endLoc.x);
  int dY = abs(pos.y - endLoc.y);
  return dX > dY ? dX : dY; //Return the greater difference
}

void drawCell(SDL_Renderer* renderer, int cellXPos, int cellYPos, colorTypes color)
{
  SDL_SetRenderDrawColor(renderer,
    colors[color].first, //R
    colors[color].second,//G
    colors[color].third, 0); //B, A

    SDL_Rect spot;
    spot.w = CELL_SIZE;
    spot.h = CELL_SIZE;
    spot.x = (cellXPos * (CELL_SIZE + BORD_SIZE)) + BORD_SIZE;
    spot.y = (cellYPos * (CELL_SIZE + BORD_SIZE)) + BORD_SIZE;
    SDL_RenderFillRect(renderer, &spot);
}
