#include "StartOfDayState.h"
#include "GamePlayState.h"
#include "PlayState.h"
#include "BuyMaskState.h"
#include "TextureSingleton.h"

CStartOfDayState *CStartOfDayState::theStartOfDayState = NULL;

void CStartOfDayState::LoadTextures()
{
	//Textures

	TextureSingleton * theInstance = TextureSingleton::getInstance();
	background[0].texID = theInstance->GetNumber(38);
	background[1].texID = theInstance->GetNumber(13);
	for (int i = 0; i < 15; i++)
	{
		button[i].texID = theInstance->GetNumber(i + 14);
	}

	button[15].texID = theInstance->GetNumber(47);
	button[16].texID = theInstance->GetNumber(48);
}

void CStartOfDayState::LoadButtons()
{
	//buttons
	theButton[go] = new CButtons(SCREEN_WIDTH/2 - 125, SCREEN_HEIGHT - 100, 250, 80, go);
	theButton[go]->setButtonTexture(button[0].texID);

	theButton[back] = new CButtons(0, SCREEN_HEIGHT - 64, 64, 64, back);
	theButton[back]->setButtonTexture(button[7].texID);

	theButton[reset] = new CButtons(SCREEN_WIDTH - 64, SCREEN_HEIGHT - 64, 64, 64, reset);
	theButton[reset]->setButtonTexture(button[8].texID);

	theButton[fifty] = new CButtons(50, SCREEN_HEIGHT/2 + 80, 75, 45, fifty);
	theButton[fifty]->setButtonTexture(button[1].texID);
	
	theButton[hundred] = new CButtons(130, SCREEN_HEIGHT/2 + 80, 75, 45, hundred);
	theButton[hundred]->setButtonTexture(button[2].texID);
	
	theButton[twohundred] = new CButtons(210, SCREEN_HEIGHT/2 + 80, 75, 45, twohundred);
	theButton[twohundred]->setButtonTexture(button[3].texID);

	theButton[ten] = new CButtons(SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 80, 75, 45, ten);
	theButton[ten]->setButtonTexture(button[4].texID);
	
	theButton[twelve] = new CButtons(SCREEN_WIDTH/2 + 160, SCREEN_HEIGHT/2 + 80, 75, 45, twelve);
	theButton[twelve]->setButtonTexture(button[5].texID);
	
	theButton[fifteen] = new CButtons(SCREEN_WIDTH/2 + 240, SCREEN_HEIGHT/2 + 80, 75, 45, fifteen);
	theButton[fifteen]->setButtonTexture(button[6].texID);

	theButton[sShop1] = new CButtons(85, 150, 90, 64, sShop1);
	theButton[sShop1]->setButtonTexture(button[9].texID);

	theButton[sShop2] = new CButtons(SCREEN_WIDTH/2 - 50, 150, 90, 64, sShop2);
	theButton[sShop2]->setButtonTexture(button[10].texID);

	theButton[sShop3] = new CButtons(SCREEN_WIDTH - 200, 150, 90, 64, sShop3);
	theButton[sShop3]->setButtonTexture(button[11].texID);

	theButton[yes] = new CButtons(SCREEN_WIDTH/2 + 30, SCREEN_HEIGHT/2, 125, 60, yes);
	theButton[yes]->setButtonTexture(button[15].texID);

	theButton[no] = new CButtons(SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT/2, 125, 60, no);
	theButton[no]->setButtonTexture(button[16].texID);
}

