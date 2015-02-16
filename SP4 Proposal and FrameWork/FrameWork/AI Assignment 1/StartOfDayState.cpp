#include "StartOfDayState.h"
#include "GamePlayState.h"
#include "PlayState.h"

CStartOfDayState CStartOfDayState::theStartOfDayState;

void CStartOfDayState::Init()
{
	cout << "CStartOfDayState::Init\n" << endl;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;

}

void CStartOfDayState::Cleanup()
{
	//cout << "CStartOfDayState::Cleanup\n" << Startl;
	/*if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}*/
}

void CStartOfDayState::Pause()
{
	//cout << "CStartOfDayState::Pause\n" << Startl;
}

void CStartOfDayState::Resume()
{
	//cout << "CStartOfDayState::Resume\n" << Startl;
}

void CStartOfDayState::HandleEvents(CInGameStateManager* theGSM)
{
}

void CStartOfDayState::Update(CInGameStateManager* theGSM) 
{
	//cout << "CStartOfDayState::Update\n" << Startl;
	keyboardUpdate();

}

void CStartOfDayState::Draw(CInGameStateManager* theGSM) 
{
	CApplication::getInstance()->theCamera->SetHUD(true);

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor3f(0,0,1);

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

void CStartOfDayState::keyboardUpdate()
{
	if(CInputSystem::getInstance()->myKeys['s'])
		CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());

	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}
