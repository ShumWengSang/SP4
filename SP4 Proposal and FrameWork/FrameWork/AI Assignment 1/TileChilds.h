#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
#include "Tile.h"



class Tiles;

class CTileChilds : public Entity
{
private:
	Vector3 colour;
	Vector3 pos;
	float ypos;
	
public:
	int CurrentLevel;
	int MAX_LEVEL;
	float AlphaValue;
	float HazeTileValue;
	int ChildNum;
	Tiles * ParentTile;
	CTileChilds * ParentChildTile; 

	CTileChilds * top;
	CTileChilds * left;
	CTileChilds * right;
	CTileChilds * bottom;

	CTileChilds * childs[4];

	Vector3 getColor(void){return colour;}
	Vector3 getPos(void){return pos;}
	void setColor(float x, float y, float z){colour.Set(x,y,z);}
	void setPos(float x, float y, float z){pos.Set(x,y,z);}

	CTileChilds(void);	
	CTileChilds(Tiles * ParentTile, int numb, int = 0);
	CTileChilds(CTileChilds * ParentTile, int numb, int CurrentLevel);
	~CTileChilds(void){};


	void drawTile(float x, float y, float z, float tileWidth, float tileHeight);
	void Pressure(CTileChilds &currentCell, CTileChilds &neighbourCell);
	void init();
	void LinkTiles();
	void Seeded(int);
	void ContructorInit();
	void GetHaze(int &Haze, int&Number);

	//Entity functions
	bool glRenderObject();
	void Update();


};

