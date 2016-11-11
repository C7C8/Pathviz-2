#include "HeuristicBFS.h"

HeuristicBFS::HeuristicBFS(bool** newBars,
	SDL_Point* newSLoc,
	SDL_Point* newELoc,
	float (*newHeur)(SDL_Point, SDL_Point),
	bool newDiag) : PathAlgo(newBars, newSLoc, newELoc)
{
	heuristic = newHeur;
	diagonal = newDiag;
}

bool HeuristicBFS::step()
{
	//Basically the same as Dijkstra's, but with a HEURISTIC!

	//Pre-check
	if (blocked || complete)
	{
		if (openList.size() == 0)
			blocked = true;
		return false;
	}

	//Setup initial conditions
	if (openList.count(*startLoc) == 0 && closedList.count(*startLoc) == 0)
	{
		startLNode.f = 0;
		openList[*startLoc] = startLNode;
	}

	//Get the lowest F-val node - sorting won't work here.
	SDL_Point currentCoord;
	Node currentNode;
	float lowVal = 9999999;
	for (auto iter = openList.begin(); iter != openList.end(); iter++)
	{
		if (iter->second.f < lowVal) //vg ack 
		{
			lowVal = iter->second.f;
			currentCoord = iter->first;
			currentNode = iter->second;
		}
	}
	openList.erase(currentCoord); //Pop off of open list.

	for (int iX = -1; iX <= 1; iX++)
	{
		for (int iY = -1; iY <= 1; iY++)
		{
			if (iX == 0 && iY == 0)
				continue; //Skip self

			if ((iX && iY) && !diagonal)
				continue;

			SDL_Point newCoord = {currentCoord.x + iX, currentCoord.y + iY};
			if (newCoord.x < 0 || newCoord.x >= CELLX_SIZE || newCoord.y < 0 || newCoord.y >= CELLY_SIZE)
				continue; //Bounds check

			if (barriers[newCoord.x][newCoord.y])
				continue; //Ignore barriers

			if (newCoord.x == endLoc->x && newCoord.y == endLoc->y)
			{
				complete = true;
				endLNode.parent = currentCoord;
				closedList[*endLoc] = endLNode;
				closedList[currentCoord] = currentNode;
				return false;
			}

			Node newNode;
			newNode.g = currentNode.g + 1;
			newNode.parent = currentCoord; //Parents the new node to the current node coords
			if (iX && iY)
				newNode.g += 0.41; //Diagonal cost is greater
			newNode.f = newNode.g + heuristic(newCoord, *endLoc);

			if (openList.count(newCoord) == 0 && closedList.count(newCoord) == 0)
				openList[newCoord] = newNode;
			if (openList.count(newCoord) > 0)
			{
				if (openList[newCoord].f > newNode.f) //vg ack, REMOVE MAP USAGE!
					openList[newCoord] = newNode;
				else
					continue;
			}
			if (closedList.count(newCoord) > 0)
			{
				if (closedList[newCoord].f > newNode.f)
				{
					openList[newCoord] = newNode;
					closedList.erase(newCoord);
				}
			}

		}
	}
	closedList[currentCoord] = currentNode;
	return true;
}

void HeuristicBFS::reset()
{
	openList.clear();
	closedList.clear();
	complete = false;
	blocked = false;
}

void HeuristicBFS::drawAll(SDL_Renderer* renderer)
{
	//Open nodes
	for (auto iter = openList.begin(); iter != openList.end(); iter++)
		drawCell(renderer, iter->first.x, iter->first.y, OPEN);

	//Closed nodes
	for (auto iter = closedList.begin(); iter != closedList.end(); iter++)
		drawCell(renderer, iter->first.x, iter->first.y, CLOSED);

	//Found path
	if (complete)
	{
		SDL_Point node = *endLoc;
		//cout << "endLoc: " << node.x << ", " << node.y << endl;
		drawCell(renderer, node.x, node.y, PATH);
		while (node.x != startLoc->x || node.y != startLoc->y)
		{
			drawCell(renderer, node.x, node.y, PATH);
			node = closedList[node].parent;
		}
	}
}
