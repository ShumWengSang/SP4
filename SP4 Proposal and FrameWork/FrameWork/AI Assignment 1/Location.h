#pragma once
#include <iostream>
class Location
{
private:
	int x, y,z;

	int tileHeight, tileWidth;

public:
	Location(void);
	~Location(void);

	void renderMap(void);
	void drawGrid(int, int, int);
	
	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getX();
	int getY();
	int getZ();
};

