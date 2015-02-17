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