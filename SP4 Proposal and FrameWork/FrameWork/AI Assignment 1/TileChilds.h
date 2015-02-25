#pragma once
#include "Vector3.h"
#include "freeglut.h"
#include "Entity.h"
#include "Tile.h"

class CTileChilds : public Entity
{
private:
	Vector3 colour;
	Vector3 pos;
	float ypos;
	
public:
	Vector3 getColor(void){return colour;}
	Vector3 getPos(void){return pos;}
	void setColor(float x, float y, float z){colour.Set(x,y,z);}
	void setPos(float x, float y, float z){pos.Set(x,y,z);}

	CTileChilds(void);	
	~CTileChilds(void){};


	void drawTile(float x, float y, float z, float tileWidth, float tileHeight);


	//Entity functions
	bool glRenderObject();
	void Update();

	void init();
};

