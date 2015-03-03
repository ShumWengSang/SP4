#include "TutorialState.h"

CTutorialState * CTutorialState::theTutorState = NULL;

CTutorialState::CTutorialState(void)
{
}

CTutorialState::~CTutorialState(void)
{
}

void CTutorialState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	
	/*for (int i = 0; i < 3; i++)
	{
		background[i].texID = theInstance->GetNumber(i + 6);
	}*/
}
void CTutorialState::Init()
{
	LoadTextures();

	thisState = TutorialState;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CTutorialState::Update(CInGameStateManager* GSM)
{
	keyboardUpdate();
}

void CTutorialState::Draw(CInGameStateManager* GSM)
{
	Camera::getInstance()->SetHUD(true);
	DrawBackground();
	Camera::getInstance()->SetHUD(false);
}
void CTutorialState::DrawBackground()
{
	//background
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

void CTutorialState::keyboardUpdate(void)
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}
	
//Inputs
void  CTutorialState::MouseClick(int button, int state, int x, int y)
{
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) 
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//go buy mask state
				CInGameStateManager::getInstance()->ChangeState(CBuyMaskState::Instance());
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
