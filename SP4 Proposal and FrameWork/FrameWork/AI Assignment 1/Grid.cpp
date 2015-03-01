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
	TimerKeyHazeDiffusal = theTimer->insertNewTime(100);

	for(int a = 0; a < TILE_NO_X; ++a)
	{
		for(int b = 0; b < TILE_NO_Y; ++b)
		{
			temp [a][b].setPos( (static_cast<float>(a*tileHeight)), 0, (static_cast<float>(b*tileWidth)) );
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

	for (int j = 0; j < TILE_NO_X; j ++)
	{
		for (int k = 0; k < TILE_NO_Y; k ++)
		{
			temp[j][k].init();
		}
	}

	for (int j = 0; j < TILE_NO_X; j++)
	{
		for (int k = 0; k < TILE_NO_Y; k++)
		{
			temp[j][k].LinkChilds();
		}
	}
}

void Grid::renderGrid(bool isPicking)
{
	//glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int k = 0; k < TILE_NO_X; ++k)
	{
		for(int l = 0; l < TILE_NO_Y; ++l)
		{
			//drawTile(k*tileHeight, 0, l*tileWidth, isPicking);
			//temp[k][l].drawTile(k*tileHeight, 0, l*tileWidth, tileWidth, tileHeight, isPicking);
			temp[k][l].drawTile( (static_cast<int>(temp[k][l].getPos().x)), (static_cast<int>(temp[k][l].getPos().y)), (static_cast<int>(temp[k][l].getPos().z)), tileWidth, tileHeight, isPicking);
		}
	}

	for (int k = 0; k < TILE_NO_X; ++k)
	{
		for (int l = 0; l < TILE_NO_Y; ++l)
		{
			//drawTile(k*tileHeight, 0, l*tileWidth, isPicking);
			//temp[k][l].drawTile(k*tileHeight, 0, l*tileWidth, tileWidth, tileHeight, isPicking);
			temp[k][l].drawTileChilds((static_cast<int>(temp[k][l].getPos().x)), (static_cast<int>(temp[k][l].getPos().y)), (static_cast<int>(temp[k][l].getPos().z)), tileWidth, tileHeight, isPicking);
		}
	}
	glDisable(GL_BLEND);
	//glPopMatrix();

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
			//temp[0][i].top = &temp[0][i - 1];
			temp[0][i].bottom = &temp[0][i - 1];
		}
		if (i != TILE_NO_Y - 1)
		{
			//temp[0][i].bottom = &temp[0][i + 1];
			temp[0][i].top = &temp[0][i + 1];
		}
		temp[0][i].right = &temp[1][i];
	}

	//TOP
	for (int i = 0; i < TILE_NO_X; i++)
	{
		if (i != 0)
		{
			temp[i][0].left = &temp[i - 1][0];
		}
		if (i != TILE_NO_X - 1)
		{
			temp[i][0].right = &temp[1 + i][0];
		}
		//temp[i][0].bottom = &temp[i][1];
		temp[i][0].top = &temp[i][1];
	}

	//RIGHT
	for (int i = 0; i < TILE_NO_Y; i++)
	{
		if (i != 0)
		{
			temp[TILE_NO_X - 1][i].bottom = &temp[TILE_NO_X - 1][i - 1];
			//temp[TILE_NO_X - 1][i].bottom = &temp[TILE_NO_X - 1][i + 1];
		}
		if (i != TILE_NO_Y - 1)
		{
			temp[TILE_NO_X - 1][i].top = &temp[TILE_NO_X - 1][i + 1];
			//temp[TILE_NO_X - 1][i].top = &temp[TILE_NO_X - 1][i - 1];
		}

		temp[TILE_NO_X - 1][i].left = &temp[TILE_NO_X - 2][i];
	}

	//BOTTOM
	for (int i = 0; i < TILE_NO_X; i++)
	{
		if (i != 0)
		{
			temp[i][TILE_NO_Y - 1].left = &temp[i - 1][TILE_NO_Y - 1];
		}
		if (i != TILE_NO_X - 1)
		{
			temp[i][TILE_NO_Y - 1].right = &temp[1 + i][TILE_NO_Y - 1];
		}
		//temp[i][TILE_NO_Y - 1].top = &temp[i][TILE_NO_Y - 2];
		temp[i][TILE_NO_Y - 1].bottom = &temp[i][TILE_NO_Y - 2];
	}

	for (int i = 1; i < TILE_NO_X - 1; i++)
	{
		for (int j = 1; j < TILE_NO_Y - 1; j++)
		{
			//temp[i][j].top = &temp[i][j - 1];


			temp[i][j].left = &temp[i - 1][j];

			temp[i][j].right = &temp[i + 1][j];

			//temp[i][j].bottom = &temp[i][j + 1];



			temp[i][j].top = &temp[i][j + 1];
			temp[i][j].bottom = &temp[i][j - 1];
		}
	}
}
