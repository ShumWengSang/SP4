#include "TileChilds.h"

void CTileChilds::ContructorInit()
{
	top = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	HazeTileValue = 0;
	ChildNum = 0;
	CurrentLevel = 0;
	MAX_LEVEL = 5;
	ypos = 1;
	this->ParentChildTile = NULL;
	this->ParentTile = NULL;
}

CTileChilds::CTileChilds(void)
{
	ContructorInit();
}

CTileChilds::CTileChilds(Tiles * ParentTile, int numb, int CurrentLevel)
{
	ContructorInit();
	this->ParentTile = ParentTile;
	ChildNum = numb;
	this->CurrentLevel = CurrentLevel;


	if (this->CurrentLevel != MAX_LEVEL)
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i] = new CTileChilds(this, i, this->CurrentLevel + 1);
		}
	}
}

CTileChilds::CTileChilds(CTileChilds * ParentTile, int numb, int CurrentLevel = 0)
{
	ContructorInit();
	ParentChildTile = ParentTile;
	ChildNum = numb;
	this->CurrentLevel = CurrentLevel;

	if (this->CurrentLevel != MAX_LEVEL)
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i] = new CTileChilds(this, i, this->CurrentLevel + 1);
		}
	}
}


void CTileChilds::drawTile(float x, float y, float z, float tileWidth, float tileHeight)
{

	if (this->CurrentLevel != MAX_LEVEL)
	{

		//glBegin(GL_LINES);
		//glPushMatrix();
		////glColor3f(color.x,color.y,color.z);
		//glColor3f(1, 1, 1);

		////Top left to top right
		//glVertex3i(x, ypos, z + tileWidth);
		//glVertex3i(x + tileHeight, ypos, z + tileWidth);

		////Top Right to bottom right
		//glVertex3i(x + tileHeight, ypos, z + tileWidth);
		//glVertex3i(x + tileHeight, ypos, z);

		////Bottom right to bottom left
		//glVertex3i(x + tileHeight, ypos, z);
		//glVertex3i(x, ypos, z);

		////Bottom right to top Left
		//glVertex3i(x, ypos, z);
		//glVertex3i(x, ypos, z + tileWidth);
		//glPopMatrix();
		//glEnd();

		glPushMatrix();

		childs[0]->drawTile(x, 0, z, tileWidth / 2, tileHeight / 2);
		childs[1]->drawTile(x + tileHeight / 2, 0, z, tileWidth / 2, tileHeight / 2);
		childs[2]->drawTile(x, 0, z + tileWidth / 2, tileWidth / 2, tileHeight / 2);
		childs[3]->drawTile(x + tileHeight / 2, 0, z + tileWidth / 2, tileWidth / 2, tileHeight / 2);
	}
	else
	{
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
		glBegin(GL_QUADS);
		glColor4f(colour.x, colour.y, colour.z, 0);
		glVertex3f(x, ypos, z + tileWidth);
		glVertex3f(x + tileHeight, ypos, z + tileWidth);
		glVertex3f(x + tileHeight, ypos, z);
		glVertex3f(x, ypos, z);
		glEnd();
		//glDisable(GL_BLEND);
	}


}

bool CTileChilds::glRenderObject()
{
	return true;
}

