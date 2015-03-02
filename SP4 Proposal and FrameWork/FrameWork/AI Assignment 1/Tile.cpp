#include "Tile.h"
int Tiles::TexID = 0;
void Tiles::drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking)
{

		if(isPicking)
		{
			glColor4f(color.x, color.y, color.z, HazeAlpha);
			tempC = Vector3(color.x, color.y, color.z);
		}
		else if(ShopOnTop != NULL)
		{
			glColor4f(1, 1, 0, HazeAlpha);
			tempC = Vector3(1, 1, 0);
		}
		else {
			glColor4f(1, 1, 1, HazeAlpha);
			tempC = Vector3(1, 1, 1);
		}
		
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		if (isPicking)
			glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TexID);
		glBegin(GL_QUADS);
	
			glTexCoord2f(0, 0);
			glVertex3f(static_cast<GLfloat>(x),0,static_cast<GLfloat>(z+tileWidth));
			glTexCoord2f(1, 0);
			glVertex3f(static_cast<GLfloat>(x+tileHeight),0,static_cast<GLfloat>(z+tileWidth));
			glTexCoord2f(1, 1);
			glVertex3f(static_cast<GLfloat>(x+tileHeight),0,static_cast<GLfloat>(z));
			glTexCoord2f(0, 1);
			glVertex3f(static_cast<GLfloat>(x),0,static_cast<GLfloat>(z));
			
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//glDisable(GL_BLEND);
}

void Tiles::drawTileChilds(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking)
{
	if (!isPicking)
	{
		int tW = tileWidth / 2;
		int tH = tileHeight / 2;
		childs[0]->drawTile(static_cast<float>(x), 0, static_cast<float>(z), static_cast<float>(tW), static_cast<float>(tH));
		childs[1]->drawTile(static_cast<float>(x + tileHeight / 2), 0, static_cast<float>(z), static_cast<float>(tW), static_cast<float>(tH));
		childs[2]->drawTile(static_cast<float>(x), 0, static_cast<float>(z + tileWidth / 2), static_cast<float>(tW), static_cast<float>(tH));
		childs[3]->drawTile(static_cast<float>(x + tileHeight / 2), 0, static_cast<float>(z + tileWidth / 2), static_cast<float>(tW), static_cast<float>(tH));
	}
}


bool Tiles::isWithin(Vector3 pos)
{
	if(pos.x >= this->pos.x && pos.x <= this->pos.x + TILE_SIZE_X && pos.z >= this->pos.z && pos.z <= this->pos.z + TILE_SIZE_Y)
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
	neighbourCell.TileHazeValue += PressureFlow/4;
	currentCell.TileHazeValue -= PressureFlow /4;

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

	for (int i = 0; i < 4; i++)
	{
		childs[i]->Update();
	}

}

Vector3 Tiles::GetScale()
{
	return scale;
}

void Tiles::CalcHazeAlpha()
{
	float temp = TileHazeValue * HAZE_MAX;
	HazeAlpha = HAZE_MIN / temp;
}


void Tiles::init()
{
	childs[0] = new CTileChilds(this, 0);
	childs[0]->init();
	childs[1] = new CTileChilds(this, 1);
	childs[1]->init();
	childs[2] = new CTileChilds(this, 2);
	childs[2]->init();
	childs[3] = new CTileChilds(this, 3);
	childs[3]->init();


}

void Tiles::LinkChilds()
{
	for (int i = 0; i < 4; i++)
	{
		childs[i]->LinkTiles();
	}
}

void Tiles::Seeded(int HazeValue)
{
	//for (int i = 0; i < 4; i++)
	//{
	//	childs[i]->Seeded(HazeValue);
	//}
	childs[1]->Seeded(HazeValue);
}

int Tiles::GetHaze()
{
	int Haze = 0;
	int NumberWentThrough = 0;
	for (int i = 0; i < 4; i++)
	{
		childs[i]->GetHaze(Haze, NumberWentThrough);
	}
	return Haze / NumberWentThrough;
}