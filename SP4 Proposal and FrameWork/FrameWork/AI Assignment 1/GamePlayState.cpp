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

	

	CApplication::getInstance()->LoadTGA(&buyingButton[0],"images/startState/back.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[1],"images/playState/50.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[2],"images/playState/100.tga");
	CApplication::getInstance()->LoadTGA(&buyingButton[3],"images/playState/200.tga");
	CApplication::getInstance()->LoadTGA(&buyingBackground[0],"images/playState/box.tga");
}
void CGamePlayState::LoadButtons()
{
	//buttons
	theButton[pause] = new CButtons(SCREEN_WIDTH - 50, 1, 48, 48, pause);
	theButton[pause]->setButtonTexture(button[0].texID);

	theButton[shop] = new CButtons(0, SCREEN_HEIGHT - 50, 70, 50, shop);
	theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2] = new CButtons(80, SCREEN_HEIGHT - 50, 70, 50, shop2);
	theButton[shop2]->setButtonTexture(button[2].texID);

	theButton[shop3] = new CButtons(160, SCREEN_HEIGHT - 50, 70, 50, shop3);
	theButton[shop3]->setButtonTexture(button[3].texID);



	theBuyingButton[close] = new CButtons(240, SCREEN_HEIGHT - 390, 70, 50, close);
	theBuyingButton[close]->setButtonTexture(buyingButton[0].texID);

	theBuyingButton[bpFifty] = new CButtons(10, SCREEN_HEIGHT - 250, 70, 50, bpFifty);
	theBuyingButton[bpFifty]->setButtonTexture(buyingButton[1].texID);
	
	theBuyingButton[bpHundred] = new CButtons(90, SCREEN_HEIGHT - 130, 70, 50, bpHundred);
	theBuyingButton[bpHundred]->setButtonTexture(buyingButton[2].texID);
	
	theBuyingButton[bpTwohundred] = new CButtons(170, SCREEN_HEIGHT - 130, 70, 50, bpTwohundred);
	theBuyingButton[bpTwohundred]->setButtonTexture(buyingButton[3].texID);
}

void CGamePlayState::Init()
{
	cout << "CGamePlayState::Init\n" << endl;
	theGrid = new Grid();

	isPause = false;
	shop1Selected = false;
	shop2Selected = false;
	shop3Selected = false;

	
	isBuying = false;


	LoadTextures();
	LoadButtons();

	font_style = GLUT_BITMAP_HELVETICA_18;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
	
	//Isometric view
	CApplication::getInstance()->theCamera->SetCameraType(Camera::AIR_CAM);
	CApplication::getInstance()->theCamera->SetPosition(50.0, 50.0, -70.0);
	Vector3 temp = -CApplication::getInstance()->theCamera->GetPosition();
	CApplication::getInstance()->theCamera->SetDirection(temp.Normalized().x, temp.Normalized().y, temp.Normalized().z);

	CPlayState * PlayState = CPlayState::Instance();

	for (int i = 0; i < SEEDCOUNT; i++)
	{
		int x = rand() % TILE_NO_X;
		int y = rand() % TILE_NO_Y;

		theGrid->temp[x][y].childs[0]->HazeTileValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
		theGrid->temp[x][y].TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
		theSeededTiles.push_back(&theGrid->temp[x][y]);
		//for (int m = 0; m < TILE_NO_X; i++)
		//{
		//	for (int k = 0; k < TILE_SIZE_Y; k++)
		//	{
		//		for (int j = 0; )
		//		theGrid->temp[i][k].TileHazeValue = 0;
		//	}
		//}

		//GET TILE INFO FROM POSITION
		//SET THE HAZE
	}

	theTimerInstance = CTimer::getInstance();
	TimerKeySeed = theTimerInstance->insertNewTime(3000);
	TimerKeyDay = theTimerInstance->insertNewTime(27000);
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
	if(!isPause)
		keyboardUpdate();
	else{}

	for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
	{
		(*i)->Update();
	}


	if (theTimerInstance->executeTime(TimerKeyDay))
	{
		DayNumber++;
		//CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
		HourNumber = 0;
		theSeededTiles.clear();
		for (int i = 0; i < SEEDCOUNT; i++)
		{
			int x = rand() % TILE_NO_X;
			int y = rand() % TILE_NO_Y;

			theGrid->temp[x][y].childs[0]->HazeTileValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
			theGrid->temp[x][y].TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
			theSeededTiles.push_back(&theGrid->temp[x][y]);
			//GET TILE INFO FROM POSITION
			//SET THE HAZE
		}
		std::cout << "DAY CHANGE IT IS NOW DAY " << DayNumber << std::endl;
	}

	if (theTimerInstance->executeTime(TimerKeySeed))
	{
		HourNumber++;
		if (!(HourNumber * DayTime >= noiseWidth))
		{
			for (auto i = theSeededTiles.begin(); i != theSeededTiles.end(); i++)
			{
				(*i)->TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber + DayNumber * DayTime] * 8;
				(*i)->childs[0]->HazeTileValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber + DayNumber * DayTime] * 8;
			}
		}
	}

	if (theTimerInstance->executeTime(TimerKeyDay))
	{
		DayNumber++;
		CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
	}

}

