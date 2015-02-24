#include "Tile.h"

void Tiles::drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking)
{
	CalcHazeAlpha();
	if(!isPicking) {
		glBegin(GL_LINES);
		glPushMatrix();
		//glColor3f(color.x,color.y,color.z);
		glColor3f(0,0,0);
	
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

	glPushMatrix();
		if(isPicking)
			glColor4f(color.x, color.y, color.z, HazeAlpha);
		else if (TileHazeValue > 50)
		{
			glColor4f(1, 1, 0, HazeAlpha);
		}
		else
			glColor4f(1, 1, 1, HazeAlpha);
		glBegin(GL_QUADS);
			glVertex3f(x,0,z+tileWidth);
			glVertex3f(x+tileHeight,0,z+tileWidth);
			glVertex3f(x+tileHeight,0,z);
			glVertex3f(x,0,z);
		glEnd();
	glPopMatrix();
}

bool Tiles::isWithin(Vector3 pos)
{
	if(pos.x > this->pos.x && pos.x < this->pos.x + TILE_SIZE_X && pos.z > this->pos.z && pos.z < this->pos.z + TILE_SIZE_Y)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Tiles::glRenderObject()
{
	return true;
}

void Tiles::Pressure(Tiles &currentCell, Tiles &neighbourCell)
{
	//if there is more pressure in cell than in neighbour
	if (currentCell.TileHazeValue > neighbourCell.TileHazeValue)
	{
		//get the pressure ratio between the cells
		float Pressure_ratio = currentCell.TileHazeValue / neighbourCell.TileHazeValue;

	}
	//Pressure difference
	float PressureFlow = currentCell.TileHazeValue - neighbourCell.TileHazeValue;

	//pressure diffuse to neightbour
	neighbourCell.TileHazeValue += PressureFlow * 0.25;
	currentCell.TileHazeValue -= PressureFlow * 0.25;

	//detect and remove oscillations
	if ((PressureFlow > 0) && (neighbourCell.TileHazeValue < currentCell.TileHazeValue))
	{
		//calculate the average pressure of currentcell and neighbourcell and distribute evenly
		float TotalPressure = currentCell.TileHazeValue + neighbourCell.TileHazeValue;
		float AveragePressure = TotalPressure / 2;
		currentCell.TileHazeValue = AveragePressure;
		neighbourCell.TileHazeValue = AveragePressure;
	}
}

void Tiles::Update()
{
	if (this->TileHazeValue <= 50)
	{
		return;
	}
	if (top != NULL)
		Pressure(*this, *top);
	if (bottom != NULL)
		Pressure(*this, *bottom);
	if (left != NULL)
		Pressure(*this, *left);
	if (right != NULL)
		Pressure(*this, *right);

	
	//this->TileHazeValue -= 1;
}

void Tiles::CalcHazeAlpha()
{
	float temp = TileHazeValue * HAZE_MAX;
	HazeAlpha = HAZE_MIN / temp;
}

