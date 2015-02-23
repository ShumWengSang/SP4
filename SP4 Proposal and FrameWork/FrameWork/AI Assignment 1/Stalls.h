#pragma once
#include <iostream>
#include "Money.h"
#include "Entity.h"
using namespace std;

class CStalls : Entity
{
	int gasMaskAmount;
public:
	CStalls(void);
	~CStalls(void);

	CMoney theStoreMoney;

	int getMaskNo();
	void setMaskNo(int mn);

	void buyMask(int amt);
	void moveStall();
};

