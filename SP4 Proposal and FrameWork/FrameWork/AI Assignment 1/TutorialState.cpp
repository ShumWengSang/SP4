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
	background[0].texID = theInstance->GetNumber(58);

	for(int i = 0; i < 4; i++)
	{
		background[i+1].texID = theInstance->GetNumber(i+53);
	}
}

void CTutorialState::Init()
{
	LoadTextures();

	rotate = 0;
	speed = 0;

	screen = 1;

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
		RenderPictures();
		Camera::getInstance()->SetHUD(false);
	}
	else
		MoveNewsPaper();
}

void CTutorialState::MoveNewsPaper()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(0.5f, 0.5f, 1);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, -1200, -100);
		glRotatef(static_cast<GLfloat>(-rotate), 0, 1, 0);
		glTranslatef(0, static_cast<GLfloat>(speed), -100);
		glBindTexture(GL_TEXTURE_2D, background[0].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1);  glVertex3f(-210, 0.0f, 210);
			glTexCoord2f(0, 1);  glVertex3f(210, 0.0f, 210); 
			glTexCoord2f(0, 0);	 glVertex3f(210, 0.0f, -210);
			glTexCoord2f(1, 0);	 glVertex3f(-210, 0.0f, -210);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CTutorialState::DrawNewsPaper()
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

void CTutorialState::DrawFirstScreen()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
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

void CTutorialState::DrawSecondScreen()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[2].texID);
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

void CTutorialState::DrawThirdScreen()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[3].texID);
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

void CTutorialState::DrawLastScreen()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[4].texID);
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

void CTutorialState::RenderPictures()
{
	switch (screen)
	{
		case 1:
			DrawNewsPaper();
			break;
		case 2:
			DrawFirstScreen();
			break;
		case 3:
			DrawSecondScreen();
			break;
		case 4:
			DrawThirdScreen();
			break;
		case 5:
			DrawLastScreen();
			break;
		case 6:
		{
			//go buy mask state
			CInGameStateManager::getInstance()->ChangeState(CBuyMaskState::Instance());
			screen = 1;
		}
			break;
	}
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

				if (speed <= 800)
				{
					rotate = 0;
					speed = 1000;
				}
				else
				{
					screen += 1;
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
