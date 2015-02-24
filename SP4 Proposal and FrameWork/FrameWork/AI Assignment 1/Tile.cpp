#include "Tile.h"

void Tiles::drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking)
{
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

	glPushMatrix();
		if(isPicking)
			glColor3f(color.x,color.y,color.z);
		else
			glColor3f(1,1,1);
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