#include "helpState.h"

helpState helpState::theHelpState;




helpState::~helpState(void)
{
}


void helpState::LoadTextures()
{
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/back.tga"); // Back Button
	CApplication::getInstance()->LoadTGA(&button[1],"images/volDown.tga"); // Vol up Button 
	CApplication::getInstance()->LoadTGA(&button[2],"images/volUp.tga"); // Vol down Button
	CApplication::getInstance()->LoadTGA(&background[0],"images/description.tga"); //help state Background image

}

void helpState::LoadButtons()
{
	//buttons
	theButton[back] = new CButtons(0, SCREEN_HEIGHT - 64, 64, 64, back);
	theButton[back]->setButtonTexture(button[0].texID);

	theButton[volDown] = new CButtons(SCREEN_WIDTH/2 - 250, SCREEN_HEIGHT - 150, 64, 64, volDown);
	theButton[volDown]->setButtonTexture(button[1].texID);

	theButton[volUp] = new CButtons(SCREEN_WIDTH - 210, SCREEN_HEIGHT - 150, 64, 64, volDown);
	theButton[volUp]->setButtonTexture(button[2].texID);
}

void helpState::Init()
{
	cout << "helpState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	//Input System
	InputSystem = CInputSystem::getInstance();
	CInputSystem::getInstance()->mouseInfo.mLClicked = false;
	CInputSystem::getInstance()->mouseInfo.mLReclicked = true;

	//Audio Player
	se = createIrrKlangDevice();
	font_style = GLUT_BITMAP_HELVETICA_18;
	//generatenoise();
	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;
	//sound = AudioPlayer::Instance();
	//playSound();

	sound = AudioPlayer::Instance();
	sound->getFileName();
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
	DrawInfo();
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
	theButton[back]->drawButton();

	theButton[volDown]->drawButton();

	theButton[volUp]->drawButton();

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

void helpState::DrawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			glColor3f( 1.0f, 1.0f, 0.0f);
			printw (SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 125, 0, "Volume: %d", sound->getCurrentVolume());
		glPopAttrib();
	glPopMatrix();
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
			if (state == GLUT_UP) {
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
				CInputSystem::getInstance()->mouseInfo.mLReclicked = true;
			}
			else if (state == GLUT_DOWN)
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				//skip = true;
				se->play2D("audio/click.wav",false);
				InputSystem->mouseInfo.mLButtonUp = false;
				InputSystem->mouseInfo.clickedX = x;
				InputSystem->mouseInfo.clickedY = y;

						if(CInputSystem::getInstance()->mouseInfo.mLReclicked == true)
						CInputSystem::getInstance()->mouseInfo.mLClicked = true;
						CInputSystem::getInstance()->mouseInfo.mLReclicked = false;

					if(CInputSystem::getInstance()->mouseInfo.mLClicked == true)
					{
						//go to start of the day
						if(theButton[back]->isInside(x, y))
						{
							//CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());
							CGameStateManager::getInstance()->PopState();
						}


						if(theButton[volUp]->isInside(x, y))
						{						
							sound->increaseVolume(10);
							if (se->getSoundVolume() >= 1)
							{
								se->setSoundVolume(1);
							}
							else
							{
								se->setSoundVolume(se->getSoundVolume() +0.10);
							}
							//theButton[sliding]->setButtonX(theButton[sliding]->getButtonX() + sound->getCurrentVolume());

						}
						if(theButton[volDown]->isInside(x, y))
						{
							sound->decreaseVolume(10);
							if (se->getSoundVolume() <= 0)
							{
								se->setSoundVolume(0);
							}
							else
							{
								se->setSoundVolume(se->getSoundVolume() - 0.1);
							}
							//theButton[sliding]->setButtonX(theButton[sliding]->getButtonX() - sound->getCurrentVolume());
						}
						cout<<sound->getCurrentVolume()<<endl;
						cout<<se->getSoundVolume();
						CInputSystem::getInstance()->mouseInfo.mLClicked = false;
					}
			}
			else
				InputSystem->mouseInfo.mLButtonUp = true;
			CInputSystem::getInstance()->mouseInfo.clickedX = x;
			CInputSystem::getInstance()->mouseInfo.clickedY = y;
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void helpState::printw (float x, float y, float z, char* format, ...)
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