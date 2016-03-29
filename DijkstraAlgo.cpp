#include "DijkstraAlgo.h"

DijkstraAlgo::DijkstraAlgo(bool** newBars, SDL_Point* newSLoc, SDL_Point* newELoc) : PathAlgo(newBars, newSLoc, newELoc) {};

bool DijkstraAlgo::step()
{
	/*
	Psuedocode:
	Grab the first node, erase it from the open list
	Investigate the spots around it,
    	If node at spot nonexistant, add the new node to the open list
    	If node at spot has lower G value, ignore this node
    	If node at spot has higher G value, parent this node to the most recent node, erase the old node, and add the new one to the open list.
	*/

	//Pre-check
	if (blocked || complete)
		return false;

	//Setup initial conditions
	if (openList.count(*startLoc) == 0 && closedList.count(*startLoc) == 0)
	{
		startLNode.g = 0;
		openList[*startLoc] = startLNode;
	}

	//Make sure the algorithm isn't blocked
	if (openList.size() == 0)
	{
		blocked = true;
		return false;
	}

	//Get the lowest G-val node - sorting won't work here.
	SDL_Point currentCoord;
	DjkNode currentNode;
	float lowVal = 9999999;
	for (auto iter = openList.begin(); iter != openList.end(); iter++)
	{
		if (iter->second.g < lowVal)
		{
			lowVal = iter->second.g;
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

			DjkNode newNode = {currentNode.g + 1, currentCoord}; //Parents the new node to the current node coords
			if (iX && iY)
				newNode.g += 0.41; //Diagonal cost is greater

			if (openList.count(newCoord) == 0 && closedList.count(newCoord) == 0)
				openList[newCoord] = newNode;
			if (openList.count(newCoord) > 0)
			{
				if (openList[newCoord].g > newNode.g)
					openList[newCoord] = newNode;
				else
					continue;
			}
			if (closedList.count(newCoord) > 0)
			{
				if (closedList[newCoord].g > newNode.g)
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

void DijkstraAlgo::reset()
{
	openList.clear();
	closedList.clear();
	complete = false;
	blocked = false;
}

void DijkstraAlgo::drawAll(SDL_Renderer* renderer)
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
