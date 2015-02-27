#include "GamePlayState.h"
#include "EndOfDayState.h"
#include "PlayState.h"

CGamePlayState CGamePlayState::theGamePlayState;

void CGamePlayState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&map[0],"images/playState/map.tga");
	CApplication::getInstance()->LoadTGA(&button[0], "images/playState/pause.tga");
	CApplication::getInstance()->LoadTGA(&button[1], "images/playState/shop.tga");
	CApplication::getInstance()->LoadTGA(&button[2], "images/playState/shop2.tga");
	CApplication::getInstance()->LoadTGA(&button[3], "images/playState/shop3.tga");
	CApplication::getInstance()->LoadTGA(&button[4],"images/playState/shopSelected.tga");
	CApplication::getInstance()->LoadTGA(&button[5],"images/playState/shop2Selected.tga");
	CApplication::getInstance()->LoadTGA(&button[6],"images/playState/shop3Selected.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[0], "images/playState/SkyBox/skybox_near.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[1], "images/playState/SkyBox/skybox_far.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[2], "images/playState/SkyBox/skybox_left.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[3], "images/playState/SkyBox/skybox_right.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[4], "images/playState/SkyBox/skybox_top.tga");
	CApplication::getInstance()->LoadTGA(&skyBox[5], "images/playState/SkyBox/skybox_bottom.tga");

	

	CApplication::getInstance()->LoadTGA(&buyingButton[0],"images/playState/x.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[1],"images/playState/50.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[2],"images/playState/100.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[3],"images/playState/200.tga");
	CApplication::getInstance()->LoadTGA(&buyingBackground[0],"images/playState/box.tga");
}
void CGamePlayState::LoadButtons()
{
	//buttons
	theButton[pause] = new CButtons(SCREEN_WIDTH/2 - 45, 1, 32, 32, pause);
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
	cout << "CGamePlayState::Init\n" << endl;
	theGrid = new Grid();

	isPause = false;
	isBuying = false;

	LoadTextures();
	LoadButtons();

	barPos.Set(80, 10, 0);

	font_style = GLUT_BITMAP_HELVETICA_18;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;

	CInputSystem::getInstance()->mouseInfo.mLClicked = false;
	CInputSystem::getInstance()->mouseInfo.mLReclicked = true;

	Camera::getInstance()->Reset();

	//Isometric view
	Camera::getInstance()->SetCameraType(Camera::AIR_CAM);	

	CPlayState * PlayState = CPlayState::Instance();

	//for (int i = 0; i < SEEDCOUNT; i++)
	//{
	//	int x = rand() % TILE_NO_X;
	//	int y = rand() % TILE_NO_Y;

	//	theGrid->temp[x][y].Seeded(CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime] * 10000);//CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime]
	//	theSeededTiles.push_back(&theGrid->temp[x][y]);
	//	//for (int m = 0; m < TILE_NO_X; i++)
	//	//{
	//	//	for (int k = 0; k < TILE_SIZE_Y; k++)
	//	//	{
	//	//		for (int j = 0; )
	//	//		theGrid->temp[i][k].TileHazeValue = 0;
	//	//	}
	//	//}

	//	//GET TILE INFO FROM POSITION
	//	//SET THE HAZE
	//}
	theGrid->temp[2][0].Seeded(CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime] * 100000);//CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime]
	theGrid->temp[3][0].Seeded(CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime] * 10000);
	//theGrid->temp[1][2].Seeded(CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime] * 10000);
	//theGrid->temp[3][4].Seeded(CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime] * 10000);

	theTimerInstance = CTimer::getInstance();
	TimerKeySeed = theTimerInstance->insertNewTime(3000);
	TimerKeyDay = theTimerInstance->insertNewTime(270000);
	HourNumber = 0;
	
	Buyer * newBuyer;

	std::vector<CStalls*> theListofStalls;
	for (int i = 0; i < 3; i++)
	{
		theListofStalls.push_back(CPlayState::Instance()->theStall[i]);
	}

	for (int i = 0; i < 1; i++)
	{
		newBuyer = new Buyer(theListofStalls, theGrid);
		theListofEntities.push_back(newBuyer);
	}

	// Stall Initialisation on Tiles
	//theGrid->GetTile(CPlayState::Instance()->theStall[0]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[0];
	//theGrid->GetTile(CPlayState::Instance()->theStall[1]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[1];
	//theGrid->GetTile(CPlayState::Instance()->theStall[2]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[2];


	theListofEntities.push_back(CPlayState::Instance()->theStall[0]);
	theListofEntities.push_back(CPlayState::Instance()->theStall[1]);
	theListofEntities.push_back(CPlayState::Instance()->theStall[2]);
	theListofEntities.push_back(theGrid);

	CPlayState::Instance()->theStall[0]->setColour(Vector3(0,0,1));
	CPlayState::Instance()->theStall[1]->setColour(Vector3(1,0,0));
	CPlayState::Instance()->theStall[2]->setColour(Vector3(0,1,0));
}

