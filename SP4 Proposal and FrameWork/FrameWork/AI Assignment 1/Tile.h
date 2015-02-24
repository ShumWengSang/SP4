#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
//#include "Grid.h"

#define TILE_SIZE_X 8
#define TILE_SIZE_Y 8

class Tiles : public Entity
{
private:
	Vector3 color;
	Vector3 pos;
	
public:
	Vector3 getColor(void){return color;}
	Vector3 getPos(void){return pos;}
	void setColor(float x, float y, float z){color.Set(x,y,z);}
	void setPos(float x, float y, float z){pos.Set(x,y,z);}
	Tiles():color(0,0,0),pos(0,0,0)
	{
		theType = TILE; 
		TileHazeValue = 0;
	}
	~Tiles(void){};
	static void Pressure(Tiles &currentCell,Tiles &neighborCell);
	bool isWithin(Vector3);

	void drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking);

	float TileHazeValue;


	//Entity functions
	bool glRenderObject();
	void Update();
};
