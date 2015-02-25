#include "TileChilds.h"


CTileChilds::CTileChilds(void)
{
	top = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	HazeTileValue = 0;
}

CTileChilds::CTileChilds(Tiles * ParentTile, int numb)
{
	top = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	this->ParentTile = ParentTile;
	HazeTileValue = 0;


	if(ParentTile->top != NULL)
	{
		if(numb != 0 && numb != 1)
			top = ParentTile->top->childs[numb-2];
		else
			top = ParentTile->childs[numb+2];
	}
	else
	{
		if(numb != 2 && numb != 3)
			top = ParentTile->childs[numb+2];
	}

	if(ParentTile->bottom != NULL)
	{
		if(numb != 2 && numb != 3)
			bottom = ParentTile->bottom->childs[numb+2];
		else
			bottom = ParentTile->childs[numb-2];
	}
	else
	{
		if(numb != 0 && numb != 1)
			bottom = ParentTile->childs[numb-2];
	}

	if(ParentTile->left != NULL)
	{
		if(numb != 1 && numb != 3)
			left = ParentTile->left->childs[numb+1];
		else
			left = ParentTile->childs[numb-1];
	}
	else
	{
		if(numb != 0 && numb != 2)
			left = ParentTile->childs[numb-1];
	}

	if(ParentTile->right != NULL)
	{
		if(numb != 0 && numb != 2)
			right = ParentTile->right->childs[numb-1];
		else
			right = ParentTile->childs[numb+1];
	}
	else
	{
		if(numb != 1 && numb != 3)
			right = ParentTile->childs[numb+1];
	}
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
	colour = Vector3(1,0,0);
	ypos = 20;
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