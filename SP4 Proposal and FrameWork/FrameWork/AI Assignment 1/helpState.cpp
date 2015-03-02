#include "helpState.h"

helpState helpState::theHelpState;


helpState::~helpState(void)
{
}


void helpState::LoadTextures()
{
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/back.tga"); // Back Button
	CApplication::getInstance()->LoadTGA(&button[1],"images/.tga"); // Vol up Button 
	CApplication::getInstance()->LoadTGA(&button[2],"images/.tga"); // Vol down Button
	CApplication::getInstance()->LoadTGA(&button[3],"images/.tga"); // Information Button
	CApplication::getInstance()->LoadTGA(&background[0],"images/description.tga"); //help state Background image
}

void helpState::LoadButtons()
{
	//buttons
	theButton[volUp] = new CButtons(SCREEN_WIDTH/2 - 125, SCREEN_HEIGHT - 100, 250, 80, volUp);
	theButton[volUp]->setButtonTexture(button[1].texID);

	theButton[back] = new CButtons(0, SCREEN_HEIGHT - 64, 64, 64, back);
	theButton[back]->setButtonTexture(button[0].texID);

	theButton[volDown] = new CButtons(SCREEN_WIDTH - 64, SCREEN_HEIGHT - 64, 64, 64, volDown);
	theButton[volDown]->setButtonTexture(button[2].texID);
}

void helpState::Init()
{
	cout << "helpState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	//isPassed = false;
	//skip = false;
	//exponent = 0;

	//turbulencenum = 64;

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Audio Player
	se = createIrrKlangDevice();
	//generatenoise();
	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;
	//sound = AudioPlayer::Instance();
	//playSound();
}

void helpState::HandleEvents(CGameStateManager* theGSM)
{
}

void helpState::Update(CGameStateManager* theGSM) 
{
	//cout << "CStartOfDayState::Update\n" << Startl;
	keyboardUpdate();
}

void helpState::Draw(CGameStateManager* theGSM) 
{
	Camera::getInstance()->SetHUD(true);
	DrawBackground();
	DrawButtons();
	//drawInfo();
	Camera::getInstance()->SetHUD(false);
}

void helpState::keyboardUpdate()
{
	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
}

void helpState::DrawButtons()
{
	theButton[volUp]->drawButton();
	theButton[back]->drawButton();
	theButton[volDown]->drawButton();
}

void helpState::DrawBackground()
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

	/*glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[0].texID);
		glPushMatrix();
			glTranslatef(10, 10, 0);
			glScalef(static_cast<GLfloat>(0.98), static_cast<GLfloat>(0.5), 1);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, SCREEN_HEIGHT);
				glTexCoord2f(1, 0);	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
				glTexCoord2f(1, 1);	glVertex2f(SCREEN_WIDTH, 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();*/
}

// Inputs
void helpState::MouseMove (int x, int y) 
{
	InputSystem->mouseInfo.lastX = x;
	InputSystem->mouseInfo.lastY = y;
}

void helpState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	switch (button) {
		case GLUT_LEFT_BUTTON:
			
			if (state == GLUT_DOWN)
			{
				//skip = true;
				se->play2D("audio/click.wav",false);
				InputSystem->mouseInfo.mLButtonUp = false;
				InputSystem->mouseInfo.clickedX = x;
				InputSystem->mouseInfo.clickedY = y;

					//go to start of the day
					if(theButton[back]->isInside(x, y))
					{
						//CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());
						CGameStateManager::getInstance()->PopState();
					}


					if(theButton[volUp]->isInside(x, y))
					{
						int v = sound->getCurrentVolume();
						v += 10;
						sound->setVolume(v);
					}
					if(theButton[volDown]->isInside(x, y))
					{
						int v = sound->getCurrentVolume();
						v -= 10;
						sound->setVolume(v);
					}

					/*if(theButton[help]->isInside(x, y))
					{
					}*/
				
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