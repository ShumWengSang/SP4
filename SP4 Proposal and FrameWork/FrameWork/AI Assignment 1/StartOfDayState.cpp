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
	theButton[go] = new CButtons(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100, 200, 100, go);
	theButton[go]->setButtonTexture(button[0].texID);

	//For shop 1
	CApplication::getInstance()->LoadTGA(&button[1],"images/startState/50.tga");
	theButton[fifty] = new CButtons(50, 100, 50, 30, fifty);
	theButton[fifty]->setButtonTexture(button[1].texID);

	CApplication::getInstance()->LoadTGA(&button[2],"images/startState/100.tga");
	theButton[hundred] = new CButtons(101, 100, 50, 30, hundred);
	theButton[hundred]->setButtonTexture(button[2].texID);

	CApplication::getInstance()->LoadTGA(&button[3],"images/startState/200.tga");
	theButton[twohundred] = new CButtons(152, 100, 50, 30, twohundred);
	theButton[twohundred]->setButtonTexture(button[3].texID);

	//For shop 2
	theButton[fifty2] = new CButtons(300, 100, 50, 30, fifty2);
	theButton[fifty2]->setButtonTexture(button[1].texID);

	theButton[hundred2] = new CButtons(351, 100, 50, 30, hundred2);
	theButton[hundred2]->setButtonTexture(button[2].texID);

	theButton[twohundred2] = new CButtons(402, 100, 50, 30, twohundred2);
	theButton[twohundred2]->setButtonTexture(button[3].texID);

	//For shop 3
	theButton[fifty3] = new CButtons(550, 100, 50, 30, fifty3);
	theButton[fifty3]->setButtonTexture(button[1].texID);

	theButton[hundred3] = new CButtons(601, 100, 50, 30, hundred3);
	theButton[hundred3]->setButtonTexture(button[2].texID);

	theButton[twohundred3] = new CButtons(652, 100, 50, 30, twohundred3);
	theButton[twohundred3]->setButtonTexture(button[3].texID);

	theStall[0] = new CStalls();

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
		glTranslatef(theButton[go]->getButtonX(), theButton[go]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[go]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[go]->getWidth(), theButton[go]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[go]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//50 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[fifty]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[fifty]->getButtonX(), theButton[fifty]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[fifty]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[fifty]->getWidth(), theButton[fifty]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[fifty]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//100 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[hundred]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[hundred]->getButtonX(), theButton[hundred]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[hundred]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[hundred]->getWidth(), theButton[hundred]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[hundred]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//200 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[twohundred]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[twohundred]->getButtonX(), theButton[twohundred]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[twohundred]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[twohundred]->getWidth(), theButton[twohundred]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[twohundred]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//50 mask shop 2
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[fifty2]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[fifty2]->getButtonX(), theButton[fifty2]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[fifty2]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[fifty2]->getWidth(), theButton[fifty2]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[fifty2]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//100 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[hundred2]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[hundred2]->getButtonX(), theButton[hundred2]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[hundred2]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[hundred2]->getWidth(), theButton[hundred2]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[hundred2]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//200 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[twohundred2]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[twohundred2]->getButtonX(), theButton[twohundred2]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[twohundred2]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[twohundred2]->getWidth(), theButton[twohundred2]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[twohundred2]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//50 mask shop 3
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[fifty3]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[fifty3]->getButtonX(), theButton[fifty3]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[fifty3]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[fifty3]->getWidth(), theButton[fifty3]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[fifty3]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//100 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[hundred3]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[hundred3]->getButtonX(), theButton[hundred3]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[hundred3]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[hundred3]->getWidth(), theButton[hundred3]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[hundred3]->getWidth(), 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();

	//200 mask
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, theButton[twohundred3]->getButton());
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(theButton[twohundred3]->getButtonX(), theButton[twohundred3]->getButtonY(), 0);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);	glVertex2f(0,  theButton[twohundred3]->getHeight());
			glTexCoord2f(1, 0);	glVertex2f(theButton[twohundred3]->getWidth(), theButton[twohundred3]->getHeight());
				glTexCoord2f(1, 1);	glVertex2f(theButton[twohundred3]->getWidth(), 0);
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

//Inputs
void CStartOfDayState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CStartOfDayState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == 0)
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//go to start of the day
				if(theButton[start]->isInside(x, y))
					CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());

				if(theButton[fifty]->isInside(x, y))
				{
					theStall[0]->setMaskNo(50);
					cout << "1. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}

				if(theButton[hundred]->isInside(x, y))
				{
					theStall[0]->setMaskNo(100);
					cout << "1. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}
				if(theButton[twohundred]->isInside(x, y))
				{
					theStall[0]->setMaskNo(200);
					cout << "1. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}

				if(theButton[fifty2]->isInside(x, y))
				{
					theStall[0]->setMaskNo(50);
					cout << "2. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}

				if(theButton[hundred2]->isInside(x, y))
				{
					theStall[0]->setMaskNo(100);
					cout << "2. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}
				if(theButton[twohundred2]->isInside(x, y))
				{
					theStall[0]->setMaskNo(200);
					cout << "2. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}

				if(theButton[fifty3]->isInside(x, y))
				{
					theStall[0]->setMaskNo(50);
					cout << "3. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}

				if(theButton[hundred3]->isInside(x, y))
				{
					theStall[0]->setMaskNo(100);
					cout << "3. the no of mask is: " << theStall[0]->getMaskNo() << endl;
				}
				if(theButton[twohundred3]->isInside(x, y))
				{
					theStall[0]->setMaskNo(200);
					cout << "3. the no of mask is: " << theStall[0]->getMaskNo() << endl;
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

void CStartOfDayState::MouseWheel(int button, int dir, int x, int y) {

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
