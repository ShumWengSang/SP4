#include "TileChilds.h"


CTileChilds::CTileChilds(void)
{
	top = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	HazeTileValue = 0;
}

CTileChilds::CTileChilds(Tiles * ParentTile)
{
	top = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	this->ParentTile = ParentTile;
	HazeTileValue = 0;
}

void CTileChilds::drawTile(float x, float y, float z, float tileWidth, float tileHeight)
{



	glBegin(GL_QUADS);
		glColor4f(colour.x, colour.y, colour.z, 1);
		glVertex3f(x, ypos, z+tileWidth);
		glVertex3f(x+tileHeight, ypos, z+tileWidth);
		glVertex3f(x+tileHeight, ypos, z);
		glVertex3f(x, ypos, z);
	glEnd();
}

bool CTileChilds::glRenderObject()
{
	return true;
}

void CTileChilds::Update()
{
	if (this->HazeTileValue <= 50)
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

	if (HazeTileValue > 50)
	{
		colour.Set(1, 1, 0);
	}
}


void CTileChilds::init()
{
	colour = Vector3(1,1, 1);
	ypos = 10;
}

void CTileChilds::Pressure(CTileChilds &currentCell, CTileChilds &neighbourCell)
{
	//if there is more pressure in cell than in neighbour
	if (currentCell.HazeTileValue > neighbourCell.HazeTileValue)
	{
		//get the pressure ratio between the cells
		float Pressure_ratio = currentCell.HazeTileValue / neighbourCell.HazeTileValue;

	}
	//Pressure difference
	float PressureFlow = currentCell.HazeTileValue - neighbourCell.HazeTileValue;

	//pressure diffuse to neightbour
	neighbourCell.HazeTileValue += PressureFlow * 0.25;
	currentCell.HazeTileValue -= PressureFlow * 0.25;

	//detect and remove oscillations
	if ((PressureFlow > 0) && (neighbourCell.HazeTileValue < currentCell.HazeTileValue))
	{
		//calculate the average pressure of currentcell and neighbourcell and distribute evenly
		float TotalPressure = currentCell.HazeTileValue + neighbourCell.HazeTileValue;
		float AveragePressure = TotalPressure / 2;
		currentCell.HazeTileValue = AveragePressure;
		neighbourCell.HazeTileValue = AveragePressure;
	}
}

