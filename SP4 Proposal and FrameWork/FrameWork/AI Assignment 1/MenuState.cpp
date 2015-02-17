#include "MenuState.h"
#include "PlayState.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	cout << "CMenuState::Init\n" << endl;

	glEnable(GL_TEXTURE_2D);
		CApplication::getInstance()->LoadTGA(&bg[0],"SkyBox/skybox_near.tga");
	glDisable(GL_TEXTURE_2D);

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

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void CMenuState::keyboardUpdate()
{
	if(InputSystem->myKeys['a'])
		CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());

	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
}

