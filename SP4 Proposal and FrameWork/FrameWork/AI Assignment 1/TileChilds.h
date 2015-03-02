#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
#include "Tile.h"



class Tiles;
class ColorChanger
{

public:

	void HSLtoRGB(float &Rh, float &Gs, float &Bl);
	~ColorChanger();
	static ColorChanger * GetInstance();
	private:
		ColorChanger(){};
		static ColorChanger * instance;
};

//Rh = 23, Gs = 5, Bl = 100 - blue;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
//HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB

class CTileChilds : public Entity
{
private:
	Vector3 colour;
	Vector3 pos;
	float ypos;
	
public:
	int CurrentLevel;
	static int MAX_LEVEL;
	float AlphaValue;
	int HazeTileValue;
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


	void drawTile(float x, float y, float z, float  tileWidth, float tileHeight);
	void Pressure(CTileChilds &currentCell, CTileChilds &neighbourCell, const float &Ratio1);
	void Pressure2(CTileChilds &currentCell, CTileChilds &neighbourCell, const float &Ratio1, const float &Ratio2);
	void DiffusePressureOnEdge();
	void init();
	void LinkTiles();
	void Seeded(int);
	void ContructorInit();
	void GetHaze(int &Haze, int&Number);
	void MoveHaze(CTileChilds * other);
	bool isWithin(Vector3 Pos);
	ColorChanger * theColor;


	//Entity functions
	bool glRenderObject();
	void Update();


};

