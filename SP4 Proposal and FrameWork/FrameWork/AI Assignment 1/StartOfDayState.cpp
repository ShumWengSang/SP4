#include "StartOfDayState.h"
#include "GamePlayState.h"
#include "PlayState.h"
#include "BuyMaskState.h"

CStartOfDayState CStartOfDayState::theStartOfDayState;

void CStartOfDayState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&background[1],"images/startState/box.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/startState/go.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/startState/50.tga");
	CApplication::getInstance()->LoadTGA(&button[2],"images/startState/100.tga");
	CApplication::getInstance()->LoadTGA(&button[3],"images/startState/200.tga");
	CApplication::getInstance()->LoadTGA(&button[4],"images/startState/10.tga");
	CApplication::getInstance()->LoadTGA(&button[5],"images/startState/12.tga");
	CApplication::getInstance()->LoadTGA(&button[6],"images/startState/15.tga");
	CApplication::getInstance()->LoadTGA(&button[7],"images/startState/back.tga");
	CApplication::getInstance()->LoadTGA(&button[8],"images/startState/reset.tga");
	CApplication::getInstance()->LoadTGA(&button[9],"images/startState/shop.tga");
	CApplication::getInstance()->LoadTGA(&button[10],"images/startState/shop2.tga");
	CApplication::getInstance()->LoadTGA(&button[11],"images/startState/shop3.tga");
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
}

void CStartOfDayState::Init()
{
	cout << "CStartOfDayState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	font_style = GLUT_BITMAP_HELVETICA_18;
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
	drawInfo();
	CApplication::getInstance()->theCamera->SetHUD(false);
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
	theButton[sShop2]->drawButton();
	theButton[sShop3]->drawButton();

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
			glScalef(0.98, 0.5, 1);
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
			if (state == GLUT_DOWN)
			{
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//start the day
				if(theButton[go]->isInside(x, y))
				{
					CInGameStateManager::getInstance()->ChangeState(CGamePlayState::Instance());
					CPlayState::Instance()->totalMaskForSell = CPlayState::Instance()->theStall[0]->getMaskNo() + CPlayState::Instance()->theStall[1]->getMaskNo() + CPlayState::Instance()->theStall[2]->getMaskNo();
				}

				//back to buy mask
				if(theButton[back]->isInside(x, y))
					CInGameStateManager::getInstance()->PopState();

				if(theButton[reset]->isInside(x, y))
				{
					CPlayState::Instance()->maskInStock = CPlayState::Instance()->oldMaskValue;
					CPlayState::Instance()->theStall[0]->setMaskNo(0);
					CPlayState::Instance()->theStall[1]->setMaskNo(0);
					CPlayState::Instance()->theStall[2]->setMaskNo(0);
					CPlayState::Instance()->theStall[0]->setMaskPrice(0);
					CPlayState::Instance()->theStall[1]->setMaskPrice(0);
					CPlayState::Instance()->theStall[2]->setMaskPrice(0);
				}

				if(theButton[sShop1]->isInside(x, y))
				{
					shop1Selected = true;
					shop2Selected = false;
					shop3Selected = false;
				}
				if(theButton[sShop2]->isInside(x, y))
				{
					shop1Selected = false;
					shop2Selected = true;
					shop3Selected = false;
				}
				if(theButton[sShop3]->isInside(x, y))
				{
					shop1Selected = false;
					shop2Selected = false;
					shop3Selected = true;
				}
					

				//No. of mask setting
				if(theButton[fifty]->isInside(x, y))
				{
					if(!(CPlayState::Instance()->maskInStock < 50))
					{
						if(shop1Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
						else if(shop2Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
						else if(shop3Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 50);
							CPlayState::Instance()->maskInStock -= 50;
						}
					}
				}
				if(theButton[hundred]->isInside(x, y))
				{
					if(!(CPlayState::Instance()->maskInStock < 100))
					{
						if(shop1Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
						else if(shop2Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
						else if(shop3Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 100);
							CPlayState::Instance()->maskInStock -= 100;
						}
					}
				}
				if(theButton[twohundred]->isInside(x, y))
				{
					if(!(CPlayState::Instance()->maskInStock < 200))
					{
						if(shop1Selected)
						{
							CPlayState::Instance()->theStall[0]->setMaskNo(CPlayState::Instance()->theStall[0]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
						else if(shop2Selected)
						{
							CPlayState::Instance()->theStall[1]->setMaskNo(CPlayState::Instance()->theStall[1]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
						else if(shop3Selected)
						{
							CPlayState::Instance()->theStall[2]->setMaskNo(CPlayState::Instance()->theStall[2]->getMaskNo() + 200);
							CPlayState::Instance()->maskInStock -= 200;
						}
					}
				}

				//Price setting
				if(theButton[ten]->isInside(x, y))
				{
					if(shop1Selected)
						CPlayState::Instance()->theStall[0]->setMaskPrice(10);
					else if(shop2Selected)
						CPlayState::Instance()->theStall[1]->setMaskPrice(10);
					else if(shop3Selected)
						CPlayState::Instance()->theStall[2]->setMaskPrice(10);
				}
				if(theButton[twelve]->isInside(x, y))
				{
					if(shop1Selected)
						CPlayState::Instance()->theStall[0]->setMaskPrice(12);
					else if(shop2Selected)
						CPlayState::Instance()->theStall[1]->setMaskPrice(12);
					else if(shop3Selected)
						CPlayState::Instance()->theStall[2]->setMaskPrice(12);
				}
				if(theButton[fifteen]->isInside(x, y))
				{
					if(shop1Selected)
						CPlayState::Instance()->theStall[0]->setMaskPrice(15);
					else if(shop2Selected)
						CPlayState::Instance()->theStall[1]->setMaskPrice(15);
					else if(shop3Selected)
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

void CStartOfDayState::drawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			//print shop number
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (150, 70, 0, "Click the shops and decide the number of mask and price for sell.");
			printw (100, 120, 0, "SHOP1");
			printw (50.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[0]->getMaskNo());
			printw (50.0, 270.0, 0, "Price of mask for sell: %d", CPlayState::Instance()->theStall[0]->getMaskPrice());

			printw (350, 120, 0, "SHOP2");
			printw (300.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[1]->getMaskNo());
			printw (300.0, 270.0, 0, "Price of mask for sell: %d", CPlayState::Instance()->theStall[1]->getMaskPrice());

			printw (600, 120, 0, "SHOP3");
			printw (550.0, 250.0, 0, "Number of mask for sell: %d", CPlayState::Instance()->theStall[2]->getMaskNo());
			printw (550.0, 270.0, 0, "Price of mask for sell: %d", CPlayState::Instance()->theStall[2]->getMaskPrice());

			printw (50, 350, 0, "Number of mask for sell");
			printw (SCREEN_WIDTH/2 + 80, 350, 0, "Price of each mask for sell");

			glColor3f( 0.0f, 0.0f, 1.0f);
			printw (50, SCREEN_HEIGHT/2 + 180, 0, "Weather Forecast: %d - %d - %d", 50*(CPlayState::Instance()->forecasting->getCurrentDayRange()-1)+1 , (CPlayState::Instance()->forecasting->getCurrentForecast()), 50*(CPlayState::Instance()->forecasting->getCurrentDayRange()) );

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
