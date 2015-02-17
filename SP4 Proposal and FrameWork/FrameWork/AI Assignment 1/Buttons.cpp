#include "Buttons.h"

CButtons::CButtons(void)
{
}

CButtons::CButtons(int x , int y, int w, int h, int button)
{
	this-> x = x;
	this-> y = y;
	this-> w = w;
	this-> h = h;
	this->button = button;
}

CButtons::~CButtons(void)
{}

int CButtons::getButton()
{
	return button;
}

int CButtons::getButtonX()
{
	return x;
}

int CButtons::getButtonY()
{
	return y;
}

int CButtons::getWidth()
{
	return w;
}
int CButtons::getHeight()
{
	return h;
}

void CButtons::setButtonX(int x)
{
	x = x;
}
void CButtons::setButtonY(int y)
{
	y = y;
}

void CButtons::setWidth(int w)
{
	w = w;
}
void CButtons::setHeight(int h)
{
	h = h;
}


void CButtons::setButtonTexture(int bt)
{
	button = bt;
}

bool CButtons::isInside(int mx, int my)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	if( (mx >= ( x * (double)width/ SCREEN_WIDTH) ) && ( mx <= ((x + w)*(double)width/SCREEN_WIDTH) ) 
		&& ( my >= (y*(double)height/SCREEN_HEIGHT) ) && ( my <= ((y + h)*(double)height/SCREEN_HEIGHT)) )
		return true;
	return false;
}