#include "Tile.h"

void Tiles::drawTile(int x, int y, int z, int tileWidth, int tileHeight, bool isPicking)
{
	glBegin(GL_LINES);
	glColor3f(color.x,color.y,color.z);
	glPushMatrix();
	
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
		glBegin(GL_QUADS);
			glVertex3f(x,0,z+tileWidth);
			glVertex3f(x+tileHeight,0,z+tileWidth);
			glVertex3f(x+tileHeight,0,z);
			glVertex3f(x,0,z);
		glEnd();
	glPopMatrix();
}
