#include "EndOfDayState.h"
#include "PlayState.h"

CEndOfDayState CEndOfDayState::theEndOfDayState;

void CEndOfDayState::Init()
{
	cout << "CEndOfDayState::Init\n" << endl;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;

}

void CEndOfDayState::Cleanup()
{
	//cout << "CEndOfDayState::Cleanup\n" << endl;
	/*if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}*/
}

void CEndOfDayState::Pause()
{
	//cout << "CEndOfDayState::Pause\n" << endl;
}

void CEndOfDayState::Resume()
{
	//cout << "CEndOfDayState::Resume\n" << endl;
}

void CEndOfDayState::HandleEvents(CInGameStateManager* theGSM)
{
}

void CEndOfDayState::Update(CInGameStateManager* theGSM) 
{
	//cout << "CEndOfDayState::Update\n" << endl;
	keyboardUpdate();

}

void CEndOfDayState::Draw(CInGameStateManager* theGSM) 
{
	CApplication::getInstance()->theCamera->SetHUD(true);

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor3f(0,1,0);

		glPushMatrix();
			glBegin(GL_QUADS);
				glVertex2f(0,SCREEN_HEIGHT);
				glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);
				glVertex2f(SCREEN_WIDTH,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CEndOfDayState::keyboardUpdate()
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}
