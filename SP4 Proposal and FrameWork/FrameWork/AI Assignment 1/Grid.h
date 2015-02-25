#pragma once
#include <iostream>
#include "Tile.h"
#include "Timer.h"


#define TILE_NO_X 5
#define TILE_NO_Y 5

class Tiles;

class Grid : public Entity
{
private:
	int x, y,z;

	int tileHeight, tileWidth;

public:
	Grid(void);
	~Grid(void);

	Tiles * GetTile(Vector3 pos)
	{
		Tiles * theTile;
		//Check if pos is inside any of the tiles. if it is, set the tile to that tile.
		for (int i = 0; i < TILE_NO_X; i++)
		{
			for (int j = 0; j < TILE_NO_Y; j++)
			{
				if (temp[i][j].isWithin(pos) == true)
				{
					theTile = &temp[i][j];
					return theTile;;
				}
			}
		}


	}
	int TimerKeyHazeDiffusal;

	void InitGrid(void);
	void renderGrid(bool isPicking);

	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getX();
	int getY();
	int getZ();

	Tiles temp[TILE_NO_X][TILE_NO_Y];

	bool Click;
	void CalculateDiffuse();
	void SetPointers();

	//entity functions
	EntityType getObjectType(void);
	bool glRenderObject();
	void Update();
};

