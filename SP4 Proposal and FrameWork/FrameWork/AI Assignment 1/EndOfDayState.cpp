#include "EndOfDayState.h"
#include "PlayState.h"
#include "SaveState.h"
#include "BuyMaskState.h"

CEndOfDayState CEndOfDayState::theEndOfDayState;

void CEndOfDayState::LoadTextures()
{
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/endState/save.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/endState/next.tga");
}
void CEndOfDayState::LoadButtons()
{
	theButton[save] = new CButtons(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT - 100, 200, 100, save);
	theButton[save]->setButtonTexture(button[0].texID);

	theButton[eNext] = new CButtons(SCREEN_WIDTH/2 + 100, SCREEN_HEIGHT - 100, 200, 100, eNext);
	theButton[eNext]->setButtonTexture(button[1].texID);
}

void CEndOfDayState::Init()
{
	cout << "CEndOfDayState::Init\n" << endl;

	LoadTextures();
	LoadButtons();
	font_style = GLUT_BITMAP_HELVETICA_18;
	//Input System
	CInputSystem::getInstance()->OrientCam = true;
	CPlayState::Instance()->forecasting->setCurrentDay(CPlayState::Instance()->forecasting->getCurrentDay() + 1);
	CPlayState::Instance()->day = CPlayState::Instance()->forecasting->getCurrentDay();
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
	DrawBackground();
	DrawButtons();
	drawInfo();
	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CEndOfDayState::DrawButtons()
{
	theButton[save]->drawButton();
	theButton[eNext]->drawButton();
}

void CEndOfDayState::DrawBackground()
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
			if (state == GLUT_DOWN) 
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//save the game
				if(theButton[save]->isInside(x, y))
					CGameStateManager::getInstance()->ChangeState(CSaveState::Instance());

				//back to buyMaskState
				if(theButton[eNext]->isInside(x, y))
				{
					CPlayState::Instance()->firstDay = false;
					CPlayState::Instance()->theStall[0]->setMaskNo(0);
					CPlayState::Instance()->theStall[1]->setMaskNo(0);
					CPlayState::Instance()->theStall[2]->setMaskNo(0);
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

void CEndOfDayState::MouseWheel(int button, int dir, int x, int y) {

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

void CEndOfDayState::drawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			//print shop number
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (50.0, 100, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[0]->getTotalMaskSold());
			printw (50.0, 130.0, 0, "Money Earned: %d", CPlayState::Instance()->earned);

			printw (300.0, 100, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[1]->getTotalMaskSold());
			printw (300.0, 130.0, 0, "Money Earned: %d", CPlayState::Instance()->earned2);

			printw (550.0, 100, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[2]->getTotalMaskSold());
			printw (550.0, 130.0, 0, "Money Earned: %d", CPlayState::Instance()->earned3);
			
			int totalMaskSold = CPlayState::Instance()->theStall[0]->getTotalMaskSold() + CPlayState::Instance()->theStall[1]->getTotalMaskSold() + CPlayState::Instance()->theStall[2]->getTotalMaskSold();
			int maskLeft = (CPlayState::Instance()->totalMaskForSell - totalMaskSold) + CPlayState::Instance()->maskInStock;
			printw ((SCREEN_WIDTH / 2) - 200, SCREEN_HEIGHT/2 + 150, 0, "Mask Left: %d", maskLeft);

			int totalEarn = CPlayState::Instance()->earned + CPlayState::Instance()->earned2 + CPlayState::Instance()->earned3;
			printw ((SCREEN_WIDTH/2)-100, SCREEN_HEIGHT/2, 0, "Total Money Earned: %d", totalEarn);

			CPlayState::Instance()->newMoneyValue = totalEarn + CPlayState::Instance()->theMoney.getCurrentMoney();
			printw ((SCREEN_WIDTH/2)+50, SCREEN_HEIGHT/2 + 150, 0, "Total Money : %d", CPlayState::Instance()->newMoneyValue);

		glPopAttrib();
	glPopMatrix();
}

void CEndOfDayState::printw (float x, float y, float z, char* format, ...)
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

