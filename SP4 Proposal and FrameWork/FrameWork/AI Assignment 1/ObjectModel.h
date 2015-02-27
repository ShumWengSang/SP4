#pragma once

#include "freeglut.h"
#include "Vector3.h"
#include "ObjLoader\ObjLoader.h"

class CObjectModel
{
private:
	Vector3 thePosition;

public:
	ObjFile theObj;

	CObjectModel(void);
	~CObjectModel(void);

	void Init (void);
	void Render();
	void SetPosition(Vector3 theNewPosition);
	Vector3 GetPosition();
};

