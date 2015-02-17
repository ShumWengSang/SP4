#include "Buttons.h"

CButtons::CButtons(void)
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	button = 0;
}

CButtons::CButtons(int button)
{
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
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	return w;
}
int CButtons::getHeight()
{
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &h);
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

void CButtons::setButtonTexture(int bt)
{
	button = bt;
}