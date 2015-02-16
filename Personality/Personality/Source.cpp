
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <map>
#include "Personality.h"

class Stall
{
public:
	int Price;
	Vector3 Location;
};

class StoreHolder
{
public:

	bool Considered;
	Stall * theStall;
};

class Buyer
{
public:
	Buyer()
	{
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
	std::map<int,Stall*> ProbabilitytoBuyMask;

	Vector3 Position;

	bool WillBuyMask(int Price)
	{
		if (CurrentMoney < Price)
			return false;
		if (HasMask)
			return false;
		return true;
	}

	int GetFactors(int Price, int Distance, int Haze)
	{
		return (Price * hisPersonality.MoneyPreference) + (Distance * hisPersonality.DistancePreference) + (Haze * hisPersonality.HazePreference);
	}

	//Find all the stalls it will buy from, with their probability to buy.
	void WillBuy(int Haze)
	{
		for (auto i = theStalls.begin(); i != theStalls.end(); i++)
		{
			if (WillBuyMask((*i)->theStall->Price))
			{
				(*i)->Considered = true;
				//float Distance = (*i)->theStall->Location - Position;
				float Distance = 10;
				ProbabilitytoBuyMask.insert(std::pair<int, Stall*>((GetNumber((*i)->theStall->Price, Distance, Haze)), (*i)->theStall));
					//(GetNumber((*i)->theStall->Price, Distance, Haze));
			}
		}
	}

	int GetNumber(int Price, int Distance, int Haze)
	{
		//y= 2 ^x
		return pow(2, GetFactors(Price, Distance, Haze));
	}

	Stall * StalltoBuyFrom(int Haze)
	{
		WillBuy(Haze);
		if (ProbabilitytoBuyMask.empty())
		{
			return NULL;
		}
		int LeastNumber = 999;

		typedef std::map<int, Stall*>::iterator it_type;
		for (it_type iterator = ProbabilitytoBuyMask.begin(); iterator != ProbabilitytoBuyMask.end(); iterator++)
		{
			if (LeastNumber > iterator->first)
			{
				LeastNumber = iterator->first;
			}
		}
		if (LeastNumber > 100)
			return NULL;
		return ProbabilitytoBuyMask.find(LeastNumber)->second;
	}
};





void main()
{
	Stall * theStall = new Stall();
	theStall->Location = Vector3(5, 10);
	theStall->Price = 5;

	int Haze = 400;

	StoreHolder holder;
	holder.Considered = false;
	holder.theStall = theStall;


	Buyer TestBuyer;
	TestBuyer.theStalls.push_back(&holder);

	Stall * theStallPointer = TestBuyer.StalltoBuyFrom(Haze);


}