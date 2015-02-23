#pragma once
#include <iostream>
#include "Tile.h"

class Grid
{
private:
	int x, y,z;

	int tileHeight, tileWidth;

public:
	Grid(void);
	~Grid(void);

	void InitGrid(void);
	void renderMap(bool);
	void drawGrid(int, int, int, bool);
	
	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getX();
	int getY();
	int getZ();

	Tiles temp[1][1];

};

