#include "MenuState.h"
#include "PlayState.h"
#include "LoadState.h"

CMenuState CMenuState::theMenuState;

void CMenuState::LoadTextures()
{
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&map[0],"images/menuState/map.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/menuState/start.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/menuState/loadGame.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/menuState/options.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/menuState/quit.tga");
}
void CMenuState::LoadButtons()
{
	//buttons
	theButton[start] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 400, 300, 80, start);
	theButton[start]->setButtonTexture(button[0].texID);
	
	theButton[loadGame] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 300, 300, 80, loadGame);
	theButton[loadGame]->setButtonTexture(button[1].texID);
	
	theButton[options] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 200, 300, 80, options);
	theButton[options]->setButtonTexture(button[2].texID);
	
	theButton[quit] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 100, 300, 80, quit);
	theButton[quit]->setButtonTexture(button[3].texID);
}

void CMenuState::Init()
{
	cout << "CMenuState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	isPassed = false;
	skip = false;

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Audio Player
	se = createIrrKlangDevice();

	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;
	sound = AudioPlayer::Instance();
	playSound();
}

void CMenuState::Cleanup()
{
	//cout << "CMenuState::Cleanup\n" << endl;
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
	keyboardUpdate();
	Camera::getInstance()->newUpdate();
	checkCameraPos();
	if(isPassed)
		Camera::getInstance()->Walk(0);
	else
		Camera::getInstance()->Walk(1);
}

void CMenuState::checkCameraPos()
{
	Vector3 pos;
	pos.Set(0, -50, 320);
	if(skip)
		Camera::getInstance()->SetPos(Vector3(0, -50, 320));
	if(Camera::getInstance()->GetPos() == pos)
	{
		isPassed = true;
	}
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	drawMap();

	if(isPassed || skip)
	{
		Camera::getInstance()->SetHUD(true);
		DrawBackground();
		DrawButtons();
		Camera::getInstance()->SetHUD(false);
	}
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

void CMenuState::drawMap()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(0.5f, 0.5f, 1);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(-210, -300, -260);
		glBindTexture(GL_TEXTURE_2D, map[0].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1);  glVertex3f(0, 0.0f, 420);
			glTexCoord2f(0, 1);  glVertex3f(420, 0.0f, 420); 
			glTexCoord2f(0, 0);	 glVertex3f(420, 0.0f, 0);
			glTexCoord2f(1, 0);	 glVertex3f(0, 0.0f, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CMenuState::keyboardUpdate()
{
	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
}

//Inputs
void CMenuState::MouseMove (int x, int y) {
	InputSystem->mouseInfo.lastX = x;
	InputSystem->mouseInfo.lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	switch (button) {
		case GLUT_LEFT_BUTTON:
			
			if (state == GLUT_DOWN)
			{
				skip = true;
				se->play2D("audio/click.wav",false);
				InputSystem->mouseInfo.mLButtonUp = false;
				InputSystem->mouseInfo.clickedX = x;
				InputSystem->mouseInfo.clickedY = y;

				if(isPassed)
				{
					//go to start of the day
					if(theButton[start]->isInside(x, y))
					{
						CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());
					}

					//load game
					if(theButton[loadGame]->isInside(x, y))
						CGameStateManager::getInstance()->ChangeState(CLoadState::Instance());

					//quit game
					if(theButton[quit]->isInside(x, y))
						exit(0);
				}
			}
			else
				InputSystem->mouseInfo.mLButtonUp = true;
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CMenuState::MouseWheel(int button, int dir, int x, int y) {

}

void CMenuState::playSound()
{
	sound->setFileName("audio/Sims.mp3");
	sound->playSoundThreaded();
}