void CGamePlayState::Cleanup()
{
	//cout << "CGamePlayState::Cleanup\n" << endl;
	/*if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}*/
}

void CGamePlayState::Pause()
{
	if(isPause == false)
		isPause = true;
}

void CGamePlayState::Resume()
{
	if(isPause == true)
		isPause = false;
}

void CGamePlayState::HandleEvents(CInGameStateManager* theGSM)
{
}

void CGamePlayState::Update(CInGameStateManager* theGSM) 
{
	if(isPause)
		Camera::getInstance()->newUpdate();
	else
	{
		keyboardUpdate();
		Camera::getInstance()->newUpdate();
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			(*i)->Update();
		}

		//if (theTimerInstance->executeTime(TimerKeyDay))
		//{
		//	DayNumber++;
		//	//CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
		//	HourNumber = 0;
		//	theSeededTiles.clear();
		//	for (int i = 0; i < SEEDCOUNT; i++)
		//	{
		//		int x = rand() % TILE_NO_X;
		//		int y = rand() % TILE_NO_Y;

		//		theGrid->temp[x][y].childs[0]->HazeTileValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
		//		theGrid->temp[x][y].TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
		//		theSeededTiles.push_back(&theGrid->temp[x][y]);
		//		//GET TILE INFO FROM POSITION
		//		//SET THE HAZE
		//	}
		//	std::cout << "DAY CHANGE IT IS NOW DAY " << DayNumber << std::endl;
		//}

		if (theTimerInstance->executeTime(TimerKeySeed))
		{
			HourNumber++;
		//	if (!(HourNumber * DayTime >= noiseWidth))
		//	{
		//		for (auto i = theSeededTiles.begin(); i != theSeededTiles.end(); i++)
		//		{
		//			(*i)->TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber + DayNumber * DayTime] * 8;
		//			(*i)->childs[0]->HazeTileValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber + DayNumber * DayTime] * 8;
		//		}
		//	}
		}

		if (theTimerInstance->executeTime(TimerKeyDay))
		{
			DayNumber++;
			CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
		}
	}
}

void CGamePlayState::Draw(CInGameStateManager* theGSM) 
{



	// Render Objects to be selected in the color scheme
	if(CInputSystem::getInstance()->mouseInfo.mLClicked == true)
	{
		theGrid->Click = true;
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			if((*i)->getObjectType() == GRID)
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

		glPushMatrix();
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glTranslatef( -150.0f, -0.1f, -150.0f );
			glScalef(0.5f, 0.5f, 0.5f);
			glColor3f(1.0,1.0,1.0);
			glBindTexture(GL_TEXTURE_2D, map[0].texID);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);  glVertex3f(SCREEN_WIDTH, 0.0f, 0);
				glTexCoord2f(1, 0);  glVertex3f(0, 0.0f, 0);
				glTexCoord2f(1, 1);	 glVertex3f(0, 0.0f, SCREEN_HEIGHT);
				glTexCoord2f(0, 1);	 glVertex3f(SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		glPopMatrix();


		theGrid->Click = false;
		//theGrid.renderGrid(false);
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
	DrawButtons();//pause button here
	drawInfo();
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
				glScalef(0.4, 0.55, 1);
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
				
				//SCREEN_WIDTH - 90, SCREEN_HEIGHT - 310
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 270, 0,  "Current money: $%d", CPlayState::Instance()->theMoney.getCurrentMoney());

				if(CPlayState::Instance()->theStall[0]->Selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 1-", CPlayState::Instance()->theMoney.getCurrentMoney());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[0]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[0]->getMaskPrice());
				}

				if(CPlayState::Instance()->theStall[1]->Selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 2-", CPlayState::Instance()->theMoney.getCurrentMoney());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[1]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[1]->getMaskPrice());
				}

				if(CPlayState::Instance()->theStall[2]->Selected)
				{
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 300, 0,  "Shop 3-", CPlayState::Instance()->theMoney.getCurrentMoney());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 240, 0,  "Current shop's masks: %d", CPlayState::Instance()->theStall[2]->getMaskNo());
					printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 210, 0,  "Current shop's mask price: %d", CPlayState::Instance()->theStall[2]->getMaskPrice());
				}
				
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 140, 0, "Amount of masks to buy");
				printw (SCREEN_WIDTH - 310, SCREEN_HEIGHT - 110, 0, "Price:");
				//10, SCREEN_HEIGHT - 250
				printw (SCREEN_WIDTH - 290, SCREEN_HEIGHT - 80, 0, "$300");
				printw (SCREEN_WIDTH - 200, SCREEN_HEIGHT - 80, 0, "$550");
				printw (SCREEN_WIDTH - 110, SCREEN_HEIGHT - 80, 0, "$1050");
			glPopAttrib();
		glPopMatrix();
	}
}

