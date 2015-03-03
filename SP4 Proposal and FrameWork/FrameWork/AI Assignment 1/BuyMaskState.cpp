#include "BuyMaskState.h"
#include "PlayState.h"
#include "StartOfDayState.h"
#include "LoadState.h"
#include "EndOfDayState.h"
#include "TextureSingleton.h"

CBuyMaskState * CBuyMaskState::theBuyMaskState = NULL;

void CBuyMaskState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	
	for (int i = 0; i < 3; i++)
	{
		background[i].texID = theInstance->GetNumber(i + 6);
	}

	button[0].texID = theInstance->GetNumber(9);
	for (int i = 0; i < 3; i++)
	{
		button[i + 1].texID = theInstance->GetNumber(i + 15);
	}

	/*CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&background[1],"images/buyMaskState/box.tga");
	CApplication::getInstance()->LoadTGA(&background[2],"images/buyMaskState/box2.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/buyMaskState/next.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/buyMaskState/50.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/buyMaskState/100.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/buyMaskState/200.tga");*/
}

void CBuyMaskState::LoadButtons()
{
	//buttons
	theButton[nextPage] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 100, 300, 80, nextPage);
	theButton[nextPage]->setButtonTexture(button[0].texID);

	theButton[bFifty] = new CButtons(70, SCREEN_HEIGHT/2, 100, 60, bFifty);
	theButton[bFifty]->setButtonTexture(button[1].texID);
	
	theButton[bHundred] = new CButtons(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2, 100, 60, bHundred);
	theButton[bHundred]->setButtonTexture(button[2].texID);
	
	theButton[bTwohundred] = new CButtons(SCREEN_WIDTH - 160, SCREEN_HEIGHT/2, 100, 60, bTwohundred);
	theButton[bTwohundred]->setButtonTexture(button[3].texID);
}

void CBuyMaskState::Init()
{
	for (int i = 0; i < 4; i++)
	{
		theButton[i] = NULL;
	}

	if (sound != NULL)
	{
		sound = NULL;
	}

	if (se != NULL)
	{
		se = NULL;
	}


	thisState = BuyMaskState;

	cout << "CBuyMaskState::Init\n" << endl;

	LoadTextures();
	LoadButtons();
	font_style = GLUT_BITMAP_HELVETICA_18;
	se = createIrrKlangDevice();


	if (CLoadState::Instance()->getLoaded())
	{
		CPlayState::Instance()->theMoney.setCurrentMoney(CLoadState::Instance()->getLoadData()->getMoney());
		CPlayState::Instance()->maskInStock = CLoadState::Instance()->getLoadData()->getMask();
		CPlayState::Instance()->day = CLoadState::Instance()->getLoadData()->getDay();
		CPlayState::Instance()->forecasting->setCurrentDay(CLoadState::Instance()->getLoadData()->getDay());
	}
	else
	{
		if(CPlayState::Instance()->firstDay)
			CPlayState::Instance()->theMoney.setCurrentMoney(900);
		else
			CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->newMoneyValue);
	}

	needMoney = false;

	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CBuyMaskState::Update(CInGameStateManager* theGSM) 
{
	//cout << "CEndOfDayState::Update\n" << endl;
	keyboardUpdate();
}

void CBuyMaskState::Draw(CInGameStateManager* theGSM) 
{
	Camera::getInstance()->SetHUD(true);
	DrawBackground();
	DrawButtons();
	drawInfo();
	Camera::getInstance()->SetHUD(false);
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

	//gray rectangle
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glPushMatrix();
			glTranslatef(20, SCREEN_HEIGHT/2 - 100, 0);
			glScalef( (static_cast<GLfloat>(0.95)), (static_cast<GLfloat>(0.4)), 1);
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

	//three green rectangle
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[2].texID);
		glPushMatrix();
			glTranslatef(60, SCREEN_HEIGHT/2 - 35, 0);
			glScalef((static_cast<GLfloat>(0.15)), (static_cast<GLfloat>(0.2)), 1);
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
		glBindTexture(GL_TEXTURE_2D, background[2].texID);
		glPushMatrix();
			glTranslatef(SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 - 35, 0);
			glScalef((static_cast<GLfloat>(0.15)), (static_cast<GLfloat>(0.2)), 1);
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
		glBindTexture(GL_TEXTURE_2D, background[2].texID);
		glPushMatrix();
			glTranslatef(SCREEN_WIDTH - 170,  SCREEN_HEIGHT/2 - 35, 0);
			glScalef((static_cast<GLfloat>(0.15)), (static_cast<GLfloat>(0.2)), 1);
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

void CBuyMaskState::keyboardUpdate()
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}

void CBuyMaskState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) 
			{//obj = 
				se->play2D("audio/click.wav",false);
				//obj->setVolume(25.0);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//go to sell setting
				if(theButton[nextPage]->isInside(x, y))
				{
					se->play2D("audio/cashRegister.mp3",false);
					CPlayState::Instance()->oldMaskValue = CPlayState::Instance()->maskInStock;
					CPlayState::Instance()->moneyAfterBuy = CPlayState::Instance()->theMoney.getCurrentMoney();
					CInGameStateManager::getInstance()->ChangeState(CStartOfDayState::Instance());
				}

				if(theButton[bFifty]->isInside(x, y))
				{
					if(CPlayState::Instance()->theMoney.getCurrentMoney() < 250)
						needMoney = true;
					else{
						CPlayState::Instance()->theMoney.setCurrentMoney(CPlayState::Instance()->theMoney.getCurrentMoney() - 250);
						CPlayState::Instance()->maskInStock += 50;
						if (se->isCurrentlyPlaying("audio/stock.mp3") != true)
						{
							se->play2D("audio/stock.mp3",false);
						}
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
						if (se->isCurrentlyPlaying("audio/stock.mp3") != true)
						{
							se->play2D("audio/stock.mp3",false);
						}
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
						if (se->isCurrentlyPlaying("audio/stock.mp3") != true)
						{
							se->play2D("audio/stock.mp3",false);
						}
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
			glColor3f(0.8f, 0.1f, 0.1f);
			printw (200, 120, 0, "Click the buttons to select the number of mask to buy.");
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (300, 250, 0, "Number of mask and cost:");

			printw ( (static_cast<float>(theButton[bFifty]->getButtonX() + theButton[bFifty]->getWidth() / 2)),	 static_cast<float>(theButton[bFifty]->getButtonY() - 10), 0, "$250");
			printw((static_cast<float>(theButton[bHundred]->getButtonX()) + theButton[bHundred]->getWidth() / 2), (static_cast<float>(theButton[bHundred]->getButtonY() - 10)), 0, "$450");
			printw((static_cast<float>(theButton[bTwohundred]->getButtonX() + theButton[bTwohundred]->getWidth() / 2)), (static_cast<float>(theButton[bTwohundred]->getButtonY() - 10)), 0, "$850");

			if(needMoney)
			{
				glColor3f( 1.0f, 0.0f, 0.0f);
				printw ((SCREEN_WIDTH/2)-100, SCREEN_HEIGHT/2 + 130, 0, "You need more money!!!");
			}

			glColor3f( 0.5f, 0.0f, 0.5f);
			printw (SCREEN_WIDTH/2-50, 180, 0, "Mask in Stock: %d", CPlayState::Instance()->maskInStock);

			glColor3f( 0.5f, 0.0f, 0.8f);
			printw (SCREEN_WIDTH-150, 180, 0, "Money: $%d", CPlayState::Instance()->theMoney.getCurrentMoney());

			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (50, 180, 0, "Day: %d", CPlayState::Instance()->day );
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


