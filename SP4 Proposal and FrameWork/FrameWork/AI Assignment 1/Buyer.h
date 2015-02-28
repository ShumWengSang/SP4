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
#include "TileChilds.h"
#include "Grid.h"
#include "Timer.h"

#include "ObjectModel.h"

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
	Buyer(std::vector<CStalls*>, Grid *);
	~Buyer();

	CObjectModel* theModel;

	int CurrentMoney;
	bool HasMask;
	int Texture;
	Personality hisPersonality;
	Vector3 Position;
	Vector3 Velocity;
	Vector3 Color;
	BuyerAIStates CurrentState;
	Tiles * theTileTemp;
	CStalls * theShopToBuy;

	void GotoLocation(Vector3 theNewPos, float speed);
	bool ReachedLocation(Vector3 thePosReached);

	std::vector<StoreHolder*> theStalls;
	std::map<long long, CStalls*> ProbabilitytoBuyMask;
	std::vector<Vector3> TargettoWalk;

	bool WillBuyMask(int Price);
	float GetFactors(int Price, int Distance, int Haze);
	long long GetNumber(int Price, int Distance, int Haze);
	CStalls * StalltoBuyFrom(int Haze);
	void Insert(CStalls * theStall);
	void WillBuy(int Haze);
	void AIUpdate();
	void Init();

	Grid * theGrid;
	
	/////////////////////////////////////////////////////////////////
	//Base Entity Functions
	void Update();
	bool glRenderObject();
};
