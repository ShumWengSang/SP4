#include "Stalls.h"

CStalls::CStalls(Vector3 pos, Vector3 scale)
{
	gasMaskAmount = 0;
	maskSold = 0;
	totalMaskSold = 0;
	Selected = false;
	isPicking = false;
	colour.SetZero();
	colour2.SetZero();

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
Vector3 CStalls::getColour2()
{
	return colour2;
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
	theModel->SetPosition( Vector3(static_cast<float>(pos.x+ static_cast<float>(TILE_SIZE_X / 2)), pos.y, static_cast<float>(pos.z+ static_cast<float>(TILE_SIZE_Y / 2)) ) );
}
void CStalls::setScale(Vector3 scale)
{
	this->scale = scale;
}
void CStalls::setColour(Vector3 colour)
{
	this->colour = colour;
}
void CStalls::setColour2(Vector3 colour2)
{
	this->colour2 = colour2;
}

void CStalls::buyMask(int maskNo)
{
	if(getMaskNo() >= getMaskSold())
	{
		setMaskSold(maskNo);
		setTotalMaskSold(maskNo);
		setMaskNo(getMaskNo() - getMaskSold());
		theMoney.setCurrentMoney(getTotalMaskSold() * getMaskPrice());

		theMAnimation.active = true;
		theMAnimation.setPos(getPosition());

		cout << "mask sold " <<  getMaskSold() << endl;
		cout << "mask in stall: " << getMaskNo() << endl;
		cout << "total mask sold: " << getTotalMaskSold() << endl;
		cout << "Money: " << theMoney.getCurrentMoney() << endl;
		cout << "/////////////////////////////////////" << theMAnimation.active << endl;
	}
}

//Entity Functions
bool CStalls::glRenderObject() {
	glPushMatrix();
		glEnable(GL_BLEND);
		
		if(isPicking)
			glColor3f(colour.x, colour.y, colour.z);
		else
			glColor3f(colour2.x, colour2.y, colour2.z);
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

