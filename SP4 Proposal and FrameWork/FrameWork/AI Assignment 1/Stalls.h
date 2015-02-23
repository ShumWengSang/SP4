#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
using namespace std;

class CStalls : Entity
{
	int gasMaskAmount;
	int maskPrice;
public:
	CStalls(void);
	~CStalls(void);

	CMoney theStoreMoney;

	int getMaskNo();
	int getMaskPrice();

	void setMaskNo(int mn);
	void setMaskPrice(int mp);

	void buyMask(int amt);
	void moveStall();
};

