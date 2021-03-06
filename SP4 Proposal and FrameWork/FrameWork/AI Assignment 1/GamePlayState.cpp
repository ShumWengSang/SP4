#include "GamePlayState.h"
#include "EndOfDayState.h"
#include "PlayState.h"
#include "TextureSingleton.h"

CGamePlayState *CGamePlayState::theGamePlayState = NULL;

void CGamePlayState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	Tiles::TexID = theInstance->GetNumber(36);

	for (int i = 0; i < 3; i++) //shop 1, 2, 3
	{
		button[i + 1].texID = theInstance->GetNumber(i + 23);
	}
	button[0].texID = theInstance->GetNumber(29); //pause

	for (int i = 0; i < 3; i++) //shopSelected 1, 2, 3
	{
		button[i + 4].texID = theInstance->GetNumber(i + 26);
	}

	for (int i = 0; i < 6; i++)
	{
		skyBox[i].texID = theInstance->GetNumber(i + 30);
	}

	buyingButton[0].texID = theInstance->GetNumber(37);
	for (int i = 0; i < 3; i++)
	{
		buyingButton[i + 1].texID = theInstance->GetNumber(i + 10);
	}
	buyingBackground[0].texID = theInstance->GetNumber(13);

	ControlTexID = theInstance->GetNumber(47);
}

void CGamePlayState::LoadButtons()
{
	theButton[pause] = new CButtons(SCREEN_WIDTH/4 + 5, 1, 32, 32, pause);
	theButton[pause]->setButtonTexture(button[0].texID);

	theButton[shop] = new CButtons(0, SCREEN_HEIGHT - 50, 70, 50, shop);
	theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2] = new CButtons(80, SCREEN_HEIGHT - 50, 70, 50, shop2);
	theButton[shop2]->setButtonTexture(button[2].texID);

	theButton[shop3] = new CButtons(160, SCREEN_HEIGHT - 50, 70, 50, shop3);
	theButton[shop3]->setButtonTexture(button[3].texID);

	theBuyingButton[close] = new CButtons(SCREEN_WIDTH - 45, SCREEN_HEIGHT - 320, 32, 32, close);
	theBuyingButton[close]->setButtonTexture(buyingButton[0].texID);

	theBuyingButton[bpFifty] = new CButtons(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 70, 70, 50, bpFifty);
	theBuyingButton[bpFifty]->setButtonTexture(buyingButton[1].texID);
	
	theBuyingButton[bpHundred] = new CButtons(SCREEN_WIDTH - 210, SCREEN_HEIGHT - 70, 70, 50, bpHundred);
	theBuyingButton[bpHundred]->setButtonTexture(buyingButton[2].texID);
	
	theBuyingButton[bpTwohundred] = new CButtons(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 70, 70, 50, bpTwohundred);
	theBuyingButton[bpTwohundred]->setButtonTexture(buyingButton[3].texID);
}

