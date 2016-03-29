#include "PathAlgo.h"
#include <stack>
using std::stack;

class MazeGeneratorDepth : public PathAlgo
{
public:
	MazeGeneratorDepth(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc);
	bool step(); 										//ONE step of the generation progress, to visualize the algorithm.
	void reset();										//Completely resets the algorithm.
	void drawAll(SDL_Renderer* renderer);				//Graphics - draw what needs to be drawn
protected:
	bool checkAvailable(SDL_Point node); 				//Checks if there are unvisited neighbors

	enum spotTypes {UNEXPLORED, EXPLORED, EMPTY}; 		//One of these is unused, but only for now
	stack<SDL_Point> nodeStack;							//A stack of nodes visited. First in, last out.
	spotTypes mazeBoard[CELLX_SIZE][CELLY_SIZE];		//Board of the status of all the different
	SDL_Point nodeN;
	bool ready; //Internal use;
};
