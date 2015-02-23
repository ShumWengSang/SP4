#include "GamePlayState.h"
#include "EndOfDayState.h"
#include "PlayState.h"

CGamePlayState CGamePlayState::theGamePlayState;

void CGamePlayState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&map[0],"images/playState/map.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/playState/pause.tga");
}
void CGamePlayState::LoadButtons()
{
	//buttons
	theButton[pause] = new CButtons(SCREEN_WIDTH - 64, 32, 32, 32, pause);
	theButton[pause]->setButtonTexture(button[0].texID);
}

void CGamePlayState::Init()
{
	cout << "CGamePlayState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
	
	//Isometric view
	CApplication::getInstance()->theCamera->SetCameraType(Camera::AIR_CAM);
	CApplication::getInstance()->theCamera->SetPosition(50.0, 50.0, -70.0);
	Vector3 temp = -CApplication::getInstance()->theCamera->GetPosition();
	CApplication::getInstance()->theCamera->SetDirection(temp.Normalized().x, temp.Normalized().y, temp.Normalized().z);

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
	myLoc.renderMap(false);

	//Center
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor3f(1,1,1);
		glTranslatef(0,0,0);
		glutSolidSphere(1,20,20);
		glDisable(GL_BLEND);
	glPopMatrix();

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

	CApplication::getInstance()->theCamera->SetHUD(true);

	DrawButtons();//pause button here

	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CGamePlayState::DrawButtons()
{
	//pause game
	theButton[pause]->drawButton();
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

	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}

//Inputs
void CGamePlayState::MouseMove (int x, int y) {

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);


	//Checking mouse boundary. (Width)
	if  (CInputSystem::getInstance()->mouseInfo.lastX > w-50)
	{
		CInputSystem::getInstance()->mouseInfo.lastX = w-50;
		glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
		CApplication::getInstance()->theCamera->Strafe(1);
	}
	else if  (CInputSystem::getInstance()->mouseInfo.lastX < 50)
	{
		CInputSystem::getInstance()->mouseInfo.lastX = 50;
		glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
		CApplication::getInstance()->theCamera->Strafe(-1);
	}else
	CInputSystem::getInstance()->mouseInfo.lastX = x;

	//Checking mouse boundary. (Height)
	if  (CInputSystem::getInstance()->mouseInfo.lastY > h-50)
	{
		CInputSystem::getInstance()->mouseInfo.lastY = h-50;
		glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
		CApplication::getInstance()->theCamera->Walk(-1);
	}
	else if  (CInputSystem::getInstance()->mouseInfo.lastY < 50)
	{
		CInputSystem::getInstance()->mouseInfo.lastY = 50;
		glutWarpPointer(CInputSystem::getInstance()->mouseInfo.lastX, CInputSystem::getInstance()->mouseInfo.lastY);
		CApplication::getInstance()->theCamera->Walk(1);
	}else
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
 
				GLbyte color[4];
 
				glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
 
				printf("Clicked on pixel %d, %d, color %d%d%d%d\n", x, y, -color[0], -color[1], -color[2], -color[3]);

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
