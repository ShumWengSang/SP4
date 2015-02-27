#include "TileChilds.h"
ColorChanger * ColorChanger::instance = NULL;

void ColorChanger::HSLtoRGB(float &Rh, float &Gs, float&Bl)
{
	float min, max;
	Gs /= 100;
	Bl /= 100;
	float R, G, B;
	//IF NO SATURATION, ITS GREY.
	if (Gs == 0)
	{
		R = Bl * 255;
		G = Bl * 255;
		B = Bl * 255;
	}
	else
	{
		float temp1;
		float temp2;
		//USE RIGHT FORMULA TO FIND RGB
		if (Bl < 0.5)
		{
			temp1 = Bl * (1.0 + Gs);
		}
		else if (Bl >= 0.5)
		{
			temp1 = Bl + Gs - Bl * Gs;
		}
		temp2 = 2 * Bl - temp1;

		Rh /= 360;

		R = Rh + 0.333;
		G = Rh;
		B = Rh - 0.333;

		//SET ALL VALUES TO BETWEEN 0 AND 1
		if (R > 1)
			R - 1;
		else if (R < 1)
			R + 1;
		if (G > 1)
			G - 1;
		else if (G < 1)
			G + 1;
		if (B > 1)
			B - 1;
		else if (B < 1)
			B + 1;
		//NOW START TO FIND THE NUMBERS FOR RGB WITH THESE TESTS. 3 TESTS TO DETERMINE WHAT FORMULA TO USE
		//RED SEARCH
		if (6 * R < 1)
		{
			R = temp2 + (temp1 - temp2) * 6 * R;
		}
		else if (2 * R < 1)
		{
			R = temp1;
		}
		else if (3 * R < 2)
		{
			R = temp2 + (temp1 - temp2) * (0.6666 - R) * 6;
		}
		else
		{
			R = temp2;
		}
		//NOW DO BLUE
		if (6 * B < 1)
		{
			B = temp2 + (temp1 - temp2) * 6 * B;
		}
		else if (2 * B < 1)
		{
			B = temp1;
		}
		else if (3 * B < 2)
		{
			B = temp2 + (temp1 - temp2) * (0.6666 - B) * 6;
		}
		else
		{
			B = temp2;
		}
		//NOW DO GREEN
		if (6 * G < 1)
		{
			G = temp2 + (temp1 - temp2) * 6 * G;
		}
		else if (2 * G < 1)
		{
			G = temp1;
		}
		else if (3 * G < 2)
		{
			G = temp2 + (temp1 - temp2) * (0.6666 - G) * 6;
		}
		else
		{
			G = temp2;
		}
		//NOW RGB IS REALLY RGB IN DECIMAL FORM. 
		Rh = R; Gs = G; Bl = B;
	}
}

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
	ypos = 5;
	newHazeTileValue = 0;
	AlphaValue = 1;
	this->ParentChildTile = NULL;
	this->ParentTile = NULL;
}

