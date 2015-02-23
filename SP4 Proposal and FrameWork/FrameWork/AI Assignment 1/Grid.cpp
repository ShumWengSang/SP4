#include "Grid.h"
#include "freeglut.h"

Grid::Grid(void)
{
	tileHeight = 10;
	tileWidth = 10;
	InitGrid();
}

Grid::~Grid(void)
{
}

void Grid::InitGrid (void) {

	int a = 0;
	int s = 0;
	int maxa = 50;
	int maxs = 50;

	for (float i = 1.00f; i >= 0.00f; i -= 0.05f)
	{
		for (float j = 1.00f; j >= 0.00f; j -= 0.05f)
		{
			for (float k = 1.00f; k >= 0.00f; k -= 0.05f)
			{
				// Make loop through all grid (VectorList?)
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
	for (int k = 0; k < 50; ++k)
	{
		for(int l = 0; l < 50; ++l)
		{
			//drawTile(k*tileHeight, 0, l*tileWidth, isPicking);
			temp[k][l].drawTile(k*tileHeight, 0, l*tileWidth, tileWidth, tileHeight, isPicking);
		}
	}

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
