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

class StoreHolder
{
public:

	bool Considered;
	CStalls * theStall;
};

class Buyer
{
public:
	Buyer()
	{
		CurrentMoney = rand() % 10 + 1;
	}
	~Buyer()
	{
		if (!theStalls.empty())
		{
			for (int i = 0; i < theStalls.size(); i++)
			{
				theStalls[i] = NULL;
				theStalls.pop_back();
			}
		}
	}
	int CurrentMoney;
	bool HasMask;

	std::vector<StoreHolder*> theStalls;
	Personality hisPersonality;

	void Update();
	void Render();
	std::map<long long, Stall*> ProbabilitytoBuyMask;

	Vector3 Position;

	bool WillBuyMask(int Price)
	{
		if (CurrentMoney < Price)
			return false;
		if (HasMask)
			return false;
		return true;
	}

	float GetFactors(int Price, int Distance, int Haze)
	{
		float i = -(Price * hisPersonality.MoneyPreference) - (Distance * hisPersonality.DistancePreference) + (Haze * hisPersonality.HazePreference);
		return i;
	}

	//Find all the stalls it will buy from, with their probability to buy.
	void WillBuy(int Haze)
	{
		for (auto i = theStalls.begin(); i != theStalls.end(); i++)
		{
			if (WillBuyMask((*i)->theStall->Price))
			{
				(*i)->Considered = true;
				float Distance = ((*i)->theStall->Location - Position).Length();
				//float Distance = 10;
				ProbabilitytoBuyMask.insert(std::pair<long long, Stall*>((GetNumber((*i)->theStall->Price, Distance, Haze)), (*i)->theStall));
				//(GetNumber((*i)->theStall->Price, Distance, Haze));
			}
		}
	}

	long long GetNumber(int Price, int Distance, int Haze)
	{
		//y= 2 ^x
		long long i = pow(2, GetFactors(Price, Distance, Haze)* 0.05);
		return i;
	}

	Stall * StalltoBuyFrom(int Haze)
	{
		WillBuy(Haze);
		if (ProbabilitytoBuyMask.empty())
		{
			return NULL;
		}
		long long LeastNumber = ProbabilitytoBuyMask.begin()->first;

		typedef std::map<long long, Stall*>::iterator it_type;
		for (it_type iterator = ProbabilitytoBuyMask.begin(); iterator != ProbabilitytoBuyMask.end(); iterator++)
		{
			if (LeastNumber > iterator->first)
			{
				LeastNumber = iterator->first;
			}
		}
		if (LeastNumber)
			std::cout << "LeastNumber " << LeastNumber << std::endl;
		if (LeastNumber < 50)
			return NULL;
		return ProbabilitytoBuyMask.find(LeastNumber)->second;
	}

	void Insert(Stall * theStall)
	{
		StoreHolder * holder = new StoreHolder();
		holder->Considered = false;
		holder->theStall = theStall;
		theStalls.push_back(holder);
	}
};
