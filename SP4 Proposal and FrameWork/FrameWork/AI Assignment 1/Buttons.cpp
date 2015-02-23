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

void CButtons::drawButton()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, button);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x, y, 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  h);
			glTexCoord2f(1, 0);	glVertex2f(w, h);
			glTexCoord2f(1, 1);	glVertex2f(w, 0);
			glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
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