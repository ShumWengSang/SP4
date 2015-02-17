#pragma once
#include "freeglut.h"

class CButtons
{
	int x, y;
	int w, h;
	int button;
public:
	CButtons(void);
	CButtons(int x , int y, int w, int h, int button);
	~CButtons(void);

	int getButton();
	int getButtonX();
	int getButtonY();
	int getWidth();
	int getHeight();

	void setButtonX(int x);
	void setButtonY(int y);
	void setWidth(int w);
	void setHeight(int h);

	void setButtonTexture(int bt);
};

