#include "ObjectModel.h"


CObjectModel::CObjectModel(void)
	: thePosition(0,0,0),
	theObj(0)
{
}


CObjectModel::~CObjectModel(void)
{
}

void CObjectModel::Init(void)
{
}

void CObjectModel::Render()
{

	glPushMatrix();

	glTranslatef( thePosition.x, thePosition.y, thePosition.z);
	glRotatef(180,0,1,0);
		//glColor3f(1.0f, 0.0f, 0.0f);
		DrawOBJ ( theObj );

	glPopMatrix();
}

void CObjectModel::SetPosition(Vector3 theNewPosition)
{
	thePosition.x = theNewPosition.x;
	thePosition.y = theNewPosition.y;
	thePosition.z = theNewPosition.z;
}


Vector3 CObjectModel::GetPosition()
{
	return thePosition;
}