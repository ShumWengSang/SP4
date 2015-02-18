#include "Stalls.h"

CStalls::CStalls(void)
{
	gasMaskAmount = 0;
}

CStalls::~CStalls(void)
{
}

int CStalls::getMaskNo()
{
	return gasMaskAmount;
}
void CStalls::setMaskNo(int mn)
{
	gasMaskAmount = mn;
}

void CStalls::buyMask(int amt)
{
	cout << "buy mask here" << endl;
}
void CStalls::moveStall()
{
	//moveeeeee
}
