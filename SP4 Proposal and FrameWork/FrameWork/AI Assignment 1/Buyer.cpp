#include "Buyer.h"

Buyer::Buyer()
{
	Init();
	theGrid = NULL;
	theShopToBuy = NULL;
	Color.SetZero();
}

Buyer::Buyer(std::vector<CStalls*> theStalls, Grid * theGrid)
{
	this->theGrid = theGrid;
	for (unsigned int i = 0; i < theStalls.size(); i++)
	{
		Insert(theStalls[i]);
	}
	Init();
}

Buyer::~Buyer()
{
	if (!theStalls.empty())
	{
		for (unsigned int i = 0; i < theStalls.size(); i++)
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
	ProbabilitytoBuyMask.clear();
	for (auto i = theStalls.begin(); i != theStalls.end(); i++)
	{
		if (WillBuyMask( (static_cast<int>((*i)->theStall->Price))) )
		{
			(*i)->Considered = true;
			float Distance = ((*i)->theStall->getPosition() - Position).Length();
			//float Distance = 10;
			long long temp = (GetNumber( static_cast<int>((*i)->theStall->Price), static_cast<int>(Distance), Haze));
			if (temp < 0)
			{
				temp = 9999 + rand() % 1000;
			}
			ProbabilitytoBuyMask.insert(std::pair<long long, CStalls*>(temp, (*i)->theStall));
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
	StorePriorities.clear();
	WillBuy(Haze);
	if (ProbabilitytoBuyMask.empty())
	{
		return NULL;
	}
	long long LeastNumber = ProbabilitytoBuyMask.begin()->first;

	if (LeastNumber > 50)
		StorePriorities.push_back(ProbabilitytoBuyMask.begin()->second);

	typedef std::map<long long, CStalls*>::iterator it_type;
	for (it_type iterator = ProbabilitytoBuyMask.begin(); iterator != ProbabilitytoBuyMask.end(); iterator++)
	{
		if (LeastNumber < iterator->first)
		{
			LeastNumber = iterator->first;
			if (LeastNumber > 50)
				StorePriorities.push_back(iterator->second);
		}
	}
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
	if (ReachedLocation(*TargettoWalk.front()))
	{
		Velocity.Set(0, 0, 0);
		TargettoWalk.clear();
		Init();
		//TargettoWalk.push_back(Vector3(rand() % TILE_WORLD_SIZE_X, 0, rand() % TILE_WORLD_SIZE_Y));
	}
	else
	{
		GotoLocation(*TargettoWalk.back(), 5);
	}

	Position += Velocity * CTimer::getInstance()->getDelta();
}

bool Buyer::glRenderObject()
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	//glScalef(3, 3, 3);

	glColor3f(Color.x, Color.y, Color.z);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture); 
	theModel->Render();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glPopMatrix();
	return true;
}

void Buyer::AIUpdate()
{
	//TODO 
	//	if (theTileTemp != /*GET TILE INFO*/){


	switch (CurrentState)
	{
		case IDLEWALKING:
		{
							if (theTileTemp != theGrid->GetTile(this->Position) && theGrid->GetTile(this->Position) != NULL)
							{
								theTileTemp = theGrid->GetTile(this->Position);
								if (theTileTemp != NULL)
								{
									if (HasMask)
									{
										Color.Set(0, 0, 0);
									}
									else
									{
										CStalls * theStall = StalltoBuyFrom(theTileTemp->GetHaze());

										if (theStall != NULL)
										{
											theShopToBuy = theStall;
											TargettoWalk.push_back(&theShopToBuy->pos);
											CurrentState = GOINGTOBUY;

										}

									}
								}
							}
		}
		break;
		case GOINGTOBUY:
		{
						   theTileTemp = theGrid->GetTile(this->Position);
						   if (theTileTemp == NULL)
							   break;
						   if (theTileTemp->ShopOnTop == theShopToBuy && HasMask == false)
						   {
							   if (theShopToBuy->getMaskNo() <= 0)
							   {
								   StorePriority++;
								   if (StorePriority >= StorePriorities.size())
								   {
									   CurrentState = NOTHINGTOBUYWALK;
									   for (unsigned int i = TargettoWalk.size(); i !=  1; i--)
									   {
										   TargettoWalk.pop_back();
									   }
								   }
								   else
								   {
									   theShopToBuy = StorePriorities[StorePriority];
									   TargettoWalk.push_back(&theShopToBuy->pos);
								   }
							   }
							   else
							   {
								   HasMask = true;
								   Color.Set(0, 0, 0);
								   CurrentState = IDLEWALKING;
								   theTileTemp->ShopOnTop->buyMask(1);
								   for (unsigned int i = TargettoWalk.size(); i != 1; i--)
								   {
									   TargettoWalk.pop_back();
								   }
							   }
						   }
		}
		break;
		case NOTHINGTOBUYWALK:

		break;
		default:
		break;
	}
}

void Buyer::Init()
{
	Color.Set(1, 1, 1);
	CurrentMoney = rand() % 20 + 1;
	theType = BUYER;
	CurrentState = IDLEWALKING;
	HasMask = false;
	theTileTemp = NULL;
	StorePriority = 0;
	hisPersonality.Init();

	int i = rand() % 4;
	Vector3 * temp;
	switch (i)
	{
		case 0:
		this->Position.Set(static_cast<float>(rand() % TILE_WORLD_SIZE_X), 0, 0);
		temp = new Vector3(Vector3(static_cast<float>(rand() % TILE_WORLD_SIZE_X), 0, TILE_WORLD_SIZE_Y));
		TargettoWalk.push_back(temp);
		break;

		case 1:
		this->Position.Set(static_cast<float>(rand() % TILE_WORLD_SIZE_X), 0, TILE_WORLD_SIZE_Y);
		temp = new Vector3(static_cast<float>(rand() % TILE_WORLD_SIZE_X), 0, 0);
		TargettoWalk.push_back(temp);
		break;

		case 2:
			this->Position.Set(0, 0, static_cast<float>(rand() % TILE_WORLD_SIZE_Y));
			temp = new Vector3(TILE_WORLD_SIZE_X, 0, static_cast<float>(rand() % TILE_WORLD_SIZE_Y));
			TargettoWalk.push_back(temp);
		break;
		case 3:
			this->Position.Set(TILE_WORLD_SIZE_X, 0, static_cast<float>(rand() % TILE_WORLD_SIZE_Y));
			temp = new Vector3(0, 0, static_cast<float>(rand() % TILE_WORLD_SIZE_Y));
			TargettoWalk.push_back(temp);
		break;

		default:
		//this->Position.Set(0, 0, 0);
		//TargettoWalk.push_back(Vector3(TILE_WORLD_SIZE_X, 0, TILE_WORLD_SIZE_Y));
		break;
	}


	theModel = new CObjectModel();
	theModel->theObj = LoadOBJ("./models/People.obj");
	theModel->SetPosition( Vector3 (0,(static_cast<int>(0.8)),0));
}


bool Buyer::ReachedLocation(Vector3 thePosReached)
{
	return 1 > (thePosReached - this->Position).Length();
}


void Buyer::GotoLocation(Vector3 theNewPos, float speed)
{
	Vector3 TheDirection(theNewPos - this->Position);
	if (TheDirection.Length() > 1)
		TheDirection.Normalize();
	TheDirection *= speed;
	this->Velocity = TheDirection;
}