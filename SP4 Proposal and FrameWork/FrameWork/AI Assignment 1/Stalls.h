#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
#include "freeglut.h"
#include "ObjectModel.h"
#include "Global.h"
using namespace std;

class CStalls : public Entity
{
private:
	int gasMaskAmount;
	int maskSold;
	Vector3 pos;
	Vector3 scale;
	Vector3 colour;
	Vector3 colour2;

	CObjectModel* theModel;

public:
	CStalls(Vector3 pos = Vector3(0,0,0), Vector3 scale = Vector3(4,4,4));
	~CStalls(void);

	int totalMaskSold;

	CMoney theStoreMoney;

	int getMaskNo();
	int getMaskSold();
	int getTotalMaskSold();
	int getMaskPrice();
	Vector3 getColour();
	Vector3 getColour2();

	void setMaskNo(int mn);
	void setMaskSold(int ms);
	void setTotalMaskSold(int tms);
	void setMaskPrice(int mp);

	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setColour(Vector3 colour);
	void setColour2(Vector3 colour2);

	void buyMask(int maskNo);

	CMoney theMoney;

	float Price;

	bool Selected;
	bool isPicking;

	// Entity Functions
	bool glRenderObject();
	EntityType getObjectType(void);
	Vector3 getPosition(void);
	bool operator== (Entity& o);
	Vector3 GetScale();
	void Update();
};