void CGamePlayState::DrawButtons()
{
	//pause game
	theButton[pause]->drawButton();

	//shop
	theButton[shop]->drawButton();
	if(CPlayState::Instance()->theStall[0]->Selected)
		theButton[shop]->setButtonTexture(button[4].texID);
	else
		theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2]->drawButton();
	if(CPlayState::Instance()->theStall[1]->Selected)
		theButton[shop2]->setButtonTexture(button[5].texID);
	else
		theButton[shop2]->setButtonTexture(button[2].texID);

	theButton[shop3]->drawButton();
	if(CPlayState::Instance()->theStall[2]->Selected)
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
	theTimeBar.init(1.0f, 0.2f, 0.2f, barPos);
	theTimeBar.update(HourNumber);
	theTimeBar.draw();
}

void CGamePlayState::buyMask(int stall, int maskNo) //0 is first stall
{
	CPlayState::Instance()->theStall[stall]->setMaskSold(2);
	CPlayState::Instance()->theStall[stall]->setTotalMaskSold(CPlayState::Instance()->theStall[stall]->getMaskSold());
	CPlayState::Instance()->theStall[stall]->setMaskNo(CPlayState::Instance()->theStall[stall]->getMaskNo() - CPlayState::Instance()->theStall[stall]->getMaskSold());
	cout << "mask sold " << CPlayState::Instance()->theStall[stall]->getMaskSold() << endl;
	cout << "mask in stall: " << CPlayState::Instance()->theStall[stall]->getMaskNo() << endl;
	cout << "total mask sold: " << CPlayState::Instance()->theStall[stall]->getTotalMaskSold() << endl;
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
	if (CInputSystem::getInstance()->myKeys['1'])
	{
		for (int i = 0; i < theSeededTiles.size(); i++)
		{
			std::cout << "TILE SEED NUMBER : " << i << " : " << theSeededTiles[i]->TileHazeValue << std::endl;
		}
	}

	if(CInputSystem::getInstance()->myKeys['z'])
	{
		if(CPlayState::Instance()->theStall[0]->getMaskNo() >= CPlayState::Instance()->theStall[0]->getMaskSold())
		{
			buyMask(0, 2);
			CPlayState::Instance()->earned = CPlayState::Instance()->theStall[0]->getTotalMaskSold() * CPlayState::Instance()->theStall[0]->getMaskPrice();
			cout << CPlayState::Instance()->earned << endl;
		}
		else
			cout << "no mask" << endl;
	}
	if(CInputSystem::getInstance()->myKeys['x'])
	{
		if(CPlayState::Instance()->theStall[1]->getMaskNo() >= CPlayState::Instance()->theStall[1]->getMaskSold())
		{
			buyMask(1, 2);
			CPlayState::Instance()->earned2 = CPlayState::Instance()->theStall[1]->getTotalMaskSold() * CPlayState::Instance()->theStall[1]->getMaskPrice();
			cout << CPlayState::Instance()->earned2 << endl;
		}
		else
			cout << "no mask" << endl;
	}
	if(CInputSystem::getInstance()->myKeys['c'])
	{
		if(CPlayState::Instance()->theStall[2]->getMaskNo() >= CPlayState::Instance()->theStall[2]->getMaskSold())
		{
			buyMask(2, 2);
			CPlayState::Instance()->earned3 = CPlayState::Instance()->theStall[2]->getTotalMaskSold() * CPlayState::Instance()->theStall[2]->getMaskPrice();
			cout << CPlayState::Instance()->earned3 << endl;
		}
		else
			cout << "no mask" << endl;
	}

	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);

	//Camera Locking
	if(Camera::getInstance()->GetPos().x <= theGrid->getX())
	{Camera::getInstance()->SetPos(Vector3(theGrid->getX(),Camera::getInstance()->GetPos().y,Camera::getInstance()->GetPos().z));}
	else if(Camera::getInstance()->GetPos().x >= theGrid->getX() + TILE_SIZE_X*TILE_NO_X)
	{Camera::getInstance()->SetPos(Vector3(theGrid->getX() + TILE_SIZE_X*TILE_NO_X,Camera::getInstance()->GetPos().y,Camera::getInstance()->GetPos().z));}
	if(Camera::getInstance()->GetPos().z <= theGrid->getY())
	{Camera::getInstance()->SetPos(Vector3(Camera::getInstance()->GetPos().x,Camera::getInstance()->GetPos().y,theGrid->getY()));}
	else if(Camera::getInstance()->GetPos().z >= theGrid->getY() + TILE_SIZE_Y*TILE_NO_Y)
	{Camera::getInstance()->SetPos(Vector3(Camera::getInstance()->GetPos().x,Camera::getInstance()->GetPos().y,theGrid->getY() + TILE_SIZE_Y*TILE_NO_Y));}
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
				//CApplication::getInstance()->setClickCheck(false);
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
					//CApplication::getInstance()->setClickCheck(true);
					CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
					if(CInputSystem::getInstance()->mouseInfo.mLReclicked == true)
						CInputSystem::getInstance()->mouseInfo.mLClicked = true;
					CInputSystem::getInstance()->mouseInfo.mLReclicked = false;

					//shop 1 clicked
					if(theButton[shop]->isInside(x, y))
					{
						CPlayState::Instance()->theStall[0]->Selected = true;
						CPlayState::Instance()->theStall[1]->Selected = false;
						CPlayState::Instance()->theStall[2]->Selected = false;

						isBuying = true;
					}
					if(theButton[shop2]->isInside(x, y))
					{
						CPlayState::Instance()->theStall[0]->Selected = false;
						CPlayState::Instance()->theStall[1]->Selected = true;
						CPlayState::Instance()->theStall[2]->Selected = false;
					
						isBuying = true;
					}
					if(theButton[shop3]->isInside(x, y))
					{
						CPlayState::Instance()->theStall[0]->Selected = false;
						CPlayState::Instance()->theStall[1]->Selected = false;
						CPlayState::Instance()->theStall[2]->Selected = true;
					
						isBuying = true;
					}

					if (isBuying == true)
					{
						if(theBuyingButton[close]->isInside(x, y))
						{
							CPlayState::Instance()->theStall[0]->Selected = false;
							CPlayState::Instance()->theStall[1]->Selected = false;
							CPlayState::Instance()->theStall[2]->Selected = false;

							isBuying = false;
						}

						if (CPlayState::Instance()->theStall[0]->Selected ||
							CPlayState::Instance()->theStall[1]->Selected ||
							CPlayState::Instance()->theStall[2]->Selected)
						{

							if(theBuyingButton[bpFifty]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 300)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 300);

									if(CPlayState::Instance()->theStall[0]->Selected)
										CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 50);
									if(CPlayState::Instance()->theStall[1]->Selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 50);
									if(CPlayState::Instance()->theStall[2]->Selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 50);
								}

							}
							if(theBuyingButton[bpHundred]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 550)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 550);

									if(CPlayState::Instance()->theStall[0]->Selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 100);
									if(CPlayState::Instance()->theStall[1]->Selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 100);
									if(CPlayState::Instance()->theStall[2]->Selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 100);
								}
							}
							if(theBuyingButton[bpTwohundred]->isInside(x, y))
							{
								if(CPlayState::Instance()->theMoney.getCurrentMoney() >= 1050)
								{
									CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 1050);

									if(CPlayState::Instance()->theStall[0]->Selected)
										CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 200);
									if(CPlayState::Instance()->theStall[1]->Selected)
										CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 200);
									if(CPlayState::Instance()->theStall[2]->Selected)
										CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 200);
								}
							}
						}
					}
					// Render Objects to be selected in the color scheme
					theGrid->Click = true;
					//theGrid.renderGrid(true);
				}
			}
			CInputSystem::getInstance()->mouseInfo.clickedX = x;
			CInputSystem::getInstance()->mouseInfo.clickedY = y;

			break;

		case GLUT_RIGHT_BUTTON:

			CPlayState::Instance()->theStall[0]->Selected = false;
			CPlayState::Instance()->theStall[1]->Selected = false;
			CPlayState::Instance()->theStall[2]->Selected = false;
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
					//printf("Confirmed shop clicked %d %d\n\n", a, s);
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
						//theGrid->GetTile(StallSelected->getPosition())->ShopOnTop = StallSelected;
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
		glPushAttrib(GL_DEPTH_TEST);
			glColor3f( 1.0f, 0.0f, 0.0f);
			printw (20, 20, 0,  "Time: ");
			printw (20, 45, 0, "PSI: 123");
			printw(20, 65, 0, "FPS: %f", theTimerInstance->getFPS());
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

