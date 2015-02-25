#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
#include "Stalls.h"
//#include "Grid.h"

#define TILE_SIZE_X 1
#define TILE_SIZE_Y 1
#define HAZE_MIN 50
#define HAZE_MAX 400
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
	float HazeAlpha;
	Tiles():color(0,0,0),pos(0,0,0)
	{
		theType = TILE; 
		TileHazeValue = 0;
		top = NULL;
		left = NULL;
		right = NULL;
		bottom = NULL;
		ShopOnTop = NULL;
		HazeAlpha = 1;
	}
	~Tiles(void){};
	static void Pressure(Tiles &currentCell,Tiles &neighborCell);
	bool isWithin(Vector3);
	void CalcHazeAlpha();
	void drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking);

	float TileHazeValue;

	//Pointer to neighbour tiles
	Tiles * top;
	Tiles * left;
	Tiles * right;
	Tiles * bottom;

	//Check if contains a Stall
	CStalls * ShopOnTop;

	//Entity functions
	bool glRenderObject();
	void Update();

};

