#include "helpState.h"


helpState::helpState(void)
{
}


helpState::~helpState(void)
{
}


void helpState::LoadTextures()
{
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/back.tga"); // Back Button
	CApplication::getInstance()->LoadTGA(&button[1],"images/.tga"); // Vol up Button 
	CApplication::getInstance()->LoadTGA(&button[2],"images/.tga"); // Vol down Button
	CApplication::getInstance()->LoadTGA(&button[3],"images/.tga"); // Information Button
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga"); //help state Background image
}


void helpState::keyboardUpdate()
{
	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
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
						CInGameStateManager::getInstance()->PopState();
					}

					//load game
					if(theButton[loadGame]->isInside(x, y))
						CGameStateManager::getInstance()->ChangeState(CLoadState::Instance());

					//quit game
					if(theButton[quit]->isInside(x, y))
						exit(0);
				
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