ColorChanger * ColorChanger::GetInstance()
{
	if (instance == NULL)
		instance = new ColorChanger();
	return instance;
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


void CTileChilds::drawTile(float  x, float  y, float  z, float tileWidth, float tileHeight)
{

	if (this->CurrentLevel != MAX_LEVEL)
	{
		float tileW = tileHeight / 2;
		float tileH = tileHeight / 2;

		childs[0]->drawTile(x, 0, z, tileW, tileH);
		childs[1]->drawTile(x + tileHeight / 2, 0, z, tileW, tileW);
		childs[2]->drawTile(x, 0, z + tileWidth / 2, tileW, tileW);
		childs[3]->drawTile(x + tileHeight / 2, 0, z + tileWidth / 2, tileW, tileW);
	}
	else
	{
		glBegin(GL_QUADS);
		if (colour == Vector3(0.8, 0.8, 0.8))
			glColor4f(0, 0, 0, 0);
		else
			glColor4f(colour.x, colour.y, colour.z, AlphaValue);
		glVertex3f(x, ypos, z + tileWidth);
		glVertex3f(x + tileHeight, ypos, z + tileWidth);
		glVertex3f(x + tileHeight, ypos, z);
		glVertex3f(x, ypos, z);
		glEnd();
		//std::cout << " X IS: " << x << std::endl;
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
	else if (HazeTileValue > 1)
	{
		
		float Rh, Gs, Bl;
		Rh = 38, Gs = 9, Bl = HazeTileValue / 10;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
		
		if (Bl > 50)
			Bl = 50;


		Bl -= 50;
		if (Bl < 0)
			Bl = -Bl;
		if (Bl < 5)
			Bl = 5;

		theColor = ColorChanger::GetInstance();
		theColor->HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB


		colour.Set(Rh, Gs, Bl);

		Bl = 1 / Bl;
		AlphaValue = Bl / 50.f;
		if (AlphaValue > 0.8)
			AlphaValue = 0.8;
		if (AlphaValue < 0.4)
			AlphaValue = 0.4;
		//AlphaValue = 1 / AlphaValue;




		if (top != NULL)
		{
			Pressure(*this, *top, 0.9f);
			Pressure2(*this, *top, 0.3f, 0.1f);
			//Pressure(*this, *top, 0.9f);
		}
		if (bottom != NULL)
		{
			Pressure(*this, *bottom, 0.8f);
			Pressure2(*this, *bottom, 0.1f, 0.1f);
			//Pressure(*this, *bottom, 0.4f);
		}
		if (left != NULL)
		{
			Pressure(*this, *left, 0.2f);
			Pressure2(*this, *left, 0.1f, 0.1f);
			//Pressure(*this, *left, 0.1f);
		}
		if (right != NULL)
		{
			Pressure(*this, *right, 0.3f);
			Pressure2(*this, *right, 0.1f, 0.1f);
			//Pressure(*this, *right, 0.1f);
		}

		if (top != NULL)
		{
			//Pressure(*this, *top);
		}
		
		//MOVE HAZE
		//if (top!=NULL)
			//MoveHaze(top);
	}
	else
	{
		colour.Set(0.8, 0.8, 0.8);
	}


}


void CTileChilds::init()
{
	colour = Vector3(1,0,0);
	ypos = 20;
}

void CTileChilds::Pressure(CTileChilds &currentCell, CTileChilds &neighbourCell, const float &Ratio1)
{

	//Pressure difference
	float PressureFlow = currentCell.HazeTileValue - neighbourCell.HazeTileValue;

	//float CurrentTemp = currentCell.HazeTileValue;
	//pressure diffuse to neightbour
	currentCell.HazeTileValue -= PressureFlow * Ratio1;
	neighbourCell.HazeTileValue += PressureFlow * Ratio1;
	

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

void CTileChilds::Pressure2(CTileChilds &currentCell, CTileChilds &neighbourCell, const float &Ratio1, const float &Ratio2)
{
	//Pressure difference
	float PressureFlow = currentCell.HazeTileValue - neighbourCell.HazeTileValue;

	//float CurrentTemp = currentCell.HazeTileValue;
	//pressure diffuse to neightbour
	currentCell.HazeTileValue -= PressureFlow * Ratio1;
	neighbourCell.HazeTileValue += PressureFlow * Ratio2;


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

void CTileChilds::MoveHaze(CTileChilds * other)
{
	this->HazeTileValue ^= other->HazeTileValue;
	other->HazeTileValue ^= this->HazeTileValue;
	this->HazeTileValue ^= other->HazeTileValue;
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
				//left = ParentTile->childs[ChildNum - 1];
			else
				//left = ParentTile->left->childs[ChildNum + 1];
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
				//left = ParentChildTile->childs[ChildNum - 1];
			else
				//left = ParentChildTile->left->childs[ChildNum + 1];
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

void CTileChilds::DiffusePressureOnEdge()
{

}