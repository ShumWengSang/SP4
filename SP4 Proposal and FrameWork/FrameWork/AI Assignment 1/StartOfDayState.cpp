#include "StartOfDayState.h"
#include "GamePlayState.h"
#include "PlayState.h"

CStartOfDayState CStartOfDayState::theStartOfDayState;

void CStartOfDayState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/go.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/startState/50.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/startState/100.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/startState/200.tga");
	CApplication::getInstance()->LoadTGA(&button[4],"images/startState/10.tga");
	CApplication::getInstance()->LoadTGA(&button[5],"images/startState/12.tga");
	CApplication::getInstance()->LoadTGA(&button[6],"images/startState/15.tga");
}
void CStartOfDayState::LoadButtons()
{
	//buttons
	theButton[go] = new CButtons(SCREEN_WIDTH/2, SCREEN_HEIGHT - 100, 200, 100, go);
	theButton[go]->setButtonTexture(button[0].texID);

	//For shop 1
	theButton[fifty] = new CButtons(50, 100, 50, 30, fifty);
	theButton[fifty]->setButtonTexture(button[1].texID);
	
	theButton[hundred] = new CButtons(101, 100, 50, 30, hundred);
	theButton[hundred]->setButtonTexture(button[2].texID);
	
	theButton[twohundred] = new CButtons(152, 100, 50, 30, twohundred);
	theButton[twohundred]->setButtonTexture(button[3].texID);

	theButton[ten] = new CButtons(50, 150, 50, 30, fifty);
	theButton[ten]->setButtonTexture(button[4].texID);
	
	theButton[twelve] = new CButtons(101, 150, 50, 30, hundred);
	theButton[twelve]->setButtonTexture(button[5].texID);
	
	theButton[fifteen] = new CButtons(152, 150, 50, 30, twohundred);
	theButton[fifteen]->setButtonTexture(button[6].texID);

	//For shop 2
	theButton[fifty2] = new CButtons(300, 100, 50, 30, fifty2);
	theButton[fifty2]->setButtonTexture(button[1].texID);

	theButton[hundred2] = new CButtons(351, 100, 50, 30, hundred2);
	theButton[hundred2]->setButtonTexture(button[2].texID);

	theButton[twohundred2] = new CButtons(402, 100, 50, 30, twohundred2);
	theButton[twohundred2]->setButtonTexture(button[3].texID);

	theButton[ten2] = new CButtons(300, 150, 50, 30, fifty);
	theButton[ten2]->setButtonTexture(button[4].texID);
	
	theButton[twelve2] = new CButtons(351, 150, 50, 30, hundred);
	theButton[twelve2]->setButtonTexture(button[5].texID);
	
	theButton[fifteen2] = new CButtons(402, 150, 50, 30, twohundred);
	theButton[fifteen2]->setButtonTexture(button[6].texID);

	//For shop 3
	theButton[fifty3] = new CButtons(550, 100, 50, 30, fifty3);
	theButton[fifty3]->setButtonTexture(button[1].texID);

	theButton[hundred3] = new CButtons(601, 100, 50, 30, hundred3);
	theButton[hundred3]->setButtonTexture(button[2].texID);

	theButton[twohundred3] = new CButtons(652, 100, 50, 30, twohundred3);
	theButton[twohundred3]->setButtonTexture(button[3].texID);

	theButton[ten3] = new CButtons(550, 150, 50, 30, fifty);
	theButton[ten3]->setButtonTexture(button[4].texID);
	
	theButton[twelve3] = new CButtons(601, 150, 50, 30, hundred);
	theButton[twelve3]->setButtonTexture(button[5].texID);
	
	theButton[fifteen3] = new CButtons(652, 150, 50, 30, twohundred);
	theButton[fifteen3]->setButtonTexture(button[6].texID);
}

void CStartOfDayState::Init()
{
	cout << "CStartOfDayState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

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
	//drawWords();
	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CStartOfDayState::DrawButtons()
{
	theButton[go]->drawButton();

	theButton[fifty]->drawButton();
	theButton[hundred]->drawButton();
	theButton[twohundred]->drawButton();

	theButton[ten]->drawButton();
	theButton[twelve]->drawButton();
	theButton[fifteen]->drawButton();


	theButton[fifty2]->drawButton();
	theButton[hundred2]->drawButton();
	theButton[twohundred2]->drawButton();

	theButton[ten2]->drawButton();
	theButton[twelve2]->drawButton();
	theButton[fifteen2]->drawButton();


	theButton[fifty3]->drawButton();
	theButton[hundred3]->drawButton();
	theButton[twohundred3]->drawButton();

	theButton[ten3]->drawButton();
	theButton[twelve3]->drawButton();
	theButton[fifteen3]->drawButton();
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

				//start the day
				if(theButton[go]->isInside(x, y))
					CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());

				//For Shop 1 no. of mask setting
				if(theButton[fifty]->isInside(x, y))
					CPlayState::Instance()->theStall[0]->setMaskNo(50);

				if(theButton[hundred]->isInside(x, y))
					CPlayState::Instance()->theStall[0]->setMaskNo(100);

				if(theButton[twohundred]->isInside(x, y))
					CPlayState::Instance()->theStall[0]->setMaskNo(200);

				//For Shop 2 no. of mask setting
				if(theButton[fifty2]->isInside(x, y))
					CPlayState::Instance()->theStall[1]->setMaskNo(50);

				if(theButton[hundred2]->isInside(x, y))
					CPlayState::Instance()->theStall[1]->setMaskNo(100);

				if(theButton[twohundred2]->isInside(x, y))
					CPlayState::Instance()->theStall[1]->setMaskNo(200);

				//For Shop 3 no. of mask setting
				if(theButton[fifty3]->isInside(x, y))
					CPlayState::Instance()->theStall[2]->setMaskNo(50);

				if(theButton[hundred3]->isInside(x, y))
					CPlayState::Instance()->theStall[2]->setMaskNo(100);

				if(theButton[twohundred3]->isInside(x, y))
					CPlayState::Instance()->theStall[2]->setMaskNo(200);
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

void CStartOfDayState::drawWords()
{
	glPushMatrix();
		glLoadIdentity ();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
			
			printw (25.0, 25.0, 0, "Shop 1");
		glPopAttrib();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void CStartOfDayState::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}
