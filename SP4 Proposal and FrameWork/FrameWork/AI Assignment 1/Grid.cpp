#include "Grid.h"
#include "freeglut.h"

Grid::Grid(void)
{
	x = y = z = 0;
	tileHeight = TILE_SIZE_X;
	tileWidth = TILE_SIZE_Y;
	InitGrid();
	Click = false;

	CTimer * theTimer = CTimer::getInstance();
	TimerKeyHazeDiffusal = theTimer->insertNewTime(200);

	for(int a = 0; a < TILE_NO_X; ++a)
	{
		for(int b = 0; b < TILE_NO_Y; ++b)
		{
			temp [a][b].setPos(a*tileHeight, 0, b*tileWidth);
		}
	}

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
	SetPointers();
}

void Grid::renderGrid(bool isPicking)
{
	glPushMatrix();
	for (int k = 0; k < TILE_NO_X; ++k)
	{
		for(int l = 0; l < TILE_NO_Y; ++l)
		{
			//drawTile(k*tileHeight, 0, l*tileWidth, isPicking);
			//temp[k][l].drawTile(k*tileHeight, 0, l*tileWidth, tileWidth, tileHeight, isPicking);
			temp[k][l].drawTile(temp[k][l].getPos().x, temp[k][l].getPos().y, temp[k][l].getPos().z, tileWidth, tileHeight, isPicking);
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

EntityType Grid::getObjectType(void) {
	return EntityType::GRID;
}

bool Grid::glRenderObject()
{
	renderGrid(Click);
	return true;
}

void Grid::Update()
{
	CalculateDiffuse();
}

void Grid::CalculateDiffuse()
{
	CTimer * theTimer = CTimer::getInstance();
	if (theTimer->executeTime(TimerKeyHazeDiffusal))
	{
		for (int i = 0; i < TILE_NO_X; i++)
		{
			for (int j = 0; j < TILE_NO_Y; j++)
			{
				temp[i][j].Update();
			}
		}
	}
}

void Grid::SetPointers()
{
	//Do all four sides. Start with top, than left, than bot, and right.
	//Than do middle.

	//LEFT
	for (int i = 0; i < TILE_NO_Y; i++)
	{
		if (i != 0)
		{
			temp[0][i].top = &temp[0][i - 1];
			temp[0][i].childs[0]->top = temp[0][i].childs[2];
			temp[0][i].childs[1]->top = temp[0][i].childs[3];
			temp[0][i].childs[2]->top = temp[0][i-1].childs[0];
			temp[0][i].childs[3]->top = temp[0][i-1].childs[1];
		}
		else if (i != TILE_NO_Y - 1)
		{
			temp[0][i].bottom = &temp[0][i + 1];
			temp[0][i].childs[0]->bottom = temp[0][i + 1].childs[2];
			temp[0][i].childs[1]->bottom = temp[0][i + 1].childs[3];
			temp[0][i].childs[2]->bottom = temp[0][i].childs[0];
			temp[0][i].childs[3]->bottom = temp[0][i].childs[1];
		}
		temp[0][i].right = &temp[1][i];

		temp[0][i].childs[0]->right = temp[0][i].childs[1];
		temp[0][i].childs[1]->right = temp[1][i].childs[0];
		temp[0][i].childs[2]->right = temp[0][i].childs[3];
		temp[0][i].childs[3]->right = temp[1][i].childs[2];
	}

	//TOP
	for (int i = 0; i < TILE_NO_X; i++)
	{
		if (i != 0)
		{
			temp[i][0].left = &temp[i - 1][0];

			temp[i][0].childs[0]->left = temp[i - 1][0].childs[1];
			temp[i][0].childs[1]->left = temp[i][0].childs[0];
			temp[i][0].childs[2]->left = temp[i - 1][0].childs[3];
			temp[i][0].childs[3]->left = temp[i][0].childs[2];

		}
		else if (i != TILE_NO_X - 1)
		{
			temp[i][0].right = &temp[1 + i][0];

			temp[i][0].childs[0]->right = temp[i][0].childs[1];
			temp[i][0].childs[1]->right = temp[1 + i][0].childs[0];
			temp[i][0].childs[2]->right = temp[i][0].childs[3];
			temp[i][0].childs[3]->right = temp[1 + i][0].childs[2];
		}
		temp[i][0].bottom = &temp[i][1];

		temp[i][0].childs[0]->bottom = temp[i][1].childs[2];
		temp[i][0].childs[1]->bottom = temp[i][1].childs[3];
		temp[i][0].childs[2]->bottom = temp[i][0].childs[0];
		temp[i][0].childs[3]->bottom = temp[i][0].childs[1];

	}

	//RIGHT
	for (int i = 0; i < TILE_NO_Y; i++)
	{
		if (i != 0)
		{
			temp[TILE_NO_X - 1][i].top = &temp[TILE_NO_X - 1][i - 1];

			temp[TILE_NO_X - 1][i].childs[0]->top = temp[TILE_NO_X - 1][i].childs[2];
			temp[TILE_NO_X - 1][i].childs[1]->top = temp[TILE_NO_X - 1][i].childs[3];
			temp[TILE_NO_X - 1][i].childs[2]->top = temp[TILE_NO_X - 1][i - 1].childs[0];
			temp[TILE_NO_X - 1][i].childs[3]->top = temp[TILE_NO_X - 1][i - 1].childs[1];
		}
		else if (i != TILE_NO_Y - 1)
		{
			temp[TILE_NO_X - 1][i].bottom = &temp[TILE_NO_X - 1][i + 1];

			temp[TILE_NO_X - 1][i].childs[0]->bottom = temp[TILE_NO_X - 1][i + 1].childs[2];
			temp[TILE_NO_X - 1][i].childs[1]->bottom = temp[TILE_NO_X - 1][i + 1].childs[3];
			temp[TILE_NO_X - 1][i].childs[2]->bottom = temp[TILE_NO_X - 1][i].childs[0];
			temp[TILE_NO_X - 1][i].childs[3]->bottom = temp[TILE_NO_X - 1][i].childs[1];
		}

		temp[TILE_NO_X - 1][i].left = &temp[TILE_NO_X - 2][i];

		temp[TILE_NO_X - 1][i].childs[0]->left = temp[TILE_NO_X - 2][i].childs[1];
		temp[TILE_NO_X - 1][i].childs[1]->left = temp[TILE_NO_X - 1][i].childs[0];
		temp[TILE_NO_X - 1][i].childs[2]->left = temp[TILE_NO_X - 2][i].childs[3];
		temp[TILE_NO_X - 1][i].childs[3]->left = temp[TILE_NO_X - 1][i].childs[2];
	}

	//BOTTOM
	for (int i = 0; i < TILE_NO_X; i++)
	{
		if (i != 0)
		{
			temp[i][TILE_NO_Y - 1].left = &temp[i - 1][TILE_NO_Y - 1];

			temp[i][TILE_NO_Y - 1].childs[0]->left = temp[i - 1][TILE_NO_Y - 1].childs[1];
			temp[i][TILE_NO_Y - 1].childs[1]->left = temp[i][TILE_NO_Y - 1].childs[0];
			temp[i][TILE_NO_Y - 1].childs[2]->left = temp[i - 1][TILE_NO_Y - 1].childs[3];
			temp[i][TILE_NO_Y - 1].childs[3]->left = temp[i][TILE_NO_Y - 1].childs[2];
		}
		else if (i != TILE_NO_X - 1)
		{
			temp[i][TILE_NO_Y - 1].right = &temp[1 + i][TILE_NO_Y - 1];

			temp[i][TILE_NO_Y - 1].childs[0]->right = temp[i][TILE_NO_Y - 1].childs[1];
			temp[i][TILE_NO_Y - 1].childs[1]->right = temp[1 + i][TILE_NO_Y - 1].childs[0];
			temp[i][TILE_NO_Y - 1].childs[2]->right = temp[i][TILE_NO_Y - 1].childs[3];
			temp[i][TILE_NO_Y - 1].childs[3]->right = temp[1 + i][TILE_NO_Y - 1].childs[2];
		}
		temp[i][TILE_NO_Y - 1].top = &temp[i][TILE_NO_Y - 2];

		temp[i][TILE_NO_Y - 1].childs[0]->top = temp[i][TILE_NO_Y - 1].childs[2];
		temp[i][TILE_NO_Y - 1].childs[1]->top = temp[i][TILE_NO_Y - 1].childs[3];
		temp[i][TILE_NO_Y - 1].childs[2]->top = temp[i][TILE_NO_Y - 2].childs[0];
		temp[i][TILE_NO_Y - 1].childs[3]->top = temp[i][TILE_NO_Y - 2].childs[1];
	}

	for (int i = 1; i < TILE_NO_X - 1; i++)
	{
		for (int j = 1; j < TILE_NO_Y - 1; j++)
		{
			temp[i][j].top = &temp[i][j - 1];

			temp[i][j].childs[0]->top = temp[i][j].childs[2];
			temp[i][j].childs[1]->top = temp[i][j].childs[3];
			temp[i][j].childs[2]->top = temp[i][j - 1].childs[0];
			temp[i][j].childs[3]->top = temp[i][j - 1].childs[1];


			temp[i][j].left = &temp[i - 1][j];

			temp[i][j].childs[0]->left = temp[i - 1][j].childs[1];
			temp[i][j].childs[1]->left = temp[i][j].childs[0];
			temp[i][j].childs[2]->left = temp[i - 1][j].childs[3];
			temp[i][j].childs[3]->left = temp[i][j].childs[2];

			temp[i][j].right = &temp[i + 1][j];

			temp[i][j].childs[0]->right = temp[i][j].childs[1];
			temp[i][j].childs[1]->right = temp[i + 1][j].childs[0];
			temp[i][j].childs[2]->right = temp[i][j].childs[3];
			temp[i][j].childs[3]->right = temp[i + 1][j].childs[2];

			temp[i][j].bottom = &temp[i][j + 1];

			temp[i][j].childs[0]->bottom = temp[i][j + 1].childs[2];
			temp[i][j].childs[1]->bottom = temp[i][j + 1].childs[3];
			temp[i][j].childs[2]->bottom = temp[i][j].childs[0];
			temp[i][j].childs[3]->bottom = temp[i][j].childs[1];
		}
	}
}
