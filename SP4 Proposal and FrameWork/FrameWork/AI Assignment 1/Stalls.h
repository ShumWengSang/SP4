#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
#include "freeglut.h"
using namespace std;

class CStalls : public Entity
{
private:
	int gasMaskAmount;
	int maskSold;
	Vector3 pos;
	Vector3 scale;
	int totalMaskSold;
public:
	CStalls(Vector3 pos = Vector3(0,0,0), Vector3 scale = Vector3(5,5,5));
	~CStalls(void);

	CMoney theStoreMoney;

	int getMaskNo();
	int getMaskSold();
	int getTotalMaskSold();
	int getMaskPrice();

	void setMaskNo(int mn);
	void setMaskSold(int ms);
	void setTotalMaskSold(int tms);
	void setMaskPrice(int mp);

	void buyMask(int amt);
	void moveStall();

	CMoney theMoney;

	float Price;

	// Entity Functions
	bool glRenderObject();
	EntityType getObjectType(void);
	Vector3 getPosition(void);
	bool operator== (Entity& o);
	Vector3 GetScale();
	void Update();
};

