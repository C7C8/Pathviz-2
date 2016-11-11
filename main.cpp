#include <SDL2/SDL.h>
#include "SimUtils.h"
#include "HeuristicBFS.h"
#include "MazeGeneratorDepth.h"
#include "Timer.h"
#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
	//Init
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Pathviz-2",  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINX_SIZE, WINY_SIZE, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		return 1;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		return 1;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Black, default

	//Repetitive things
	SDL_Rect screenRect;
	screenRect.x = 0;
	screenRect.y = 0;
	screenRect.w = WINX_SIZE;
	screenRect.h = WINY_SIZE;

	//Persistent things
	bool* barriers[CELLX_SIZE];
	for (int i = 0; i < CELLX_SIZE; i++)
	{
		barriers[i] = new bool[CELLY_SIZE];
		for (int j = 0; j < CELLY_SIZE; j++)
			barriers[i][j] = false;
	}
	int brushSize = 2;
	SDL_Point startLoc = {0, 0}, endLoc = {CELLX_SIZE - 1, CELLY_SIZE - 1};
	bool lBtnHld = false, rBtnHld = false;
	bool algoPaused = true;

	PathAlgo* djkalgo 	= new HeuristicBFS(barriers, &startLoc, &endLoc, &nullHeuristic);
	PathAlgo* astalgo 	= new HeuristicBFS(barriers, &startLoc, &endLoc, &euclidHeuristic);
	PathAlgo* astalgoNDiag	= new HeuristicBFS(barriers, &startLoc, &endLoc, &euclidHeuristic, false);
	PathAlgo* astMnhtDiag	= new HeuristicBFS(barriers, &startLoc, &endLoc, &manhattanHeuristic);
	PathAlgo* astMnhtNDiag	= new HeuristicBFS(barriers, &startLoc, &endLoc, &manhattanHeuristic, false);
	PathAlgo* astChebDiag	= new HeuristicBFS(barriers, &startLoc, &endLoc, &chebyshevHeuristic);
	PathAlgo* astChebNDiag	= new HeuristicBFS(barriers, &startLoc, &endLoc, &chebyshevHeuristic, false);
	PathAlgo* mazeGenerate 	= new MazeGeneratorDepth(barriers, &startLoc, &endLoc);
	PathAlgo* currentAlgo = astalgo;

	//Game loop-relevant things
	Timer fpstimer;
	bool fpsEnabled = true;
	bool quit = false;
	while (!quit)
	{
		fpstimer.reset();
		fpstimer.start();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.button.button == SDL_BUTTON_RIGHT) //vg ack nf, sdl shit
			{
				if (event.button.type == SDL_MOUSEBUTTONDOWN)
				rBtnHld = true;
				if (event.button.type == SDL_MOUSEBUTTONUP)
				rBtnHld = false;
			}
			if (event.button.button == SDL_BUTTON_LEFT) //vg ack nf, sdl shit
			{
				if (event.button.type == SDL_MOUSEBUTTONDOWN)
					lBtnHld = true;
				if (event.button.type == SDL_MOUSEBUTTONUP)
					lBtnHld = false;
			}
			if (lBtnHld || rBtnHld)
			{
				//Get raw mouse position values, relative to window
				int mX = event.button.x;
				int mY = event.button.y;

				//Skip out-of-bounds cursor values.
				if (mX <= 0 || mY <= 0 || mX >= WINX_SIZE || mY >= WINY_SIZE)
					continue;

				//Determine the cell that the mouse is hovering over
				int xTilePos = mX / (CELL_SIZE + BORD_SIZE);
				int yTilePos = mY / (CELL_SIZE + BORD_SIZE);

				//Create a "brush" area that will be covered, and apply it
				for (int x = 0; x < brushSize; x++)
				{
					for (int y = 0; y < brushSize; y++)
					{
						SDL_Point spot;
						spot.x = xTilePos + x;
						spot.y = yTilePos + y;

						if (spot.x >= CELLX_SIZE
							|| spot.x < 0
							|| spot.y >= CELLY_SIZE
							|| spot.y < 0)
							continue;

						//Verify spot is not over endloc or startloc
						if ((spot.x == startLoc.x
							&& spot.y == startLoc.y)
							|| (spot.x == endLoc.x
							&& spot.y == endLoc.y))
							continue;

						if (lBtnHld)
							barriers[spot.x][spot.y] = true;
						else if (rBtnHld)
							barriers[spot.x][spot.y] = false;
					}
				}
			}
			if (event.key.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_r)
				{
					algoPaused = true;

					for (int x = 0; x < CELLX_SIZE; x++)
					{
						for (int y = 0; y < CELLY_SIZE; y++)
							barriers[x][y] = false;
					}

					startLoc = {0, 0};
					endLoc = {CELLX_SIZE - 1, CELLY_SIZE - 1};
					currentAlgo->reset();
					mazeGenerate->reset();
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					currentAlgo->reset();
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_PAGEUP)
				{
					brushSize++;
					cout << "Brush size set to " << brushSize << endl;
				}
				else if (event.key.keysym.sym == SDLK_PAGEDOWN && brushSize > 1)
				{
					brushSize--;
					cout << "Brush size set to " << brushSize << endl;
				}
				else if (event.key.keysym.sym == SDLK_e)
				{
					int mX, mY;
					SDL_GetMouseState(&mX, &mY);
					endLoc.x = mX / (CELL_SIZE + BORD_SIZE);
					endLoc.y = mY / (CELL_SIZE + BORD_SIZE);
					barriers[endLoc.x][endLoc.y] = false;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					int mX, mY;
					SDL_GetMouseState(&mX, &mY);
					startLoc.x = mX / (CELL_SIZE + BORD_SIZE);
					startLoc.y = mY / (CELL_SIZE + BORD_SIZE);
					barriers[startLoc.x][startLoc.y] = false;
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
					algoPaused = !algoPaused;
				else if (event.key.keysym.sym == SDLK_f)
				{
					fpsEnabled = !fpsEnabled;
					if (fpsEnabled)
						cout << "Capping FPS to approximately 60 FPS." << endl;
					else
						cout << "Disabling framerate cap." << endl;
				}
				else if (event.key.keysym.sym == SDLK_1)
				{
					cout << "Switched to Dijkstra's Algorithm" << endl;
					currentAlgo = djkalgo;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_2)
				{
					cout << "Switched to A* Algorithm (Euclidean heuristic)" << endl;
					currentAlgo = astalgo;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_3)
				{
					cout << "Switched to A* Algorithm (Euclidean heuristic, no diagonals)" << endl;
					currentAlgo = astalgoNDiag;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_4)
				{
					cout << "Switched to A* Algorithm (Manhattan heuristic)" << endl;
					currentAlgo = astMnhtDiag;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_5)
				{
					cout << "Switched to A* Algorithm (Manhattan heuristic, no diagonals)" << endl;
					currentAlgo = astMnhtNDiag;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_6)
				{
					cout << "Switched to A* Algorithm (Chebyshev heuristic)" << endl;
					currentAlgo = astChebDiag;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_7)
				{
					cout << "Switched to A* Algorithm (Chebyshev heuristic, no diagonals)" << endl;
					currentAlgo = astChebNDiag;
					algoPaused = true;
				}
				else if (event.key.keysym.sym == SDLK_8)
				{
					cout << "Switched to Maze Generator" << endl;
					currentAlgo = mazeGenerate;
					algoPaused = true;
				}
			}
		}

		if (!algoPaused && !currentAlgo->isComplete())
			currentAlgo->step();

		while (!fpstimer.hasIntervalPassed(17) && fpsEnabled);

		SDL_SetRenderDrawColor(renderer, colors[BLANK].first, colors[BLANK].second, colors[BLANK].third, 0);
		SDL_RenderFillRect(renderer, &screenRect);

		/**DRAW GRID**/
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Pure black
		SDL_Rect spot;
		spot.h = WINY_SIZE;
		spot.w = BORD_SIZE;
		spot.y = 0;
		for (int x = 0; x <= CELLX_SIZE; x++)
		{ //Draw vertical lines
			spot.x = x * (CELL_SIZE + BORD_SIZE);
			SDL_RenderFillRect(renderer, &spot);
		}

		spot.h = BORD_SIZE;
		spot.w = WINX_SIZE;
		spot.x = 0;
		for (int y = 0; y <= CELLY_SIZE; y++)
		{ //Draw horizontal lines
			spot.y = y * (CELL_SIZE + BORD_SIZE);
			SDL_RenderFillRect(renderer, &spot);
		}

		//Draw barriers
		for (int x = 0; x < CELLX_SIZE; x++)
		{
			for (int y = 0; y < CELLY_SIZE; y++)
			{
				if (barriers[x][y])
					drawCell(renderer, x, y, BARRIER);
			}
		}

		currentAlgo->drawAll(renderer);

		//Draw endloc, startloc
		drawCell(renderer, startLoc.x, startLoc.y, START);
		drawCell(renderer, endLoc.x, endLoc.y, END);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
