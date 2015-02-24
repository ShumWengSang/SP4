#pragma once
#include <iostream>
#include "Tile.h"

#define TILE_NO_X 99
#define TILE_NO_Y 29
#define TILE_SIZE_X 8
#define TILE_SIZE_Y 8

class Grid
{
private:
	int x, y,z;

	int tileHeight, tileWidth;

public:
	Grid(void);
	~Grid(void);

	void InitGrid(void);
	void renderGrid(bool isPicking);
	
	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getX();
	int getY();
	int getZ();

	Tiles temp[TILE_NO_X][TILE_NO_Y];

};

