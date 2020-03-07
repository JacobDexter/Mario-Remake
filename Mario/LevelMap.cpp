#include "LevelMap.h"
#include <iostream>

using namespace std;

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	mMap = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	//return the collision of each tile
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue)
{
	mMap[column][row] = newValue;

	return;
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete [] mMap[i];
	}
	delete[] mMap;
}