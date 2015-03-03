#include "MoneyAnimation.h"
#include "TextureSingleton.h"


CMoneyAnimation::CMoneyAnimation(void)
{
	Init();
}

CMoneyAnimation::~CMoneyAnimation(void)
{
	//drop();
}

void CMoneyAnimation::LoadTexture()
{
	TextureSingleton * theTex = TextureSingleton::getInstance();

	moneyTexture[0].texID = theTex->GetNumber(42);
}

void CMoneyAnimation::Init()
{
	LoadTexture();
	position = 0, 0, 0;
	spdCounter = 2;
	animationCounter = 0;
	count = 0;
	speed = 0.5f;
	active = false;
}

void CMoneyAnimation::drop()
{

}

void CMoneyAnimation::Update()
{
	if(this->active)
	{
		this->setFly();
	}
	if(position.y >= 10)
	{
		active = false;
		position.y = 0;
	}
}

Vector3 CMoneyAnimation::getPos()
{
	return position;
}

int CMoneyAnimation::getPosX()
{
	return static_cast<int>(position.x);
}

int CMoneyAnimation::getPosY()
{
	return static_cast<int>(position.y);
}

int CMoneyAnimation::getAnimationCounter(void)
{
	return animationCounter;
}

void CMoneyAnimation::setPos(Vector3 pos)
{
	this->position = pos;
}

void CMoneyAnimation::setPosX(int x)
{
	this->position.x = static_cast<float>(x);
}

void CMoneyAnimation::setPosY(int y)
{
	this->position.y = static_cast<float>(y);
}

void CMoneyAnimation::setFly()
{
	this->position.y += speed;
}

void CMoneyAnimation::setAnimationCounter(int ac)
{
	this->animationCounter = ac;
}

void CMoneyAnimation::drawMoney()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, moneyTexture[0].texID);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0,0);
				glTexCoord2f(1, 0); glVertex2f(1,0);
				glTexCoord2f(1, 1);	glVertex2f(1,1);
				glTexCoord2f(0, 1); glVertex2f(0,1);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}
