#include "Stalls.h"

CStalls::CStalls(Vector3 pos, Vector3 scale)
{
	gasMaskAmount = 0;
	maskSold = 0;
	totalMaskSold = 0;
	Selected = false;

	this->pos = pos;
	this->scale = scale;
	Price = 1;

	theModel = new CObjectModel();
	theModel->theObj = LoadOBJ("./models/Stall.obj");
	theModel->SetPosition( pos);
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
Vector3 CStalls::getColour()
{
	return colour;
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
void CStalls::setPos(Vector3 pos)
{
	this->pos = pos;
	theModel->SetPosition( Vector3(pos.x+4.5, pos.y, pos.z+4.5) );
}
void CStalls::setScale(Vector3 scale)
{
	this->scale = scale;
}
void CStalls::setColour(Vector3 colour)
{
	this->colour = colour;
}

void CStalls::buyMask(int amt)
{
	gasMaskAmount -= amt;
}

//Entity Functions
bool CStalls::glRenderObject() {
	glPushMatrix();
		glEnable(GL_BLEND);
		
		glColor3f(colour.x, colour.y, colour.z);
		if(Selected) {
			glTranslatef(0,2,0);
		}
		theModel->Render();
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

