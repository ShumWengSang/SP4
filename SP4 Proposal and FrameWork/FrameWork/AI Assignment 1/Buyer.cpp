#include "Buyer.h"

Buyer::Buyer()
{
	CurrentMoney = rand() % 10 + 1;
	theType = BUYER;
	CurrentState = IDLEWALKING;
}

Buyer::~Buyer()
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

bool Buyer::WillBuyMask(int Price)
{
	if (CurrentMoney < Price)
		return false;
	if (HasMask)
		return false;
	return true;
}

float Buyer::GetFactors(int Price, int Distance, int Haze)
{
	return -(Price * hisPersonality.MoneyPreference) - (Distance * hisPersonality.DistancePreference) + (Haze * hisPersonality.HazePreference);
}

void Buyer::WillBuy(int Haze)
{
	for (auto i = theStalls.begin(); i != theStalls.end(); i++)
	{
		if (WillBuyMask((*i)->theStall->Price))
		{
			(*i)->Considered = true;
			float Distance = ((*i)->theStall->getPosition() - Position).Length();
			//float Distance = 10;
			ProbabilitytoBuyMask.insert(std::pair<long long, CStalls*>((GetNumber((*i)->theStall->Price, Distance, Haze)), (*i)->theStall));
			//(GetNumber((*i)->theStall->Price, Distance, Haze));
		}
	}
}

long long Buyer::GetNumber(int Price, int Distance, int Haze)
{
	return pow(2, GetFactors(Price, Distance, Haze)* 0.05);
}

CStalls * Buyer::StalltoBuyFrom(int Haze)
{
	WillBuy(Haze);
	if (ProbabilitytoBuyMask.empty())
	{
		return NULL;
	}
	long long LeastNumber = ProbabilitytoBuyMask.begin()->first;

	typedef std::map<long long, CStalls*>::iterator it_type;
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

void Buyer::Insert(CStalls * theStall)
{
	StoreHolder * holder = new StoreHolder();
	holder->Considered = false;
	holder->theStall = theStall;
	theStalls.push_back(holder);
}

void Buyer::Update()
{
	switch (CurrentState)
	{
		case IDLEWALKING:
		{
			//Every update, get tile information. Use this information to determine whether you will buy a mask.
		}
		break;
		case GOINGTOBUY:
		{

		}
		break;
		default:
		break;
	}
}

void Buyer::Render()
{
	glPushMatrix();

	glPopMatrix();
}