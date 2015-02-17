#include "MenuState.h"
#include "PlayState.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	cout << "CMenuState::Init\n" << endl;

	//Textures
	//background
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");

	//buttons
	CApplication::getInstance()->LoadTGA(&button[0],"images/menuState/start.tga");
	theButton[start] = new CButtons(SCREEN_WIDTH/2, 100, 200, 100, start);
	theButton[start]->setButtonTexture(button[0].texID);

	CApplication::getInstance()->LoadTGA(&button[1],"images/menuState/loadGame.tga");
	theButton[loadGame] = new CButtons(SCREEN_WIDTH/2, 200, 200, 100, loadGame);
	theButton[loadGame]->setButtonTexture(button[1].texID);

	CApplication::getInstance()->LoadTGA(&button[2],"images/menuState/options.tga");
	theButton[options] = new CButtons(SCREEN_WIDTH/2, 300, 200, 100, options);
	theButton[options]->setButtonTexture(button[2].texID);

	CApplication::getInstance()->LoadTGA(&button[3],"images/menuState/quit.tga");
	theButton[quit] = new CButtons(SCREEN_WIDTH/2, 400, 200, 100, quit);
	theButton[quit]->setButtonTexture(button[3].texID);

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;

}

void CMenuState::Cleanup()
{
	//cout << "CMenuState::Cleanup\n" << endl;
	if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}
}

void CMenuState::Pause()
{
	//cout << "CMenuState::Pause\n" << endl;
}

void CMenuState::Resume()
{
	//cout << "CMenuState::Resume\n" << endl;
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{

}

void CMenuState::Update(CGameStateManager* theGSM) 
{
	//cout << "CMenuState::Update\n" << endl;
	keyboardUpdate();
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	CApplication::getInstance()->theCamera->SetHUD(true);

	DrawBackground();
	DrawButtons();

	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CMenuState::DrawButtons()
{
	//start game
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[start]->getButton());
		glColor3f(1, 1, 1);
		glTranslatef(theButton[start]->getButtonX(), theButton[start]->getButtonY(), 0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, theButton[start]->getHeight());
				glTexCoord2f(1, 0);	glVertex2f(theButton[start]->getWidth(), theButton[start]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[start]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//load game
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[loadGame]->getButton());
		glColor3f(1, 1, 1);
		glTranslatef(theButton[loadGame]->getButtonX(), theButton[loadGame]->getButtonY(), 0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, theButton[loadGame]->getHeight());
				glTexCoord2f(1, 0);	glVertex2f(theButton[loadGame]->getWidth(), theButton[loadGame]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[loadGame]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
	//optins
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[options]->getButton());
		glColor3f(1, 1, 1);
		glTranslatef(theButton[options]->getButtonX(), theButton[options]->getButtonY(), 0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, theButton[options]->getHeight());
				glTexCoord2f(1, 0);	glVertex2f(theButton[options]->getWidth(), theButton[options]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[options]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
	//quit
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[quit]->getButton());
		glColor3f(1, 1, 1);
		glTranslatef(theButton[quit]->getButtonX(), theButton[quit]->getButtonY(), 0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, theButton[quit]->getHeight());
				glTexCoord2f(1, 0);	glVertex2f(theButton[quit]->getWidth(), theButton[quit]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[quit]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);		
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CMenuState::DrawBackground()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[0].texID);
		glPushMatrix();
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
}

void CMenuState::keyboardUpdate()
{
	if(InputSystem->myKeys['a'])
		CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());

	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
}

void CMenuState::mouseClick()
{
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	//if(InputSystem->isClick)
}

//Inputs
void CMenuState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == 0) 
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
			else
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
			CInputSystem::getInstance()->mouseInfo.clickedX = x;
			CInputSystem::getInstance()->mouseInfo.clickedY = y;

			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CMenuState::MouseWheel(int button, int dir, int x, int y) {

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

