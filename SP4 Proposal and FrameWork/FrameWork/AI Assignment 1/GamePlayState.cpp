#include "GamePlayState.h"
#include "EndOfDayState.h"
#include "PlayState.h"

CGamePlayState CGamePlayState::theGamePlayState;

void CGamePlayState::Init()
{
	cout << "CGamePlayState::Init\n" << endl;

	//Textures
	//buttons
	CApplication::getInstance()->LoadTGA(&button[0],"images/playState/pause.tga");
	theButton[pause] = new CButtons(SCREEN_WIDTH - 64, 0, 64, 64, pause);
	theButton[pause]->setButtonTexture(button[0].texID);

	theStall[0] = new CStalls();

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
		Vector3 theSeedLocation(rand() % TILE_NO_X, 0, rand() % TILE_NO_Y);
		//GET TILE INFO FROM POSITION
		//SET THE HAZE
	}



	PlayState->theHaze;
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
	//cout << "CGamePlayState::Pause\n" << endl;
}

void CGamePlayState::Resume()
{
	//cout << "CGamePlayState::Resume\n" << endl;
}

void CGamePlayState::HandleEvents(CInGameStateManager* theGSM)
{
}

void CGamePlayState::Update(CInGameStateManager* theGSM) 
{
	//cout << "CGamePlayState::Update\n" << endl;
	keyboardUpdate();

}

void CGamePlayState::Draw(CInGameStateManager* theGSM) 
{

	//CApplication::getInstance()->theCamera->SetHUD(true);

	//DrawButtons();//pause button here

	//CApplication::getInstance()->theCamera->SetHUD(false);

	myLoc.renderGrid(false);

}

void CGamePlayState::DrawButtons()
{
	//pause game
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[pause]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[pause]->getButtonX(), theButton[pause]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[pause]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[pause]->getWidth(), theButton[pause]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[pause]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
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

	if(CInputSystem::getInstance()->myKeys['b'])
	{
		theMoney.setMoneyIncrease(10);
		cout << theMoney.getCurrentMoney() << endl;
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

				// Render Objects to be selected in the color scheme

				GLint window_width = glutGet(GLUT_WINDOW_WIDTH);
				GLint window_height = glutGet(GLUT_WINDOW_HEIGHT);
 
				unsigned char color[3];
 
				glReadPixels(x, window_height - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
 
				float colorf[3];
				colorf[0] = (float)color[0]/255;
				colorf[1] = (float)color[1]/255;
				colorf[2] = (float)color[2]/255;

				printf("Clicked on pixel %d, %d, color %0.2f %0.2f %0.2f\n", x, y, colorf[0], colorf[1], colorf[2]);

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
