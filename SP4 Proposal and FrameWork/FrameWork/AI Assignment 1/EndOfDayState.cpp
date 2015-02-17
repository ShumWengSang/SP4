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

//Inputs
void CEndOfDayState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CEndOfDayState::MouseClick(int button, int state, int x, int y) {
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

void CEndOfDayState::MouseWheel(int button, int dir, int x, int y) {

	if(typeid(CApplication::getInstance()->GSM->GetCurrentState()).name() == typeid(CGameState*).name())
		cout << typeid(CApplication::getInstance()->GSM->GetCurrentState()).name() << endl;

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