void CGamePlayState::Init()
{

	theGrid = NULL;
	for (int i = 0; i < 4; i++)
	{
		theButton[i] = NULL;
	}
	for (int i = 0; i < 3; i++)
	{
		theStall[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		theButton[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		theBuyingButton[i] = NULL;
	}

	thisState = PlayGameState;

	theGrid = new Grid();

	isPause = false;
	isBuying = false;

	//TODO drop these textures hopefully.
	LoadTextures();
	LoadButtons();

	barPos.Set(SCREEN_WIDTH/2.9, 10, 0);
	theTimeBar.init(1.0, 0.0, 0.0, barPos);
	
	font_style = GLUT_BITMAP_HELVETICA_18;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;

	CInputSystem::getInstance()->mouseInfo.mLClicked = false;
	CInputSystem::getInstance()->mouseInfo.mLReclicked = true;
	CInputSystem::getInstance()->mouseInfo.mRButtonUp = true;
	CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;

	Camera::getInstance()->Reset();
	Camera::getInstance()->SetPos(Vector3(TILE_NO_X * TILE_SIZE_X / 2, 0, TILE_NO_X * TILE_SIZE_X / 2));
	//Isometric view
	Camera::getInstance()->SetCameraType(Camera::AIR_CAM);	

	CPlayState * PlayState = CPlayState::Instance();
	HourNumber = 0;
	SeedHaze();

	theTimerInstance = CTimer::getInstance();
	TimerKeySeed = theTimerInstance->insertNewTime(HourTime);
	TimerKeyDay = theTimerInstance->insertNewTime(HourTime * DayTime);

	TimerKeySeedTI = 0;
	TimerKeyDayTI = 0;

	TimerHalfHour = theTimerInstance->insertNewTime(HourTime / 2);

	Buyer * newBuyer;

	std::vector<CStalls*> theListofStalls;
	for (int i = 0; i < 3; i++)
	{
		theListofStalls.push_back(CPlayState::Instance()->theStall[i]);
	}

	for (int i = 0; i < STARTINGAMOUNTOFBUYERS; i++)
	{
		newBuyer = new Buyer(theListofStalls, theGrid);
		newBuyer->Texture = TextureSingleton::getInstance()->GetNumber(57);
		theListofEntities.push_back(newBuyer);
	}

	theListofEntities.push_back(CPlayState::Instance()->theStall[0]);
	theListofEntities.push_back(CPlayState::Instance()->theStall[1]);
	theListofEntities.push_back(CPlayState::Instance()->theStall[2]);
	theListofEntities.push_back(theGrid);
	
	CPlayState::Instance()->theStall[0]->Selected = false;
	CPlayState::Instance()->theStall[1]->Selected = false;
	CPlayState::Instance()->theStall[2]->Selected = false;

	CPlayState::Instance()->theStall[0]->setColour2(Vector3(0.5,0.5,1)); //B
	CPlayState::Instance()->theStall[1]->setColour2(Vector3(1,0.5,0.5)); //R
	CPlayState::Instance()->theStall[2]->setColour2(Vector3(0.5,1,0.5)); //G
}

void CGamePlayState::SeedHaze()
{
	int DayNumber = CPlayState::Instance()->day;
	int Seeds = 0;
	while (Seeds != SEEDCOUNT)
	{
		int x = rand() % TILE_NO_X;
		int y = rand() % TILE_NO_Y;

		if (!((x == 0 || (x == (TILE_NO_X - 1))) && ((y == 0 || y == (TILE_NO_Y - 1)))))
		{
			theGrid->temp[x][y].Seeded(/*static_cast<int>*/pow((CPlayState::Instance()->theHaze.HazeGraph[HourNumber + (DayNumber - 1) * DayTime] ),3));
			theSeededTiles.push_back(&theGrid->temp[x][y]);
			Seeds++;
		}

	}
}

void CGamePlayState::Cleanup()
{}

void CGamePlayState::Pause()
{
	if(isPause == false){
		isPause = true;
		TimerKeySeedTI = theTimerInstance->getTimeInterval(TimerKeySeed);
		TimerKeyDayTI = theTimerInstance->getTimeInterval(TimerKeyDay);
	}
}

void CGamePlayState::Resume()
{
	if(isPause == true){
		isPause = false;
		theTimerInstance->setTimeInterval(TimerKeySeed,TimerKeySeedTI);
		theTimerInstance->setTimeInterval(TimerKeyDay,TimerKeyDayTI);
	}
}

void CGamePlayState::HandleEvents(CInGameStateManager* theGSM)
{}

void CGamePlayState::Update(CInGameStateManager* theGSM) 
{
	keyboardUpdate();
	Camera::getInstance()->newUpdate();
	if(!isPause)
	{
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			(*i)->Update();
		}

		if (theTimerInstance->executeTime(TimerKeySeed))
		{
			HourNumber++;
		}
		if (theTimerInstance->executeTime(TimerHalfHour))
		{
			if(HourNumber != DayTime)
				SeedHaze();
		}
		theTimeBar.update(static_cast<float>(HourNumber));
		if (HourNumber == DayTime)
		{
			CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
		}

		CPlayState::Instance()->earned = CPlayState::Instance()->theStall[0]->getTotalMaskSold() * CPlayState::Instance()->theStall[0]->getMaskPrice();
		CPlayState::Instance()->earned2 = CPlayState::Instance()->theStall[1]->getTotalMaskSold() * CPlayState::Instance()->theStall[1]->getMaskPrice();
		CPlayState::Instance()->earned3 = CPlayState::Instance()->theStall[2]->getTotalMaskSold() * CPlayState::Instance()->theStall[2]->getMaskPrice();
		int totalEarn = CPlayState::Instance()->earned + CPlayState::Instance()->earned2 + CPlayState::Instance()->earned3;
		CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() );
	}
}

