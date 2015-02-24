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

//Entity Functions
bool CStalls::glRenderObject() {
	glPushMatrix();
		glEnable(GL_BLEND);
		glTranslatef( pos.x, pos.y, pos.z );
		glScalef(scale.x, scale.y, scale.z);
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_QUADS);
			glVertex3f(5, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 5, 0);
			glVertex3f(5, 5, 0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();
	return true;
}

EntityType CStalls::getObjectType(void) {
	return EntityType::STALLS;
}

Vector3 CStalls::getPosition(void) {
	return pos;
}

bool CStalls::operator== (Entity& o) {
	return bool(getObjectType() == o.getObjectType() && getPosition() == o.getPosition());
}

Vector3 CStalls::GetScale() {
	return scale;
}

void CStalls::Update() {

}