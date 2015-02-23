#pragma once
#include "Vector3.h"
#include "freeglut.h"

class CGrid
{
private:
	Vector3 color;
	Vector3 pos;
	
public:
	Vector3 getColor;
	Vector3 getPos;
	CGrid():color(0,0,0),pos(0,0,0){};
	~CGrid(void){};

	void drawGrid(int, int, int, int, int, bool);

};

