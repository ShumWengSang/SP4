#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

enum GAMEOBJECT_TYPE
{
	GO_PLAYER = 0,
	GO_CIVILIAN,
	GO_POLICE, //must be last
};

struct s_player
{
	
	int wantedlvl;

	s_player()
		:wantedlvl(0)
	{}

};

struct s_police
{
	
	bool melee;
	bool shoot;
	bool alerted;

	s_police()
		:melee(false)
		,shoot(false)
		,alerted(false)
	{}

};

struct GameObject
{
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 color;
	bool active;
	float mass;
	int hp;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_PLAYER);
	~GameObject();
};

#endif