void CGamePlayState::Draw(CInGameStateManager* theGSM) 
{
	// Render Objects to be selected in the color scheme
	if(CInputSystem::getInstance()->mouseInfo.mLClicked == true)
	{
		theGrid->Click = true;
		CPlayState::Instance()->theStall[0]->isPicking = true;
		CPlayState::Instance()->theStall[1]->isPicking = true;
		CPlayState::Instance()->theStall[2]->isPicking = true;
		
		CPlayState::Instance()->theStall[0]->setColour(theGrid->GetTile(CPlayState::Instance()->theStall[0]->getPosition())->getColor());
		CPlayState::Instance()->theStall[1]->setColour(theGrid->GetTile(CPlayState::Instance()->theStall[1]->getPosition())->getColor());
		CPlayState::Instance()->theStall[2]->setColour(theGrid->GetTile(CPlayState::Instance()->theStall[2]->getPosition())->getColor());
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			if((*i)->getObjectType() == GRID || (*i)->getObjectType() == STALLS)
				(*i)->glRenderObject();
		}
		CApplication::getInstance()->setClickCheck(true);
		ClickCollision();
		CInputSystem::getInstance()->mouseInfo.mLClicked = false;
	}
	else
	{
		// Actual Render Here
		DrawSkyBox();

		theGrid->Click = false;
		CPlayState::Instance()->theStall[0]->isPicking = false;
		CPlayState::Instance()->theStall[1]->isPicking = false;
		CPlayState::Instance()->theStall[2]->isPicking = false;

		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			(*i)->glRenderObject();
		}
		theGrid->GetTile(CPlayState::Instance()->theStall[0]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[0];
		theGrid->GetTile(CPlayState::Instance()->theStall[1]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[1];
		theGrid->GetTile(CPlayState::Instance()->theStall[2]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[2];
		CApplication::getInstance()->setClickCheck(false);	
	}
	Camera::getInstance()->SetHUD(true);
	drawInfo();
	DrawButtons();
	DrawBuying();
	DrawTimeBar();
	Camera::getInstance()->SetHUD(false);
}

void CGamePlayState::DrawBuying()
{
	if(isBuying)
	{
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, buyingBackground[0].texID);
			glPushMatrix();
				glTranslatef(SCREEN_WIDTH - 320, SCREEN_HEIGHT - 330, 2);
				glScalef((static_cast<GLfloat>(0.4)), (static_cast<GLfloat>(0.55)), (static_cast<GLfloat>(1)));
				glBegin(GL_QUADS);
					glTexCoord2f(0, 0);	glVertex2f(0, SCREEN_HEIGHT);
					glTexCoord2f(1, 0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
					glTexCoord2f(1, 1);	glVertex2f(SCREEN_WIDTH, 0);
					glTexCoord2f(0, 1);	glVertex2f(0, 0);			
				glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();

		theBuyingButton[close]->drawButton();
		theBuyingButton[bpFifty]->drawButton();
		theBuyingButton[bpHundred]->drawButton();
		theBuyingButton[bpTwohundred]->drawButton();

		glPushMatrix();
			glPushAttrib(GL_DEPTH_TEST);
				//print shop number
				glColor3f( 1.0f, 0.0f, 0.0f);
				
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 270, 0,  "Current money: $%d", CPlayState::Instance()->theMoney.getCurrentMoney());

				if(CPlayState::Instance()->shop1selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 1-");
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[0]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[0]->getMaskPrice());
				}

				if(CPlayState::Instance()->shop2selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 2-");
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[1]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[1]->getMaskPrice());
				}

				if(CPlayState::Instance()->shop3selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 3-");
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[2]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[2]->getMaskPrice());
				}
				
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 140, 0, "Amount of masks to buy");
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 110, 0, "Price:");

				printw (SCREEN_WIDTH - 290, SCREEN_HEIGHT - 80, 0, "$300");
				printw (SCREEN_WIDTH - 200, SCREEN_HEIGHT - 80, 0, "$550");
				printw (SCREEN_WIDTH - 110, SCREEN_HEIGHT - 80, 0, "$1050");
			glPopAttrib();
		glPopMatrix();
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();	
		glBindTexture(GL_TEXTURE_2D, ControlTexID);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT / 4);
		glTexCoord2f(0, 0); glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
		glTexCoord2f(0, 1); glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH / 4, 0);
		glTexCoord2f(1, 1);	glVertex2f(SCREEN_WIDTH, 0);
		glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void CGamePlayState::DrawButtons()
{
	//pause game
	theButton[pause]->drawButton();

	//shop
	theButton[shop]->drawButton();
	if(CPlayState::Instance()->shop1selected)
		theButton[shop]->setButtonTexture(button[4].texID);
	else
		theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2]->drawButton();
	if(CPlayState::Instance()->shop2selected)
		theButton[shop2]->setButtonTexture(button[5].texID);
	else
		theButton[shop2]->setButtonTexture(button[2].texID);

	theButton[shop3]->drawButton();
	if(CPlayState::Instance()->shop3selected)
		theButton[shop3]->setButtonTexture(button[6].texID);
	else
		theButton[shop3]->setButtonTexture(button[3].texID);
}

