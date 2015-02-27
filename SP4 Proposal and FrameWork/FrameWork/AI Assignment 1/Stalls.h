#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
#include "freeglut.h"

#include "ObjectModel.h"
using namespace std;

class CStalls : public Entity
{
private:
	int gasMaskAmount;
	int maskSold;
	Vector3 pos;
	Vector3 scale;
	Vector3 colour;

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

	void setMaskNo(int mn);
	void setMaskSold(int ms);
	void setTotalMaskSold(int tms);
	void setMaskPrice(int mp);

	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setColour(Vector3 colour);

	void buyMask(int amt);
	void moveStall();

	CMoney theMoney;

	float Price;

	bool Selected;

	// Entity Functions
	bool glRenderObject();
	EntityType getObjectType(void);
	Vector3 getPosition(void);
	bool operator== (Entity& o);
	Vector3 GetScale();
	void Update();

};

