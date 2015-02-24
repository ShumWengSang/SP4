#include "BuyMaskState.h"
#include "PlayState.h"
#include "StartOfDayState.h"
#include "LoadState.h"

CBuyMaskState CBuyMaskState::theBuyMaskState;

void CBuyMaskState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&background[1],"images/buyMaskState/box.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/buyMaskState/next.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/buyMaskState/50.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/buyMaskState/100.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/buyMaskState/200.tga");
}

void CBuyMaskState::LoadButtons()
{
	//buttons
	theButton[nextPage] = new CButtons(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 100, 200, 100, nextPage);
	theButton[nextPage]->setButtonTexture(button[0].texID);

	theButton[bFifty] = new CButtons(70, 100, 50, 30, bFifty);
	theButton[bFifty]->setButtonTexture(button[1].texID);
	
	theButton[bHundred] = new CButtons(SCREEN_WIDTH/2 - 25, 100, 50, 30, bHundred);
	theButton[bHundred]->setButtonTexture(button[2].texID);
	
	theButton[bTwohundred] = new CButtons(SCREEN_WIDTH - 100, 100, 50, 30, bTwohundred);
	theButton[bTwohundred]->setButtonTexture(button[3].texID);
}

void CBuyMaskState::Init()
{
	cout << "CBuyMaskState::Init\n" << endl;

	LoadTextures();
	LoadButtons();
	font_style = GLUT_BITMAP_HELVETICA_18;


	if (CLoadState::Instance()->getLoaded())
		CPlayState::Instance()->theMoney.setCurrentMoney(CLoadState::Instance()->getLoadData()->getMoney());
	else
		CPlayState::Instance()->theMoney.setCurrentMoney(1000);

	needMoney = false;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CBuyMaskState::Update(CInGameStateManager* theGSM) 
{
	//cout << "CEndOfDayState::Update\n" << endl;
}

void CBuyMaskState::Draw(CInGameStateManager* theGSM) 
{
	CApplication::getInstance()->theCamera->SetHUD(true);
	DrawBackground();
	DrawButtons();
	drawInfo();
	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CBuyMaskState::DrawButtons()
{
	theButton[nextPage]->drawButton();
	theButton[bFifty]->drawButton();
	theButton[bHundred]->drawButton();
	theButton[bTwohundred]->drawButton();
}

void CBuyMaskState::DrawBackground()
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

	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glPushMatrix();
			glTranslatef(20, 15, 0);
			glScalef(0.95, 0.3, 1);
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

//Inputs
void CBuyMaskState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CBuyMaskState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == 0) 
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//go to sell setting
				if(theButton[nextPage]->isInside(x, y))
				{
					CInGameStateManager::getInstance()->ChangeState(CStartOfDayState::Instance());
					CPlayState::Instance()->oldMaskValue = CPlayState::Instance()->maskInStock;
				}

				if(theButton[bFifty]->isInside(x, y))
				{
					if(CPlayState::Instance()->theMoney.getCurrentMoney() < 250)
						needMoney = true;
					else{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 250);
						CPlayState::Instance()->maskInStock += 50;
						needMoney = false;
					}
				}

				if(theButton[bHundred]->isInside(x, y))
				{
					if(CPlayState::Instance()->theMoney.getCurrentMoney() < 450)
						needMoney = true;
					else{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 450);
						CPlayState::Instance()->maskInStock += 100;
						needMoney = false;
					}
				}

				if(theButton[bTwohundred]->isInside(x, y))
				{
					if(CPlayState::Instance()->theMoney.getCurrentMoney() < 850)
						needMoney = true;
					else{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 850);
						CPlayState::Instance()->maskInStock += 200;
						needMoney = false;
					}
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

void CBuyMaskState::drawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw ((SCREEN_WIDTH/2)-50, 50, 0, "Click to buy the MASK");

			printw (theButton[bFifty]->getButtonX(), theButton[bFifty]->getButtonY() + 50, 0, "$250");
			printw (theButton[bHundred]->getButtonX(), theButton[bHundred]->getButtonY() + 50, 0, "$450");
			printw (theButton[bTwohundred]->getButtonX(), theButton[bTwohundred]->getButtonY() + 50, 0, "$850");

			if(needMoney)
				printw ((SCREEN_WIDTH/2)-100, SCREEN_HEIGHT/2 - 50, 0, "You need more money!!!");

			printw ((SCREEN_WIDTH / 2) - 200, SCREEN_HEIGHT/2 + 50, 0, "Mask in Stock: %d", CPlayState::Instance()->maskInStock);
			printw ((SCREEN_WIDTH/2)+50, SCREEN_HEIGHT/2 + 50, 0, "$: %d", CPlayState::Instance()->theMoney.getCurrentMoney());
		glPopAttrib();
	glPopMatrix();
}

void CBuyMaskState::printw (float x, float y, float z, char* format, ...)
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


