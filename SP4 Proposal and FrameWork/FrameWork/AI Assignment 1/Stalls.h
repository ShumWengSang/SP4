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
	int maskPrice;
	int maskSold;
	Vector3 pos;
	Vector3 scale;
	int totalMaskSold;
public:
	CStalls(void);
	~CStalls(void);

	CMoney theStoreMoney;

	int getMaskNo();
	int getMaskPrice();
	int getMaskSold();
	int getTotalMaskSold();

	void setMaskNo(int mn);
	void setMaskPrice(int mp);
	void setMaskSold(int ms);
	void setTotalMaskSold(int tms);

	void buyMask(int amt);
	void moveStall();

	float Price;

	// Entity Functions
	bool glRenderObject();
	EntityType getObjectType(void);
	Vector3 getPosition(void);
	bool operator== (Entity& o);
	Vector3 GetScale();
	void Update();

};

