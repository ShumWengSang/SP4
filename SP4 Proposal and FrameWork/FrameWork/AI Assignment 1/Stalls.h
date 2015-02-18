#pragma once
#include <iostream>
#include "Money.h"

using namespace std;

class CStalls
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

