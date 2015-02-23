#include "Location.h"
#include "freeglut.h"

Location::Location(void)
{
	tileHeight = 10;
	tileWidth = 10;
}


Location::~Location(void)
{
}


void Location::renderMap(bool isPicking)
{
	for (int k = 0; k < 50; ++k)
	{
		for(int l = 0; l < 50; ++l)
		{
			drawGrid(k*tileHeight, 0, l*tileWidth, isPicking);
		}
	}

}
	

void Location::drawGrid(int x, int y, int z, bool isPicking)
{
	glBegin(GL_LINES);
	glColor3f(0,1,0);
	glPushMatrix();
	
	//Top left to top right
	glVertex3i(x,0,z+tileWidth);
	glVertex3i(x+tileHeight,0,z+tileWidth);
	
	//Top Right to bottom right
	glVertex3i(x+tileHeight,0,z+tileWidth);
	glVertex3i(x+tileHeight,0,z);

	//Bottom right to bottom left
	glVertex3i(x+tileHeight,0,z);
	glVertex3i(x, 0, z);

	//Bottom right to top Left
	glVertex3i(x, 0, z);
	glVertex3i(x,0,z+tileWidth);
	glPopMatrix();
	glEnd();
}


void Location::setX(int x)
{
	this->x = x;
}


void Location::setY(int y)
{
	this->y = y;
}


void Location::setZ(int z)
{

}


int Location::getX()
{
	return x;
}


int Location::getY()
{
	return y;
}

int Location::getZ()
{
	return z;
}