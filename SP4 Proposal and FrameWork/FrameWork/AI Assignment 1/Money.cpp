#include "Money.h"

CMoney::CMoney(void)
{
	price = 0;
	currentMoney = 0;
}

CMoney::~CMoney(void)
{
}

int CMoney:: getPrice()
{
	return price;
}
int CMoney:: getCurrentMoney()
{
	return currentMoney;
}
void CMoney:: setPrice(int p)
{
	price = p;
}
void CMoney:: setCurrentPrice(int cm)
{
	currentMoney = cm;
}

void CMoney::setMoneyIncrease(int mi)
{
	currentMoney += mi;
}