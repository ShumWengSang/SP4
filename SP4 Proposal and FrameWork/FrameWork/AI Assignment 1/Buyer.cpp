#include "Buyer.h"

Buyer::Buyer()
{
	CurrentMoney = rand() % 10 + 1;
	theType = BUYER;
	CurrentState = IDLEWALKING;
	HasMask = false;
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
	AIUpdate();

	Vector3 * Target = &TargettoWalk.back();
	float TempX = Position.x - Target->x;
	float TempY = Position.z - Target->z;
	TempX = abs(TempX);
	TempY = abs(TempY);

	if (TempX > TempY && TempY != 0)
	{
		Velocity.Set(0, 0, 1);
	}
	else if (TempY > TempX && TempX != 0)
	{
		Velocity.Set(1, 0, 0);
	}
	else
	{
		Velocity.SetZero();
	}

	Position += Velocity;


}

void Buyer::Render()
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glScalef(5, 5, 5);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(1.0, 1, 0.5);
	glVertex3f(1.0, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	glPopMatrix();
}

void Buyer::AIUpdate()
{
	//TODO 
	//	if (theTileTemp != /*GET TILE INFO*/){
	switch (CurrentState)
	{
		case IDLEWALKING:
		{

							//Every update, get tile information. Use this information to determine whether you will buy a mask.
							if (HasMask)
							{

							}
							else
							{
								/*CStall * theStall = WillBuy(/*HAZE INFO)
								TargettoWalk.push_back(theStall->Position);
								CurrentState = GOINGTOBUY
								*/
							}
		}
		break;
		case GOINGTOBUY:
		{

						   //	theTileTemp = gettileinfo
						   //Every update, get tile information. Use this information to determine whether you will buy a mask.
						   if (HasMask)
						   {

						   }
						   else
						   {
							   /*CStall * theStall = WillBuy(/*HAZE INFO)
							   TargettoWalk.pop_back();
							   TargettoWalk.push_back(theStall->Position);

							   */
						   }

						   //Check if tile has the shop.
						   /*if(theTileTemp.hasshop == true)
						   {
						   HasMask = true;
						   CurrentState = GOINGTOBUY;
						   //ADD MONEY FOR SHOPS/
						   //MINUS MASKS FOR SHOPS
						   }
						   */

		}
		break;
		default:
		break;
	}
//}
}