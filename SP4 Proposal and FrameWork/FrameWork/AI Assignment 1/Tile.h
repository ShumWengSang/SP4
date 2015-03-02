#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
#include "Stalls.h"
#include "TileChilds.h"
#include "Global.h"
//#include "Grid.h"
class CTileChilds;

class Tiles : public Entity
{
private:
	Vector3 color;
	Vector3 pos;
	Vector3 scale;
	Vector3 tempC;
	
public:
	CTileChilds *childs[4];
	Vector3 getColor(void){return color;}
	Vector3 getPos(void){return pos;}
	void setColor(float x, float y, float z){color.Set(x,y,z);}
	void setPos(float x, float y, float z){pos.Set(x,y,z);}
	float HazeAlpha;
	Tiles():color(0,0,0),pos(0,0,0),scale(1,0,1)
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
	void drawTileChilds(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking);
	void LinkChilds();
	void Seeded(int);
	int GetHaze();

	float TileHazeValue;
	//Pointer to neighbour tiles
	Tiles * top;
	Tiles * left;
	Tiles * right;
	Tiles * bottom;

	void init (void);

	//Check if contains a Stall
	CStalls * ShopOnTop;

	//Entity functions
	bool glRenderObject();
	void Update();
	Vector3 GetScale();

	static int TexID;
};

