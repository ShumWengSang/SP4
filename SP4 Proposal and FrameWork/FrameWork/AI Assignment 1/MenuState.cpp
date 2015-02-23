#include "MenuState.h"
#include "PlayState.h"

CMenuState CMenuState::theMenuState;

void CMenuState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/menuState/start.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/menuState/loadGame.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/menuState/options.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/menuState/quit.tga");
}
void CMenuState::LoadButtons()
{
	//buttons
	theButton[start] = new CButtons(SCREEN_WIDTH/2 - 100, 100, 200, 100, start);
	theButton[start]->setButtonTexture(button[0].texID);
	
	theButton[loadGame] = new CButtons(SCREEN_WIDTH/2 - 100, 200, 200, 100, loadGame);
	theButton[loadGame]->setButtonTexture(button[1].texID);
	
	theButton[options] = new CButtons(SCREEN_WIDTH/2 - 100, 300, 200, 100, options);
	theButton[options]->setButtonTexture(button[2].texID);
	
	theButton[quit] = new CButtons(SCREEN_WIDTH/2 - 100, 400, 200, 100, quit);
	theButton[quit]->setButtonTexture(button[3].texID);
}

void CMenuState::Init()
{
	cout << "CMenuState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Audio Player
	se = createIrrKlangDevice();
	playSound();

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
	theButton[start]->drawButton();
	theButton[loadGame]->drawButton();
	theButton[options]->drawButton();
	theButton[quit]->drawButton();
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

//Inputs
void CMenuState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	switch (button) {
		case GLUT_LEFT_BUTTON:
			se->play2D("audio/click.wav",false);
			if (state == 0)
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//go to start of the day
				if(theButton[start]->isInside(x, y))
					CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());

				//quit game
				if(theButton[quit]->isInside(x, y))
					exit(0);
			}
			else
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
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


void CMenuState::playSound()
{
	sound.setFileName("audio/Sims.mp3");
	sound.playSoundThreaded();
}