void CGamePlayState::Draw(CInGameStateManager* theGSM) 
{
	// Render Objects to be selected in the color scheme
	if(CInputSystem::getInstance()->mouseInfo.mLButtonUp == false)
	{
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			if((*i)->getObjectType() == EntityType::GRID)
				(*i)->glRenderObject();
		}
		CApplication::getInstance()->setClickCheck(true);
		theGrid->Click = true;
		ClickCollision();

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


		//theGrid.renderGrid(false);
		for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
		{
			(*i)->glRenderObject();
		}
		theGrid->GetTile(CPlayState::Instance()->theStall[0]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[0];
		theGrid->GetTile(CPlayState::Instance()->theStall[1]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[1];
		theGrid->GetTile(CPlayState::Instance()->theStall[2]->getPosition())->ShopOnTop = CPlayState::Instance()->theStall[2];
		CApplication::getInstance()->setClickCheck(false);
		theGrid->Click = false;
	}

	CApplication::getInstance()->theCamera->SetHUD(true);

	DrawButtons();//pause button here
	drawInfo();

	DrawBuying();

	CApplication::getInstance()->theCamera->SetHUD(false);
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
				glTranslatef(0, SCREEN_HEIGHT - 400, 2);
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
				printw (10, SCREEN_HEIGHT - 370, 0,  "Current amount of money: ");
				printw (10, SCREEN_HEIGHT - 350, 0,  "Current amount of masks: ");
				
				printw (10, SCREEN_HEIGHT - 180, 0, "Amount of masks to buy");
				printw (10, SCREEN_HEIGHT - 160, 0, "Price:");
				printw (10, SCREEN_HEIGHT - 140, 0, "$X dollars");
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
	if(shop1Selected)
		theButton[shop]->setButtonTexture(button[4].texID);
	else
		theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2]->drawButton();
	if(shop2Selected)
		theButton[shop2]->setButtonTexture(button[5].texID);
	else
		theButton[shop2]->setButtonTexture(button[2].texID);

	theButton[shop3]->drawButton();
	if(shop3Selected)
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
	if(CInputSystem::getInstance()->myKeys['d'])
		CInGameStateManager::getInstance()->ChangeState(CEndOfDayState::Instance());
	if(CInputSystem::getInstance()->myKeys['w']) {
		cout << "\t" << CApplication::getInstance()->theCamera->GetDirection().x << "\t" << CApplication::getInstance()->theCamera->GetDirection().y << "\t" << CApplication::getInstance()->theCamera->GetDirection().z << endl << endl;
		cout << "\t" << CApplication::getInstance()->theCamera->GetPosition().x << "\t" << CApplication::getInstance()->theCamera->GetPosition().y << "\t" << CApplication::getInstance()->theCamera->GetPosition().z << endl << endl;
	}
	if(CInputSystem::getInstance()->myKeys['j'])
		CApplication::getInstance()->theCamera->Strafe(-1);
	if(CInputSystem::getInstance()->myKeys['l'])
		CApplication::getInstance()->theCamera->Strafe(1);
	if(CInputSystem::getInstance()->myKeys['i'])
		CApplication::getInstance()->theCamera->Walk(1);
	if(CInputSystem::getInstance()->myKeys['k'])
		CApplication::getInstance()->theCamera->Walk(-1);
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
}