void CTileChilds::Update()
{
	if (this->CurrentLevel != MAX_LEVEL)
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i]->Update();
		}
	}
	else if (HazeTileValue > 50)
	{

		if (top != NULL)
		{
			Pressure(*this, *top);
		}
		if (bottom != NULL)
			Pressure(*this, *bottom);
		if (left != NULL)
			Pressure(*this, *left);
		if (right != NULL)
			Pressure(*this, *right);

		if (top != NULL)
		{
			Pressure(*this, *top);
		}
	}


	if (HazeTileValue > 1.f)
	{
		colour.Set(1, 1, 0);
	}
	if (HazeTileValue > 50.f)
	{
		colour.Set(0, 1, 0);
	}
	if (HazeTileValue > 100.f)
	{
		colour.Set(255.f / 255.f, 105.f / 255.f, 180.f / 255.f);
	}
	if (HazeTileValue > 200.f)
	{
		colour.Set(1, 0, 0);
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
	neighbourCell.HazeTileValue += PressureFlow * 0.25 * 2;
	currentCell.HazeTileValue -= PressureFlow * 0.35;

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


void CTileChilds::LinkTiles()
{
	//int tempNum = ChildNum;
	//if (ChildNum <= 1)
		//ChildNum += 4;
	if (ParentTile != NULL)
	{
		if (ParentTile->top != NULL)
		{
			if (ChildNum != 0 && ChildNum != 1)
				top = ParentTile->top->childs[ChildNum - 2];
			else
				top = ParentTile->childs[ChildNum + 2];
		}
		else
		{
			if (ChildNum != 2 && ChildNum != 3)
				top = ParentTile->childs[ChildNum + 2];
		}
	
		if (ParentTile->bottom != NULL)
		{
			if (ChildNum != 2 && ChildNum != 3)
				bottom = ParentTile->bottom->childs[ChildNum + 2];
			else
				bottom = ParentTile->childs[ChildNum - 2];
		}
		else
		{
			if (ChildNum != 0 && ChildNum != 1)
				bottom = ParentTile->childs[ChildNum - 2];
		}
	
		if (ParentTile->left != NULL)
		{
			if (ChildNum != 1 && ChildNum != 3)
				left = ParentTile->left->childs[ChildNum + 1];
			else
				left = ParentTile->childs[ChildNum - 1];
		}
		else
		{
			if (ChildNum != 0 && ChildNum != 2)
				left = ParentTile->childs[ChildNum - 1];
		}
	
		if (ParentTile->right != NULL)
		{
			if (ChildNum != 0 && ChildNum != 2)
				right = ParentTile->right->childs[ChildNum - 1];
			else
				right = ParentTile->childs[ChildNum + 1];
		}
		else
		{
			if (ChildNum != 1 && ChildNum != 3)
				right = ParentTile->childs[ChildNum + 1];
		}
	}
	else if (ParentChildTile != NULL)
	{
		if (ParentChildTile->top != NULL)
		{
			if (ChildNum != 0 && ChildNum != 1)
				top = ParentChildTile->top->childs[ChildNum - 2];
			else
				top = ParentChildTile->childs[ChildNum + 2];
		}
		else
		{
			if (ChildNum != 2 && ChildNum != 3)
				top = ParentChildTile->childs[ChildNum + 2];
		}
	
		if (ParentChildTile->bottom != NULL)
		{
			if (ChildNum != 2 && ChildNum != 3)
				bottom = ParentChildTile->bottom->childs[ChildNum + 2];
			else
				bottom = ParentChildTile->childs[ChildNum - 2];
		}
		else
		{
			if (ChildNum != 0 && ChildNum != 1)
				bottom = ParentChildTile->childs[ChildNum - 2];
		}
	
		if (ParentChildTile->left != NULL)
		{
			if (ChildNum != 1 && ChildNum != 3)
				left = ParentChildTile->left->childs[ChildNum + 1];
			else
				left = ParentChildTile->childs[ChildNum - 1];
		}
		else
		{
			if (ChildNum != 0 && ChildNum != 2)
				left = ParentChildTile->childs[ChildNum - 1];
		}
	
		if (ParentChildTile->right != NULL)
		{
			if (ChildNum != 0 && ChildNum != 2)
				right = ParentChildTile->right->childs[ChildNum - 1];
			else
				right = ParentChildTile->childs[ChildNum + 1];
		}
		else
		{
			if (ChildNum != 1 && ChildNum != 3)
				right = ParentChildTile->childs[ChildNum + 1];
		}
	}


	if (this->CurrentLevel != MAX_LEVEL)
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i]->LinkTiles();
		}
	}
	//ChildNum = tempNum;
}

void CTileChilds::Seeded(int HazeValue)
{
	if (CurrentLevel != MAX_LEVEL)
	{
		//for (int i = 0; i < 4; i++)
		//{

		//}
		childs[0]->Seeded(HazeValue);
	}
	else
	{
		HazeTileValue = HazeValue;
	}
}

void CTileChilds::GetHaze(int & Haze, int & Number)
{
	if (CurrentLevel != MAX_LEVEL)
	{
		for (int i = 0; i < 4; i++)
		{
			childs[i]->GetHaze(Haze, Number);
		}
	}
	else
	{
		Haze += HazeTileValue;
		Number++;
	}
}