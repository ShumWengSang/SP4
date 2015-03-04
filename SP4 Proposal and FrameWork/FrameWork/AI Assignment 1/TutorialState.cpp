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
	background[0].texID = theInstance->GetNumber(50);
}
void CTutorialState::Init()
{
	cout << "Tutorial state init" << endl;
	LoadTextures();

	rotate = 0;
	speed = 0;

	thisState = TutorialState;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CTutorialState::Update(CInGameStateManager* GSM)
{
	rotate += 20;
	speed += pow(3.f,2.f) ;

	if(speed >= 800)
	{
		rotate = 0;
		speed = 1000;
	}
	Camera::getInstance()->newUpdate();
	keyboardUpdate();
}

void CTutorialState::Draw(CInGameStateManager* GSM)
{
	if(speed >= 800)
	{
		Camera::getInstance()->SetHUD(true);
		DrawBackground();
		Camera::getInstance()->SetHUD(false);
	}
	else
		DrawNewsPaper();
}
void CTutorialState::DrawBackground()
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

void CTutorialState::DrawNewsPaper()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(0.5f, 0.5f, 1);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, -1200, -100);
		glRotatef(-rotate, 0, 1, 0);
		glTranslatef(0, speed, -100);
		glBindTexture(GL_TEXTURE_2D, background[0].texID);
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

void CTutorialState::keyboardUpdate(void)
{
	if(CInputSystem::getInstance()->myKeys['a'])
		Camera::getInstance()->Strafe(-1);
	if(CInputSystem::getInstance()->myKeys['d'])
		Camera::getInstance()->Strafe(1);
	if(CInputSystem::getInstance()->myKeys['w'])
		Camera::getInstance()->Walk(1);
	if(CInputSystem::getInstance()->myKeys['s'])
		Camera::getInstance()->Walk(-1);
	if(CInputSystem::getInstance()->myKeys['c'])
		cout << Camera::getInstance()->GetPos() << endl;
	if(CInputSystem::getInstance()->myKeys['x'])
		cout << rotate << endl;
	if(CInputSystem::getInstance()->myKeys['z'])
		cout << speed << endl;
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

				if (speed <= 800)
				{
					rotate = 0;
					speed = 1000;
				}
				else
				{
					//go buy mask state
					CInGameStateManager::getInstance()->ChangeState(CBuyMaskState::Instance());
				}
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