//Inputs
void CGamePlayState::MouseMove (int x, int y) {

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);


	//Checking mouse boundary. (Width)
	//if  (CInputSystem::getInstance()->mouseInfo.lastX > w-50)
	//{
	//	CInputSystem::getInstance()->mouseInfo.lastX = w-50;
	//	glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
	//	CApplication::getInstance()->theCamera->Strafe(1);
	//}
	//else if  (CInputSystem::getInstance()->mouseInfo.lastX < 50)
	//{
	//	CInputSystem::getInstance()->mouseInfo.lastX = 50;
	//	glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
	//	CApplication::getInstance()->theCamera->Strafe(-1);
	//}else
	//CInputSystem::getInstance()->mouseInfo.lastX = x;

	////Checking mouse boundary. (Height)
	//if  (CInputSystem::getInstance()->mouseInfo.lastY > h-50)
	//{
	//	CInputSystem::getInstance()->mouseInfo.lastY = h-50;
	//	glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
	//	CApplication::getInstance()->theCamera->Walk(-1);
	//}
	//else if  (CInputSystem::getInstance()->mouseInfo.lastY < 50)
	//{
	//	CInputSystem::getInstance()->mouseInfo.lastY = 50;
	//	glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
	//	CApplication::getInstance()->theCamera->Walk(1);
	//}else
	//CInputSystem::getInstance()->mouseInfo.lastY = y;
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CGamePlayState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_UP) {
				//CApplication::getInstance()->setClickCheck(false);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
			}
			else {
				//CApplication::getInstance()->setClickCheck(true);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;

				
				if(theButton[pause]->isInside(x, y) && isPause == false)
				{
					Pause();
				}
				else if(theButton[pause]->isInside(x, y) && isPause == true)
				{
					Resume();
				}

				//shop 1 clicked
				if(theButton[shop]->isInside(x, y))
				{
					shop1Selected = true;
					shop2Selected = false;
					shop3Selected = false;

					isBuying = true;
				}
				if(theButton[shop2]->isInside(x, y))
				{
					shop1Selected = false;
					shop2Selected = true;
					shop3Selected = false;
					
					isBuying = true;
				}
				if(theButton[shop3]->isInside(x, y))
				{
					shop1Selected = false;
					shop2Selected = false;
					shop3Selected = true;
					
					isBuying = true;
				}

				if (isBuying == true)
				{
					if(theBuyingButton[close]->isInside(x, y))
					{
						CPlayState::Instance()->oldMaskValue = CPlayState::Instance()->maskInStock;
						isBuying = false;
					}

					if(theBuyingButton[bpFifty]->isInside(x, y))
					{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 250);

						if(shop1Selected)
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 50);
						if(shop2Selected)
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 50);
						if(shop3Selected)
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 50);
					}
					if(theBuyingButton[bpHundred]->isInside(x, y))
					{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 450);

						if(shop1Selected)
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 100);
						if(shop2Selected)
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 100);
						if(shop3Selected)
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 100);
					}
					if(theBuyingButton[bpTwohundred]->isInside(x, y))
					{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 850);

						if(shop1Selected)
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 200);
						if(shop2Selected)
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 200);
						if(shop3Selected)
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 200);
					}
				}
				// Render Objects to be selected in the color scheme
				theGrid->Click = true;
				//theGrid.renderGrid(true);


				/*GLint window_width = glutGet(GLUT_WINDOW_WIDTH);
				GLint window_height = glutGet(GLUT_WINDOW_HEIGHT);
 
				unsigned char color[3];
 
				glReadPixels(x, window_height - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
 
				float colorf[3];
				colorf[0] = (float)color[0]/255;
				colorf[1] = (float)color[1]/255;
				colorf[2] = (float)color[2]/255;

				printf("Clicked on pixel %d, %d, color %0.2f %0.2f %0.2f\n", x, y, colorf[0], colorf[1], colorf[2]);

				//Check color scheme for grids
				int a = 0;
				int s = 0;
				int maxa = TILE_NO_X;
				int maxs = TILE_NO_Y;
				while(a == maxa) {
					if(s == maxs) {
						s = 0;
						a++;
					}

					if(theGrid->temp[a][s].getColor() == Vector3(colorf[0], colorf[1], colorf[2]))
						printf("Confirmed grid clicked %0.2f %0.2f %0.2f\n\n", colorf[0], colorf[1], colorf[2]);
						
					s++;
				}*/

			}
			CInputSystem::getInstance()->mouseInfo.clickedX = x;
			CInputSystem::getInstance()->mouseInfo.clickedY = y;

			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CGamePlayState::MouseWheel(int button, int dir, int x, int y) {

	if (dir > 0) {//Zoom In
		/*if(camDist-zoomSpeed*15 > 0)
			camDist -= zoomSpeed;*/
		Vector3 temp = CApplication::getInstance()->theCamera->GetPosition() + CApplication::getInstance()->theCamera->GetDirection();
		CApplication::getInstance()->theCamera->SetPosition(temp.x,temp.y,temp.z);
	}
    else {//Zoom Out
		//camDist += zoomSpeed;
		Vector3 temp = CApplication::getInstance()->theCamera->GetPosition() - CApplication::getInstance()->theCamera->GetDirection();
		CApplication::getInstance()->theCamera->SetPosition(temp.x,temp.y,temp.z);
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
				printf("Confirmed grid clicked %d %d\n\n", a, s);
			
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
					printf("Confirmed shop clicked %d %d\n\n", a, s);
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
			//print shop number
			glColor3f( 1.0f, 0.0f, 0.0f);
			printw (SCREEN_WIDTH - 100, 96, 0, "PSI: 123");
			printw (SCREEN_WIDTH - 100, 160, 0,  "Time: ");
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

