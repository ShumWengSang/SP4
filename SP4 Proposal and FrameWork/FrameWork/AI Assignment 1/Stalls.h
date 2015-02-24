#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
using namespace std;

class CStalls : public Entity
{
	int gasMaskAmount;
	int maskPrice;
	int maskSold;
public:
	CStalls(void);
	~CStalls(void);

	CMoney theStoreMoney;

	int getMaskNo();
	int getMaskPrice();
	int getMaskSold();

	void setMaskNo(int mn);
	void setMaskPrice(int mp);
	void setMaskSold(int ms);

	void buyMask(int amt);
	void moveStall();

	float Price;

	// Entity Functions
	/*bool glRenderObject();
	EntityType getObjectType(void);
	Vector3 getPosition(void);
	bool operator== (Entity& o);
	Vector3 GetScale();
	void Update();*/

};