void CGamePlayState::DrawSkyBox()
{
	glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glColor4f(1,1,1,1);
		glTranslatef(0, 50, 0);
		glTranslatef(TILE_NO_X * TILE_SIZE_X / 2, 0, TILE_NO_X * TILE_SIZE_X / 2);
		// Render the front quad
		glBindTexture(GL_TEXTURE_2D, skyBox[0].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(  100.0f, -100.0f, -100.0f );
			glTexCoord2f(1, 0); glVertex3f( -100.0f, -100.0f, -100.0f );
			glTexCoord2f(1, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
			glTexCoord2f(0, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
		glEnd();

		// Render the back quad
		glBindTexture(GL_TEXTURE_2D, skyBox[1].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( -100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 0); glVertex3f(  100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f,  100.0f );
			glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f,  100.0f );
		glEnd();

		// Render the left quad
		glBindTexture(GL_TEXTURE_2D, skyBox[2].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(  100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 0); glVertex3f(  100.0f, -100.0f, -100.0f );
			glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
			glTexCoord2f(0, 1); glVertex3f(  100.0f,  100.0f,  100.0f );
		glEnd();

		// Render the right quad
		glBindTexture(GL_TEXTURE_2D, skyBox[3].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( -100.0f, -100.0f, -100.0f );
			glTexCoord2f(1, 0); glVertex3f( -100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 1); glVertex3f( -100.0f,  100.0f,  100.0f );
			glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
		glEnd();

		// Render the top quad
		glBindTexture(GL_TEXTURE_2D, skyBox[4].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
			glTexCoord2f(0, 0); glVertex3f( -100.0f,  100.0f,  100.0f );
			glTexCoord2f(1, 0); glVertex3f(  100.0f,  100.0f,  100.0f );
			glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
		glEnd();

		// Render the bottom quad
		glBindTexture(GL_TEXTURE_2D, skyBox[5].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( -100.0f, -100.0f, -100.0f );
			glTexCoord2f(0, 1); glVertex3f( -100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 1); glVertex3f(  100.0f, -100.0f,  100.0f );
			glTexCoord2f(1, 0); glVertex3f(  100.0f, -100.0f, -100.0f );
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glPopAttrib();
	glPopMatrix();
}
			
void CGamePlayState::DrawTimeBar()
{
	glPushMatrix();
		glTranslatef(SCREEN_WIDTH/3.5,0,0);
		printw (20, 23, 0, "Time:");
	glPopMatrix();
	theTimeBar.draw();
}

void CGamePlayState::keyboardUpdate()
{
	if(CInputSystem::getInstance()->myKeys['a'])
		Camera::getInstance()->Strafe(-1);
	if(CInputSystem::getInstance()->myKeys['d'])
		Camera::getInstance()->Strafe(1);
	if(CInputSystem::getInstance()->myKeys['w'])
		Camera::getInstance()->Walk(1);
	if(CInputSystem::getInstance()->myKeys['s'])
		Camera::getInstance()->Walk(-1);


	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);

	//Camera Locking
	if(Camera::getInstance()->GetPos().x <= theGrid->getX())
	{Camera::getInstance()->SetPos(Vector3( static_cast<float>(theGrid->getX()), Camera::getInstance()->GetPos().y,Camera::getInstance()->GetPos().z));}
	else if(Camera::getInstance()->GetPos().x >= theGrid->getX() + TILE_SIZE_X*TILE_NO_X)
	{Camera::getInstance()->SetPos(Vector3(static_cast<float>(theGrid->getX() + TILE_SIZE_X*TILE_NO_X ),Camera::getInstance()->GetPos().y,Camera::getInstance()->GetPos().z));}
	if(Camera::getInstance()->GetPos().z <= theGrid->getY())
	{Camera::getInstance()->SetPos(Vector3(Camera::getInstance()->GetPos().x,Camera::getInstance()->GetPos().y, static_cast<float>(theGrid->getY()) ));}
	else if(Camera::getInstance()->GetPos().z >= theGrid->getY() + TILE_SIZE_Y*TILE_NO_Y)
	{Camera::getInstance()->SetPos(Vector3(Camera::getInstance()->GetPos().x,Camera::getInstance()->GetPos().y, static_cast<float>(theGrid->getY() + TILE_SIZE_Y*TILE_NO_Y) ));}
}

//Inputs
void CGamePlayState::MouseMove (int x, int y) {

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	if(!CInputSystem::getInstance()->mouseInfo.mRButtonUp)
		OnRotate(x,y);

	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CGamePlayState::MouseClick(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
				CInputSystem::getInstance()->mouseInfo.mLReclicked = true;
			}
			else 
			{
				if(theButton[pause]->isInside(x, y) && isPause == false)
				{
					Pause();
				}
				else if(theButton[pause]->isInside(x, y) && isPause == true)
				{
					Resume();
				}
				if (!isPause)
				{
					CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;

					if(theButton[shop]->isInside(x, y))
					{
						CPlayState::Instance()->shop1selected = true;
						CPlayState::Instance()->shop2selected = false;
						CPlayState::Instance()->shop3selected = false;

						isBuying = true;
					}
					else if(theButton[shop2]->isInside(x, y))
					{
						CPlayState::Instance()->shop1selected = false;
						CPlayState::Instance()->shop2selected = true;
						CPlayState::Instance()->shop3selected = false;
					
						isBuying = true;
					}
					else if(theButton[shop3]->isInside(x, y))
					{
						CPlayState::Instance()->shop1selected = false;
						CPlayState::Instance()->shop2selected = false;
						CPlayState::Instance()->shop3selected = true;
					
						isBuying = true;
					}

					else if(!isBuying)
					{
						if(CInputSystem::getInstance()->mouseInfo.mLReclicked == true)
							CInputSystem::getInstance()->mouseInfo.mLClicked = true;
						CInputSystem::getInstance()->mouseInfo.mLReclicked = false;
					}

					else if (isBuying)
					{
						if(theBuyingButton[close]->isInside(x, y))
						{
							CPlayState::Instance()->shop1selected = false;
							CPlayState::Instance()->shop2selected = false;
							CPlayState::Instance()->shop3selected = false;

							isBuying = false;
						}

						if (CPlayState::Instance()->shop1selected || CPlayState::Instance()->shop2selected || CPlayState::Instance()->shop3selected)
						{
							if(theBuyingButton[bpFifty]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 300)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 300);
									CPlayState::Instance()->maskInStock += 50;
									
									if(CPlayState::Instance()->shop1selected)
										CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 50);
									if(CPlayState::Instance()->shop2selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 50);
									if(CPlayState::Instance()->shop3selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 50);
								}
							}
							if(theBuyingButton[bpHundred]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 550)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 550);
									CPlayState::Instance()->maskInStock += 100;

									if(CPlayState::Instance()->shop1selected)
										CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 100);
									if(CPlayState::Instance()->shop2selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 100);
									if(CPlayState::Instance()->shop3selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 100);
								}
							}
							if(theBuyingButton[bpTwohundred]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 1050)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 1050);
									CPlayState::Instance()->maskInStock += 200;

									if(CPlayState::Instance()->shop1selected)
										CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 200);
									if(CPlayState::Instance()->shop2selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 200);
									if(CPlayState::Instance()->shop3selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 200);
								}
							}
						}
					}
					// Render Objects to be selected in the color scheme
					theGrid->Click = true;
				}
			}
			CInputSystem::getInstance()->mouseInfo.clickedX = x;
			CInputSystem::getInstance()->mouseInfo.clickedY = y;

			break;

		case GLUT_RIGHT_BUTTON:
			
			CPlayState::Instance()->shop1selected = false;
			CPlayState::Instance()->shop2selected = false;
			CPlayState::Instance()->shop3selected = false;
			isBuying = false;

			if (state == GLUT_DOWN) {
				CInputSystem::getInstance()->mouseInfo.mRButtonUp = false;
			}
			else{
				CInputSystem::getInstance()->mouseInfo.mRButtonUp = true;
			}

			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CGamePlayState::MouseWheel(int button, int dir, int x, int y) {

	if (dir > 0) {//Zoom In
		if(Camera::getInstance()->camDist > 10)
			Camera::getInstance()->camDist -= 0.9f;
		else
			Camera::getInstance()->camDist = 10;
	}
    else {//Zoom Out
		if(Camera::getInstance()->camDist < Camera::getInstance()->camDist_max)
			Camera::getInstance()->camDist += 0.9f;
		else
			Camera::getInstance()->camDist = Camera::getInstance()->camDist_max;
	}
}

