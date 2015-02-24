#include "Stalls.h"

CStalls::CStalls(void)
{
	gasMaskAmount = 0;
	maskSold = 0;
	totalMaskSold = 0;
}

CStalls::~CStalls(void)
{
}

int CStalls::getMaskNo()
{
	return gasMaskAmount;
}
int CStalls::getMaskSold()
{
	return maskSold;
}
int CStalls::getTotalMaskSold()
{
	return totalMaskSold;
}
int CStalls::getMaskPrice()
{
	return theMoney.getPrice();
}

void CStalls::setMaskNo(int mn)
{
	gasMaskAmount = mn;
}
void CStalls::setMaskSold(int ms)
{
	maskSold = ms;
}
void CStalls::setTotalMaskSold(int ms)
{
	totalMaskSold += ms;
}
void CStalls::setMaskPrice(int mp)
{
	theMoney.setPrice(mp);
}

void CStalls::buyMask(int amt)
{
	gasMaskAmount -= amt;
}

void CStalls::moveStall()
{
	//moveeeeee
}

//bool CStalls::glRenderObject() {
//
//}
//
//EntityType CStalls::getObjectType(void) {
//
//}
//
//Vector3 CStalls::getPosition(void) {
//
//}
//
//bool CStalls::operator== (Entity& o) {
//
//}
//
//Vector3 CStalls::GetScale() {
//
//}
//
//void CStalls::Update() {
//
//}

