#include "MoneyAnimation.h"

CMoneyAnimation::CMoneyAnimation(void)
{
	Init();
}

CMoneyAnimation::~CMoneyAnimation(void)
{
}

void CMoneyAnimation::LoadTexture()
{
	CApplication::getInstance()->LoadTGA(&moneyTexture[0],"images/playState/money.tga");
}

void CMoneyAnimation::Init()
{
	LoadTexture();
	position = 0, 0, 0;
	spdCounter = 2;
	animationCounter = 0;
	count = 0;
	active = false;
}

void CMoneyAnimation::Update()
{
	if(this->active)
	{
		this->setFly();
	}
	if(position.y >= 20)
		active = false;
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
	this->position.y ++;
}

void CMoneyAnimation::setAnimationCounter(int ac)
{
	this->animationCounter = ac;
}

void CMoneyAnimation::drawMoney()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glEnable( GL_BLEND );
		glEnable( GL_TEXTURE_2D );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBindTexture( GL_TEXTURE_2D, moneyTexture[0].texID );
		noSpriteframe = 2;
		deltaSprite = (float)1/noSpriteframe;
		spdCounter = 10;

		if(animationCounter >= spdCounter) {
			++count;
			animationCounter = 0;
			if(count > noSpriteframe-1) {
				count = 0;
			}
		}
		glBegin(GL_QUADS);
			glTexCoord2f(deltaSprite * count,1);				glVertex2f(1,1);
			glTexCoord2f(deltaSprite * count,0);				glVertex2f(1,0);
			glTexCoord2f(deltaSprite * count + deltaSprite,0);	glVertex2f(0,0);
			glTexCoord2f(deltaSprite * count + deltaSprite,1);	glVertex2f(0,1);
		glEnd();
		glDisable( GL_TEXTURE_2D );
		glDisable( GL_BLEND );
	glPopMatrix();
}
