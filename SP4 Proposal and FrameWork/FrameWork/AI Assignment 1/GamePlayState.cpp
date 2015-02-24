#include "GamePlayState.h"
#include "EndOfDayState.h"
#include "PlayState.h"

CGamePlayState CGamePlayState::theGamePlayState;

void CGamePlayState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&map[0],"images/playState/map.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/playState/pause.tga");
	CApplication::getInstance()->LoadTGA(&button[1], "images/playState/shop.tga");
}
void CGamePlayState::LoadButtons()
{
	//buttons
	theButton[pause] = new CButtons(SCREEN_WIDTH - 50, 32, 32, 32, pause);
	theButton[pause]->setButtonTexture(button[0].texID);

	theButton[shop] = new CButtons(0, SCREEN_HEIGHT - 50, 70, 50, shop);
	theButton[shop]->setButtonTexture(button[1].texID);

	theButton[shop2] = new CButtons(80, SCREEN_HEIGHT - 50, 70, 50, shop2);
	theButton[shop2]->setButtonTexture(button[1].texID);

	theButton[shop3] = new CButtons(160, SCREEN_HEIGHT - 50, 70, 50, shop3);
	theButton[shop3]->setButtonTexture(button[1].texID);
}

void CGamePlayState::Init()
{
	cout << "CGamePlayState::Init\n" << endl;

	isPause = false;
	shopSelected = false;
	shop2Selected = false;
	shop3Selected = false;

	LoadTextures();
	LoadButtons();

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

		theGrid.temp[x][y].TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[DayNumber * DayTime];
		theSeededTiles.push_back(&theGrid.temp[x][y]);
		//GET TILE INFO FROM POSITION
		//SET THE HAZE
	}

	theTimerInstance = CTimer::getInstance();
	TimerKeySeed = theTimerInstance->insertNewTime(3000);
	TimerKeyDay = theTimerInstance->insertNewTime(27000);
	HourNumber = 0;

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

	if (theTimerInstance->executeTime(TimerKeySeed))
	{
		HourNumber++;
		for (auto i = theSeededTiles.begin(); i != theSeededTiles.end(); i++)
		{
			(*i)->TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber * DayTime];
		}
	}

	if (theTimerInstance->executeTime(TimerKeySeed))
	{
		HourNumber++;
		for (auto i = theSeededTiles.begin(); i != theSeededTiles.end(); i++)
		{
			(*i)->TileHazeValue = CPlayState::Instance()->theHaze.HazeGraph[HourNumber * DayTime];
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

	for (auto i = theListofEntities.begin(); i != theListofEntities.end(); i++)
	{
		(*i)->glRenderObject();
	}

	glPushMatrix();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glTranslatef( -150.0f, -0.1f, -250.0f );
		glScalef(1.3f, 1.3f, 1.3f);
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

	theGrid.renderGrid(false);

	CApplication::getInstance()->theCamera->SetHUD(true);

	DrawButtons();//pause button here

	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CGamePlayState::DrawButtons()
{
	//pause game
	theButton[pause]->drawButton();

	//shop
	theButton[shop]->drawButton();
	theButton[shop2]->drawButton();
	theButton[shop3]->drawButton();
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

	if(CInputSystem::getInstance()->myKeys['z'])
	{
		if(CPlayState::Instance()->theStall[0]->getMaskNo() >= CPlayState::Instance()->theStall[0]->getMaskSold())
		{
			CPlayState::Instance()->theStall[0]->setMaskSold(2);
			CPlayState::Instance()->theStall[0]->setTotalMaskSold(CPlayState::Instance()->theStall[0]->getMaskSold());
			CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() - CPlayState::Instance()->theStall[0]->getMaskSold());
			cout << "1. mask sold " << CPlayState::Instance()->theStall[0]->getMaskSold() << endl;
			cout << "mask in stall: " << CPlayState::Instance()->theStall[0]->getMaskNo() << endl;
			cout << "total mask sold: " << CPlayState::Instance()->theStall[0]->getTotalMaskSold() << endl;
		}
		else
			cout << "no mask" << endl;
	}
	if(CInputSystem::getInstance()->myKeys['x'])
	{
		if(CPlayState::Instance()->theStall[1]->getMaskNo() > 0)
		{
			CPlayState::Instance()->theStall[1]->setMaskSold(2);
			CPlayState::Instance()->theStall[1]->setTotalMaskSold(CPlayState::Instance()->theStall[1]->getMaskSold());
			CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() - CPlayState::Instance()->theStall[1]->getMaskSold());
			cout << "2. mask sold: " << CPlayState::Instance()->theStall[1]->getMaskSold() << endl;
			cout << "mask in stall: " << CPlayState::Instance()->theStall[1]->getMaskNo() << endl;
			cout << "total mask sold: " << CPlayState::Instance()->theStall[1]->getTotalMaskSold() << endl;
		}
	}
	if(CInputSystem::getInstance()->myKeys['c'])
	{
		if(CPlayState::Instance()->theStall[2]->getMaskNo() > 0)
		{
			CPlayState::Instance()->theStall[2]->setMaskSold(2);
			CPlayState::Instance()->theStall[2]->setTotalMaskSold(CPlayState::Instance()->theStall[2]->getMaskSold());
			CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() - CPlayState::Instance()->theStall[2]->getMaskSold());
			cout << "3. mask sold: " << CPlayState::Instance()->theStall[2]->getMaskSold() << endl;
			cout << "mask in stall: " << CPlayState::Instance()->theStall[2]->getMaskNo() << endl;
			cout << "total mask sold: " << CPlayState::Instance()->theStall[2]->getTotalMaskSold() << endl;
		}
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
			if (state == GLUT_UP) 
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
			else {
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;

				
				if(theButton[pause]->isInside(x, y) && isPause == false)
				{
					Pause();
					cout << "pppp" << endl;
				}
				else if(theButton[pause]->isInside(x, y) && isPause == true)
				{
					Resume();
				}

				//shop 1 clicked
				if(theButton[shop]->isInside(x, y))
				{
					shopSelected = true;
					cout << "ssss" << endl;
				}
				else
					shopSelected = false;

				// Render Objects to be selected in the color scheme
				theGrid.renderGrid(true);

				GLint window_width = glutGet(GLUT_WINDOW_WIDTH);
				GLint window_height = glutGet(GLUT_WINDOW_HEIGHT);
 
				unsigned char color[3];
 
				glReadPixels(x, window_height - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
 
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

					if(theGrid.temp[a][s].getColor() == Vector3(colorf[0], colorf[1], colorf[2]))
						printf("Confirmed grid clicked %0.2f %0.2f %0.2f\n\n", colorf[0], colorf[1], colorf[2]);
						
					s++;
				}

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
