#include "TileChilds.h"


CTileChilds::CTileChilds(void)
{
	
}

void CTileChilds::drawTile(float x, float y, float z, float tileWidth, float tileHeight)
{
	glBegin(GL_LINES);
	glPushMatrix();
	//glColor3f(color.x,color.y,color.z);
	glColor3f(1,1,1);
	
	//Top left to top right
	glVertex3i(x, ypos, z+tileWidth);
	glVertex3i(x+tileHeight, ypos, z+tileWidth);
	
	//Top Right to bottom right
	glVertex3i(x+tileHeight, ypos, z+tileWidth);
	glVertex3i(x+tileHeight, ypos, z);

	//Bottom right to bottom left
	glVertex3i(x+tileHeight, ypos, z);
	glVertex3i(x, ypos, z);

	//Bottom right to top Left
	glVertex3i(x, ypos, z);
	glVertex3i(x, ypos, z+tileWidth);
	glPopMatrix();
	glEnd();


	glBegin(GL_QUADS);
		glColor3f(colour.x, colour.y, colour.z);
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
	
}


void CTileChilds::init()
{
	colour = Vector3(0,0,0);
	ypos = 1;
}