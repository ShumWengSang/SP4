#include "StartOfDayState.h"
#include "GamePlayState.h"
#include "PlayState.h"

CStartOfDayState CStartOfDayState::theStartOfDayState;

void CStartOfDayState::Init()
{
	cout << "CStartOfDayState::Init\n" << endl;

	//Textures
	//background
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");

	//buttons
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/go.tga");
	theButton[go] = new CButtons(go);
	theButton[go]->setButtonTexture(button[0].texID);

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
	DrawBackground();
	DrawButtons();
	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CStartOfDayState::DrawButtons()
{
	//start game
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[go]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 100, 0);
			glScalef(0.2, 0.1, 1);
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

void CStartOfDayState::DrawBackground()
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

void CStartOfDayState::keyboardUpdate()
{
	if(CInputSystem::getInstance()->myKeys['s'])
		CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());

	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}