void CGamePlayState::ClickCollision() {

	GLint window_width = glutGet(GLUT_WINDOW_WIDTH);
	GLint window_height = glutGet(GLUT_WINDOW_HEIGHT);

	int x = CInputSystem::getInstance()->mouseInfo.clickedX;
	int y = CInputSystem::getInstance()->mouseInfo.clickedY;

	unsigned char color[3];
 
	glReadPixels(x, window_height - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
 
	float colorf[3];
	colorf[0] = (float)color[0]/255;
	colorf[1] = (float)color[1]/255;
	colorf[2] = (float)color[2]/255;
	
	//For some reason it only checks tiles with a and s that are multiples of 4
	//Check color scheme for tiles

	for (int a = 0; a < TILE_NO_X; ++a)
	{
		for(int s = 0; s < TILE_NO_Y; ++s)
		{
			if(theGrid->temp[a][s].getColor() == Vector3(colorf[0], colorf[1], colorf[2])) {
			
				CStalls* StallSelected = NULL;

				//Check if any stall is selected
				for (int i = 0; i < 3; i++)
				{
					if(CPlayState::Instance()->theStall[i]->Selected)
					{ StallSelected = CPlayState::Instance()->theStall[i]; break; }
				}

				//If clicked on stall
				if(theGrid->temp[a][s].ShopOnTop != NULL)
				{
					if(StallSelected == NULL)
						theGrid->temp[a][s].ShopOnTop->Selected = true;
				}
				else
				{
					//If have stall selected and clicked on acceptable tile
					if(StallSelected != NULL)
					{
						StallSelected->Selected = false;
						for (int k = 0; k < TILE_NO_X; ++k)
						{
							for(int l = 0; l < TILE_NO_Y; ++l)
							{
								if(theGrid->temp[k][l].ShopOnTop == StallSelected)
								{ theGrid->temp[k][l].ShopOnTop = NULL; break; }
							}
						}
						//Set position
						StallSelected->setPos(Vector3(theGrid->temp[a][s].getPos()+theGrid->temp[a][s].GetScale()*0.5));
					}

				}
				break;
			}
		}
	}
}

void CGamePlayState::drawInfo()
{
	glPushMatrix();

		glPushMatrix();
			glEnable(GL_BLEND);
			glColor4f(0, 0, 0, 0.5f);
			glBegin(GL_QUADS);
				glTexCoord2f(1, 0);	glVertex2f(0, SCREEN_HEIGHT / 4);
				glTexCoord2f(0, 0); glVertex2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
				glTexCoord2f(0, 1); glVertex2f(SCREEN_WIDTH / 4, 0);
				glTexCoord2f(1, 1);	glVertex2f(0, 0);
			glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();

		glPushAttrib(GL_DEPTH_TEST);
			glColor3f( 1,1,1);
			printw(20, SCREEN_HEIGHT*0.03, 0, "PSI: %f", CPlayState::Instance()->theHaze.HazeGraph[HourNumber + (CPlayState::Instance()->day-1) * DayTime]);
			printw(20, SCREEN_HEIGHT*0.06, 0, "Day: %d", CPlayState::Instance()->day);
			printw(20, SCREEN_HEIGHT*0.09, 0, "Hour: %d", HourNumber);
			glColor3f(0.4,0.4,1); //B
			printw (20, SCREEN_HEIGHT*0.15, 0,  "Shop 1's no. of masks: %d", CPlayState::Instance()->theStall[0]->getMaskNo());
			glColor3f(1,0.2,0.2); //R
			printw (20, SCREEN_HEIGHT*0.18, 0,  "Shop 2's no. of masks: %d", CPlayState::Instance()->theStall[1]->getMaskNo());
			glColor3f(0.2,1,0.2); //G
			printw (20, SCREEN_HEIGHT*0.21, 0,  "Shop 3's no. of masks: %d", CPlayState::Instance()->theStall[2]->getMaskNo());
		glPopAttrib();
	glPopMatrix();
}

void CGamePlayState::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

//Camera rotate function
void CGamePlayState::OnRotate(int x, int y)
{
	//Under MouseMove(int x, int y)

	int diffX = x - CInputSystem::getInstance()->mouseInfo.lastX;
	int diffY = y - CInputSystem::getInstance()->mouseInfo.lastY;

	//Update on x and z axis
	Camera::getInstance()->angle += (float) diffX*Camera::getInstance()->VEL_X * 3.142f / 180.0f;// * 180.0f / 3.142f;
	if (Camera::getInstance()->angle > 6.284f)
		Camera::getInstance()->angle -= 6.284f;
	else if (Camera::getInstance()->angle < -6.284f)
		Camera::getInstance()->angle += 6.284f;
	//Update on y axis
	if(Camera::getInstance()->GetDir().y - diffY*Camera::getInstance()->VEL_Y < -Camera::getInstance()->MAX_Y)
		Camera::getInstance()->SetDir(Vector3(sin(Camera::getInstance()->angle),-Camera::getInstance()->MAX_Y,-cos(Camera::getInstance()->angle)));
	else if(Camera::getInstance()->GetDir().y - diffY*Camera::getInstance()->VEL_Y > -Camera::getInstance()->MAX_Y/10)
		Camera::getInstance()->SetDir(Vector3(sin(Camera::getInstance()->angle),-Camera::getInstance()->MAX_Y/10,-cos(Camera::getInstance()->angle)));
	else
		Camera::getInstance()->SetDir(Vector3(sin(Camera::getInstance()->angle),Camera::getInstance()->GetDir().y - diffY*Camera::getInstance()->VEL_Y,-cos(Camera::getInstance()->angle)));
}

