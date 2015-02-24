#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
using namespace std;

class CStalls : public Entity
{
	int gasMaskAmount;
	int maskSold;
	int totalMaskSold;
public:
	CStalls(void);
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
	//bool glRenderObject();
	//EntityType getObjectType(void);
	//Vector3 getPosition(void);
	//bool operator== (Entity& o);
	//Vector3 GetScale();
	//void Update();
};

