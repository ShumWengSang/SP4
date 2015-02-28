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
		if (LeastNumber < iterator->first)
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
	if (ReachedLocation(TargettoWalk.back()))
	{
		Velocity.Set(0, 0, 0);
		TargettoWalk.clear();
		Init();
		//TargettoWalk.push_back(Vector3(rand() % TILE_WORLD_SIZE_X, 0, rand() % TILE_WORLD_SIZE_Y));
	}
	else
	{
		GotoLocation(TargettoWalk.back(), 5);
	}

	Position += Velocity * CTimer::getInstance()->getDelta();
}

bool Buyer::glRenderObject()
{
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	//glScalef(3, 3, 3);
	glBegin(GL_QUADS);
	glColor3f(Color.x, Color.y, Color.z);
	glVertex3f(0.5, 1, 0.5);
	glVertex3f(1.0, 1, 0.5);
	glVertex3f(1.0, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();

	
	theModel->Render();

	glPopMatrix();
	return true;
}

void Buyer::AIUpdate()
{
	//TODO 
	//	if (theTileTemp != /*GET TILE INFO*/){
	if (theTileTemp != theGrid->GetTile(this->Position))
	{
		theTileTemp = theGrid->GetTile(this->Position);
		if (theTileTemp != NULL)
		{

			switch (CurrentState)
			{
				case IDLEWALKING:
					{
						if (HasMask)
						{
							Color.Set(0, 1, 0);
						}
						else
						{
							CStalls * theStall = StalltoBuyFrom(theTileTemp->GetHaze());
							std::cout << "HAZE NMBER" << theTileTemp->GetHaze() << std::endl;

							if (theStall != NULL)
							{
								Color.Set(0, 0, 1);
								TargettoWalk.push_back(theStall->getPosition());
								CurrentState = GOINGTOBUY;
								theShopToBuy = theStall;
							}
						}

					}
					break;
				case GOINGTOBUY:
					{
						if (theTileTemp->ShopOnTop == theShopToBuy)
						{
							HasMask = true;
							Color.Set(1, 0, 0);
							CurrentState = IDLEWALKING;
							theTileTemp->ShopOnTop->setMaskSold(1);
							for (unsigned int i = 0; i < TargettoWalk.size() - 1; i++)
							{
								TargettoWalk.pop_back();
							}
						}
					}
					break;
				default:
					break;
			}
		}
	}
}

void Buyer::Init()
{
	CurrentMoney = rand() % 20 + 1;
	theType = BUYER;
	CurrentState = IDLEWALKING;
	HasMask = false;
	theTileTemp = NULL;

	int i = rand() % 4;
	switch (i)
	{
		case 0:
		this->Position.Set(rand() % TILE_WORLD_SIZE_X, 0, 0);
		TargettoWalk.push_back(Vector3(rand() % TILE_WORLD_SIZE_X, 0, TILE_WORLD_SIZE_Y));
		break;

		case 1:
		this->Position.Set(rand() % TILE_WORLD_SIZE_X, 0, TILE_WORLD_SIZE_Y);
		TargettoWalk.push_back(Vector3(rand() % TILE_WORLD_SIZE_X, 0, 0));
		break;

		case 2:
			this->Position.Set(0, 0, rand() % TILE_WORLD_SIZE_Y);
			TargettoWalk.push_back(Vector3(TILE_WORLD_SIZE_X, 0, rand() % TILE_WORLD_SIZE_Y));
		break;
		case 3:
			this->Position.Set(TILE_WORLD_SIZE_X, 0, rand() % TILE_WORLD_SIZE_Y);
			TargettoWalk.push_back(Vector3(0, 0, rand() % TILE_WORLD_SIZE_Y));
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