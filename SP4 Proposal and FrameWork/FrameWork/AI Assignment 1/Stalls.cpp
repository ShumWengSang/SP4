#include "Stalls.h"

CStalls::CStalls(void)
{
	gasMaskAmount = 0;
	maskPrice = 0;
}

CStalls::~CStalls(void)
{
}

int CStalls::getMaskNo()
{
	return gasMaskAmount;
}
int CStalls::getMaskPrice()
{
	return maskPrice;
}

void CStalls::setMaskNo(int mn)
{
	gasMaskAmount = mn;
}
void CStalls::setMaskPrice(int mp)
{
	maskPrice = mp;
}

void CStalls::buyMask(int amt)
{
	cout << "buy mask here" << endl;
	gasMaskAmount -= amt;
}
void CStalls::moveStall()
{
	//moveeeeee
}
