#pragma once
#include "Vector3.h"
#include "TextureImage.h"
#include "Application.h"

class CMoneyAnimation
{
	TextureImage moneyTexture[1];
	Vector3 position;
	int noSpriteframe;
	float deltaSprite;
	int spdCounter;
	int animationCounter;
	int count;
	float speed;
public:
	CMoneyAnimation(void);
	~CMoneyAnimation(void);
	void Init();
	void Update();
	void drop();

	void LoadTexture();

	Vector3 getPos();
	int getPosX();
	int getPosY();
	int getAnimationCounter(void);

	void setPos(Vector3 pos);
	void setPosX(int x);
	void setPosY(int y);
	void setFly();
	void setAnimationCounter(int ac);

	bool isActive(){ return active; };

	void drawMoney();

	bool active;
private:
};