void CStartOfDayState::Init()
{
	for (int i = 0; i < 20; i++)
	{
		theButton[i] = NULL;
	}

	sound = NULL;

	se = NULL;

	thisState = StartofDayState;

	cout << "CStartOfDayState::Init\n" << endl;
	se = createIrrKlangDevice();
	LoadTextures();
	LoadButtons();

	mouseOverReset = false;
	mouseOverBack = false;
	amtOrMoney = 0;

	r = 0, g = 0, b = 0;
	r2 = 0, g2 = 0, b2 = 0;
	r3 = 0, g3 = 0, b3 = 0;

	font_style = GLUT_BITMAP_HELVETICA_18;
	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CStartOfDayState::Cleanup()
{
	//cout << "CStartOfDayState::Cleanup\n" << Startl;
	//if (InputSystem != NULL)
	//{
	//	delete InputSystem;
	//	InputSystem = NULL;
	//}
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
	Camera::getInstance()->SetHUD(true);
	DrawBackground();
	DrawButtons();
	drawInfo();
	if(amtOrMoney == true)
		DrawMsg();
	Camera::getInstance()->SetHUD(false);
}

void CStartOfDayState::DrawButtons()
{
	theButton[go]->drawButton();
	theButton[back]->drawButton();
	theButton[reset]->drawButton();

	theButton[fifty]->drawButton();
	theButton[hundred]->drawButton();
	theButton[twohundred]->drawButton();

	theButton[ten]->drawButton();
	theButton[twelve]->drawButton();
	theButton[fifteen]->drawButton();

	theButton[sShop1]->drawButton();
	if(CPlayState::Instance()->theStall[0]->Selected)
		theButton[sShop1]->setButtonTexture(button[12].texID);
	else
		theButton[sShop1]->setButtonTexture(button[9].texID);

	theButton[sShop2]->drawButton();
	if(CPlayState::Instance()->theStall[1]->Selected)
		theButton[sShop2]->setButtonTexture(button[13].texID);
	else
		theButton[sShop2]->setButtonTexture(button[10].texID);

	theButton[sShop3]->drawButton();
	if(CPlayState::Instance()->theStall[2]->Selected)
		theButton[sShop3]->setButtonTexture(button[14].texID);
	else
		theButton[sShop3]->setButtonTexture(button[11].texID);
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

	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glPushMatrix();
			glTranslatef(10, 10, 0);
			glScalef(static_cast<GLfloat>(0.98), static_cast<GLfloat>(0.5), 1);
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

void CStartOfDayState::DrawMsg()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glPushMatrix();
			glTranslatef(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 200, 0);
			glScalef(static_cast<GLfloat>(0.5), static_cast<GLfloat>(0.5), 1);
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
		glPushAttrib(GL_DEPTH_TEST);
		glColor3f(0, 0, 0);
		printw (SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 150, 0, "You Have");
		printw (SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 120, 0, "the Number Of Mask or Price");
		printw (SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 90, 0, "Do you want to start the day?");
		glPopAttrib();
	glPopMatrix();

	theButton[yes]->drawButton();
	theButton[no]->drawButton();
}

bool CStartOfDayState::checkZero()
{
	for(int i = 0; i < 3; i++)
	{
		if(CPlayState::Instance()->theStall[i]->getMaskNo() == 0 || CPlayState::Instance()->theStall[i]->getMaskPrice() == 0)
		{
			amtOrMoney = true;
			return true;
		}
	}
	return false;
}

void CStartOfDayState::ChangeColor()
{
	if(CPlayState::Instance()->theStall[0]->Selected)
	{
		r = (rand()/((float)RAND_MAX)) - 0.2f;
		g = (rand()/((float)RAND_MAX)) - 0.5f;
		b = rand()/((float)RAND_MAX);
	}
	if(CPlayState::Instance()->theStall[1]->Selected)
	{
		r2 = (rand()/((float)RAND_MAX)) - 0.2f;
		g2 = (rand()/((float)RAND_MAX)) - 0.5f;
		b2 = rand()/((float)RAND_MAX);
	}
	if(CPlayState::Instance()->theStall[2]->Selected)
	{
		r3 = (rand()/((float)RAND_MAX)) - 0.2f;
		g3 = (rand()/((float)RAND_MAX)) - 0.5f;
		b3 = rand()/((float)RAND_MAX);
	}
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
void CStartOfDayState::MouseMove (int x, int y) 
{
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;

	if(theButton[reset]->isInside(x, y))
		mouseOverReset = true;
	else
		mouseOverReset = false;

	if(theButton[back]->isInside(x, y))
		mouseOverBack = true;
	else
		mouseOverBack = false;
}

void CStartOfDayState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				se->play2D("audio/click.wav",false);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//start the day
				if(theButton[go]->isInside(x, y))
				{
					if(checkZero())
						amtOrMoney = true;
					else{
						CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());
						CPlayState::Instance()->totalMaskForSell = CPlayState::Instance()->theStall[0]->getMaskNo() + CPlayState::Instance()->theStall[1]->getMaskNo() + CPlayState::Instance()->theStall[2]->getMaskNo();
					}
				}

				if(theButton[yes]->isInside(x, y))
				{
					CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());
					CPlayState::Instance()->totalMaskForSell = CPlayState::Instance()->theStall[0]->getMaskNo() + CPlayState::Instance()->theStall[1]->getMaskNo() + CPlayState::Instance()->theStall[2]->getMaskNo();
				}

				if(theButton[no]->isInside(x, y))
				{
					amtOrMoney = false;
				}

				//back to buy mask
				if(theButton[back]->isInside(x, y))
					CInGameStateManager::getInstance()->PopState();

				if(theButton[reset]->isInside(x, y))
				{
					CPlayState::Instance()->maskInStock = CPlayState::Instance()->oldMaskValue;
					for(int i = 0; i <3; i++)
					{
						CPlayState::Instance()->theStall[i]->setMaskNo(0);
						CPlayState::Instance()->theStall[i]->setMaskPrice(0);
						CPlayState::Instance()->theStall[i]->Selected = false;
					}
					r = 0, g = 0, b = 0;
					r2 = 0, g2 = 0, b2 = 0;
					r3 = 0, g3 = 0, b3 = 0;
				}

				if(theButton[sShop1]->isInside(x, y))
				{
					CPlayState::Instance()->theStall[0]->Selected = true;
					CPlayState::Instance()->theStall[1]->Selected = false;
					CPlayState::Instance()->theStall[2]->Selected = false;
				}
				if(theButton[sShop2]->isInside(x, y))
				{
					CPlayState::Instance()->theStall[0]->Selected = false;
					CPlayState::Instance()->theStall[1]->Selected = true;
					CPlayState::Instance()->theStall[2]->Selected = false;
				}
				if(theButton[sShop3]->isInside(x, y))
				{
					CPlayState::Instance()->theStall[0]->Selected = false;
					CPlayState::Instance()->theStall[1]->Selected = false;
					CPlayState::Instance()->theStall[2]->Selected = true;
				}

				//No. of mask setting
				if(theButton[fifty]->isInside(x, y))
				{
					ChangeColor();
					if(!(CPlayState::Instance()->maskInStock < 50))
					{
						if(CPlayState::Instance()->theStall[0]->Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
						else if(CPlayState::Instance()->theStall[1]->Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
						else if(CPlayState::Instance()->theStall[2]->Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
					}
				}
				if(theButton[hundred]->isInside(x, y))
				{
					ChangeColor();
					if(!(CPlayState::Instance()->maskInStock < 100))
					{
						if(CPlayState::Instance()->theStall[0]->Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
						else if(CPlayState::Instance()->theStall[1]->Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
						else if(CPlayState::Instance()->theStall[2]->Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
					}
				}
				if(theButton[twohundred]->isInside(x, y))
				{
					ChangeColor();
					if(!(CPlayState::Instance()->maskInStock < 200))
					{
						if(CPlayState::Instance()->theStall[0]->Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
						else if(CPlayState::Instance()->theStall[1]->Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
						else if(CPlayState::Instance()->theStall[2]->Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
					}
				}

				//Price setting
				if(theButton[ten]->isInside(x, y))
				{
					ChangeColor();
					if(CPlayState::Instance()->theStall[0]->Selected)
					{
						CPlayState::Instance()->theStall[0]->setMaskPrice(10);
						ChangeColor();
					}
					else if(CPlayState::Instance()->theStall[1]->Selected)
					{
						CPlayState::Instance()->theStall[1]->setMaskPrice(10);
					}
					else if(CPlayState::Instance()->theStall[2]->Selected)
						CPlayState::Instance()->theStall[2]->setMaskPrice(10);
				}
				if(theButton[twelve]->isInside(x, y))
				{
					ChangeColor();
					if(CPlayState::Instance()->theStall[0]->Selected)
						CPlayState::Instance()->theStall[0]->setMaskPrice(12);
					else if(CPlayState::Instance()->theStall[1]->Selected)
						CPlayState::Instance()->theStall[1]->setMaskPrice(12);
					else if(CPlayState::Instance()->theStall[2]->Selected)
						CPlayState::Instance()->theStall[2]->setMaskPrice(12);
				}
				if(theButton[fifteen]->isInside(x, y))
				{
					ChangeColor();
					if(CPlayState::Instance()->theStall[0]->Selected)
						CPlayState::Instance()->theStall[0]->setMaskPrice(15);
					else if(CPlayState::Instance()->theStall[1]->Selected)
						CPlayState::Instance()->theStall[1]->setMaskPrice(15);
					else if(CPlayState::Instance()->theStall[2]->Selected)
						CPlayState::Instance()->theStall[2]->setMaskPrice(15);
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

}

void CStartOfDayState::drawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			//print shop number
			glColor3f(0.8f, 0.1f, 0.1f);
			printw (150, 70, 0, "Click the shops and decide the number of mask and price for sell.");
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (100, 120, 0, "SHOP1");
			printw (350, 120, 0, "SHOP2");
			printw (600, 120, 0, "SHOP3");

			glColor3f( r, 0.0f, b);
			printw (50.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[0]->getMaskNo());
			printw (50.0, 270.0, 0, "Each price for sell: %d", CPlayState::Instance()->theStall[0]->getMaskPrice());

			glColor3f( r2, g2, b2);
			printw (300.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[1]->getMaskNo());
			printw (300.0, 270.0, 0, "Each price for sell: %d", CPlayState::Instance()->theStall[1]->getMaskPrice());

			glColor3f( r3, g3, b3);
			printw (550.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[2]->getMaskNo());
			printw (550.0, 270.0, 0, "Each price for sell: %d", CPlayState::Instance()->theStall[2]->getMaskPrice());

			glColor3f( 0.0f, 0.0f, 0.0f);
			if(mouseOverReset)
				printw (static_cast<float>(theButton[reset]->getButtonX()),static_cast<float>(theButton[reset]->getButtonY()) , 0, "Reset");
			if(mouseOverBack)
				printw (static_cast<float>(theButton[back]->getButtonX()),static_cast<float>(theButton[reset]->getButtonY()) , 0, "Back");

			printw (50, 350, 0, "Number of mask for sell");
			printw (SCREEN_WIDTH/2 + 80, 350, 0, "Price of each mask for sell");

			glColor3f( 1.0f, 0.5f, 0.2f);
			printw (50, SCREEN_HEIGHT/2 + 180, 0, "Weather Forecast: %d - %d - %d", 50*(CPlayState::Instance()->forecasting->getCurrentDayRange()-1)+1 , (CPlayState::Instance()->forecasting->getCurrentForecast()), 50*(CPlayState::Instance()->forecasting->getCurrentDayRange()) );
			
			glColor3f( 0.5f, 0.0f, 0.5f);
			printw (SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT/2 +180, 0, "Mask in Stock: %d", CPlayState::Instance()->maskInStock);

		glPopAttrib();
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
