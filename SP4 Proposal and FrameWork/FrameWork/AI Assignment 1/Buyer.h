#pragma once
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <map>
#include "Personality.h"
#include <iostream>
#include "Vector3.h"
#include "Stalls.h"

#include "gl\freeglut.h"
//#include <Windows.h>
//#include <gl\GL.h>
//#include <gl\GLU.h>

enum BuyerAIStates
{
	IDLEWALKING,
	GOINGTOBUY
};

class StoreHolder
{
public:

	bool Considered;
	CStalls * theStall;
};

class Buyer : public Entity
{

public:
	Buyer();
	~Buyer();

	int CurrentMoney;
	bool HasMask;
	int Texture;
	Personality hisPersonality;
	Vector3 Position;
	BuyerAIStates CurrentState;

	std::vector<StoreHolder*> theStalls;
	std::map<long long, CStalls*> ProbabilitytoBuyMask;

	Vector3 TargettoWalk;

	bool WillBuyMask(int Price);
	float GetFactors(int Price, int Distance, int Haze);
	//Find all the stalls it will buy from, with their probability to buy.
	void WillBuy(int Haze);
	long long GetNumber(int Price, int Distance, int Haze);
	CStalls * StalltoBuyFrom(int Haze);
	void Insert(CStalls * theStall);

	/////////////////////////////////////////////////////////////////
	//Base Entity Functions
	void Update();
	void Render();
};
