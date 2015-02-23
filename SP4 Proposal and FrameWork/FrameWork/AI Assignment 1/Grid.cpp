#include "Grid.h"
#include "freeglut.h"

Grid::Grid(void)
{
	tileHeight = 10;
	tileWidth = 10;
}


Grid::~Grid(void)
{
}

void Grid::InitGrid (void) {

	for (float i = 0.00; i <= 1; i+= 0.05)
	{
		for (float j = 0.00; j <= 1; j+= 0.05)
		{
			for (float k = 0.00; k <= 1; k+= 0.05)
			{
				// Make loop through all grid (VectorList?)
				temp[0][0].getColor.Set(i,j,k);
			}
		}
	}

}

void Grid::renderMap(bool isPicking)
{
	for (int k = 0; k < 50; ++k)
	{
		for(int l = 0; l < 50; ++l)
		{
			drawGrid(k*tileHeight, 0, l*tileWidth, isPicking);
		}
	}

}
	

void Grid::drawGrid(int x, int y, int z, bool isPicking)
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


void Grid::setX(int x)
{
	this->x = x;
}


void Grid::setY(int y)
{
	this->y = y;
}


void Grid::setZ(int z)
{

}


int Grid::getX()
{
	return x;
}


int Grid::getY()
{
	return y;
}

int Grid::getZ()
{
	return z;
}