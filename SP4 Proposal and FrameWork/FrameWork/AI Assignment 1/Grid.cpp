#include "Grid.h"
#include "freeglut.h"

Grid::Grid(void)
{
	tileHeight = TILE_SIZE_X;
	tileWidth = TILE_SIZE_Y;
	InitGrid();
}

Grid::~Grid(void)
{
}

void Grid::InitGrid (void) {

	int a = 0;
	int s = 0;
	int maxa = TILE_NO_X;
	int maxs = TILE_NO_Y;

	for (float i = 1.00f; i >= 0.00f; i -= 0.05f)
	{
		for (float j = 1.00f; j >= 0.00f; j -= 0.05f)
		{
			for (float k = 1.00f; k >= 0.00f; k -= 0.05f)
			{
				if(s == maxs) {
					s = 0;
					a++;
				}
				if(a == maxa)
					break;

				temp[a][s].setColor(i,j,k);

				s++;
			}
		}
	}

}

void Grid::renderGrid(bool isPicking)
{
	glPushMatrix();
	for (int k = 0; k < TILE_NO_X; ++k)
	{
		for(int l = 0; l < TILE_NO_Y; ++l)
		{
			//drawTile(k*tileHeight, 0, l*tileWidth, isPicking);
			temp[k][l].drawTile(k*tileHeight, 0, l*tileWidth, tileWidth, tileHeight, isPicking);
		}
	}
	glPopMatrix();

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
	this->z = z;
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
