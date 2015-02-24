#pragma once
#include <iostream>

using namespace std;

class CMoney
{
	int price;
	int currentMoney;

public:
	CMoney(void);
	~CMoney(void);

	int getPrice();
	int getCurrentMoney();
	void setPrice(int p);
	void setCurrentMoney(int cm);
	void setMoneyIncrease(int mi);
};

