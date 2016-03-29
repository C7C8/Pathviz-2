#include "MazeGeneratorDepth.h"

MazeGeneratorDepth::MazeGeneratorDepth(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc) : PathAlgo(newBars, newSLoc, newELoc)
{
	reset();
}

bool MazeGeneratorDepth::step()
{
	if (complete)
		return false; //TODO: Fix the need for this hack

	if (!ready) //Setup initial conditions if the algorithm is not prepped. Q&D way of prepping things.
	{
		nodeN = *startLoc;
		ready = true;
	}

	nodeStack.push(nodeN); //Push the current node
	mazeBoard[nodeN.x][nodeN.y] = EMPTY;

	while (!checkAvailable(nodeN))
	{
		//If there are no nodes available to branch into, backtrack until there are
		if (nodeStack.empty())
		{
			complete = true;

			//Copy over barriers to the map
			for (int x = 0; x < CELLX_SIZE; x++)
			{
				for (int y = 0; y < CELLY_SIZE; y++)
				{
					barriers[x][y] = false; //Reset
					if (mazeBoard[x][y] != EMPTY)
						barriers[x][y] = true;
				}
			}

			return false; //Completed
		}
		nodeN = nodeStack.top(); //Make sure that the node we're checking has an open neighbor available.
		nodeStack.pop();
	}

	SDL_Point nodeA;
	SDL_Point temp = {0, 0};
	while (true)
	{
		temp = {0, 0};
		//Pick a random, unvisited cell
		switch (rand() % 4)
		{
			case 0:
				temp.y = -1;
				break;
			case 1:
				temp.x = 1;
				break;
			case 2:
				temp.y = 1;
				break;
			case 3:
				temp.x = -1;
				break;
		}
		nodeA.x = nodeN.x + temp.x;
		nodeA.y = nodeN.y + temp.y;
		if (!boundsCheck({nodeA.x + temp.x, nodeA.y + temp.y}))
			continue;
		if (mazeBoard[nodeA.x + temp.x][nodeA.y + temp.y] == UNEXPLORED)
			break;
	}
	mazeBoard[nodeA.x][nodeA.y] = EMPTY;
	mazeBoard[nodeA.x + temp.x][nodeA.y + temp.y] = EMPTY;

	//Mark nearby cells as walls, depending on the direction travelled.
	if (temp.x != 0)
	{
		if (boundsCheck({nodeA.x, nodeA.y - 1}))
			mazeBoard[nodeA.x][nodeA.y - 1] = EXPLORED;
		if (boundsCheck({nodeA.x, nodeA.y + 1}))
			mazeBoard[nodeA.x][nodeA.y + 1] = EXPLORED;
	}
	if (temp.y != 0)
	{
		if (boundsCheck({nodeA.x - 1, nodeA.y}))
			mazeBoard[nodeA.x - 1][nodeA.y] = EXPLORED;
		if (boundsCheck({nodeA.x + 1, nodeA.y}))
			mazeBoard[nodeA.x + 1][nodeA.y] = EXPLORED;
	}
	nodeStack.push(nodeA);
	nodeN = {nodeA.x + temp.x, nodeA.y + temp.y};
	return true;
}

void MazeGeneratorDepth::reset()
{
	while (!nodeStack.empty())
		nodeStack.pop();
	complete = false;
	blocked = false;
	ready = false;
	for (int x = 0; x < CELLX_SIZE; x++)
	{
		for (int y = 0; y < CELLY_SIZE; y++)
		{
			mazeBoard[x][y] = UNEXPLORED;
		}
	}
}

void MazeGeneratorDepth::drawAll(SDL_Renderer* renderer)
{
	for (int x = 0; x < CELLX_SIZE; x++)
	{
		for (int y = 0; y < CELLY_SIZE; y++)
		{
			if (mazeBoard[x][y] == UNEXPLORED)
				drawCell(renderer, x, y, BARRIER);
			if (mazeBoard[x][y] == EXPLORED)
				drawCell(renderer, x, y, BARRIER);
		}
	}
}

bool MazeGeneratorDepth::checkAvailable(SDL_Point node)
{
	//Basically looks two spaces ahead in the grid in every given direction
	//to see if the algorithm can go to a new place from this point.
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((i && j) || (!i && !j) || !boundsCheck({node.x + (i * 2), node.y + (j* 2)}))
				continue;

			if (mazeBoard[node.x + (i * 2)][node.y + (j * 2)] == UNEXPLORED && mazeBoard[node.x + i][node.y + j] == UNEXPLORED)
				return true;
		}
	}
	return false;
}
