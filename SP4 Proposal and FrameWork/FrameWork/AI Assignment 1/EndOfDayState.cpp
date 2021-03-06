#include "EndOfDayState.h"
#include "PlayState.h"
#include "SaveState.h"
#include "LoadState.h"
#include "BuyMaskState.h"
#include "TextureSingleton.h"

CEndOfDayState * CEndOfDayState::theEndOfDayState = NULL;

void CEndOfDayState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	background[0].texID = theInstance->GetNumber(6);
	background[1].texID = theInstance->GetNumber(7);

	button[0].texID = theInstance->GetNumber(39);
	button[1].texID = theInstance->GetNumber(9);
	for (int i = 2; i < 5; i++)
	{
		button[i].texID = theInstance->GetNumber(i + 23-2);
	}
}
void CEndOfDayState::LoadButtons()
{
	theButton[save] = new CButtons(SCREEN_WIDTH/2 - 350, SCREEN_HEIGHT - 100, 300, 80, save);
	theButton[save]->setButtonTexture(button[0].texID);

	theButton[eNext] = new CButtons(SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT - 100, 300, 80, eNext);
	theButton[eNext]->setButtonTexture(button[1].texID);

	theButton[eShop1] = new CButtons(30 + 50, 100, 90, 64, eShop1);
	theButton[eShop1]->setButtonTexture(button[2].texID);

	theButton[eShop2] = new CButtons(SCREEN_WIDTH/2 - 50, 100, 90, 64, eShop2);
	theButton[eShop2]->setButtonTexture(button[3].texID);

	theButton[eShop3] = new CButtons(SCREEN_WIDTH - 170, 100, 90, 64, eShop3);
	theButton[eShop3]->setButtonTexture(button[4].texID);
}

void CEndOfDayState::Init()
{
	for (int i = 0; i < 4; i++)
	{
		theButton[i] = NULL;
	}

	sound = NULL;

	se = NULL;

	thisState = EndofDayState;

	se = createIrrKlangDevice();
	LoadTextures();
	LoadButtons();
	mouseOverNext = false;
	font_style = GLUT_BITMAP_HELVETICA_18;
	//Input System
	CInputSystem::getInstance()->OrientCam = true;
}

void CEndOfDayState::Cleanup()
{}

void CEndOfDayState::Pause()
{}

void CEndOfDayState::Resume()
{}

void CEndOfDayState::HandleEvents(CInGameStateManager* theGSM)
{
}

void CEndOfDayState::Update(CInGameStateManager* theGSM) 
{
	keyboardUpdate();
}

void CEndOfDayState::Draw(CInGameStateManager* theGSM) 
{
	Camera::getInstance()->SetHUD(true);
	DrawBackground();
	DrawButtons();
	drawInfo();
	Camera::getInstance()->SetHUD(false);
}

void CEndOfDayState::DrawButtons()
{
	theButton[save]->drawButton();
	theButton[eNext]->drawButton();
	theButton[eShop1]->drawButton();
	theButton[eShop2]->drawButton();
	theButton[eShop3]->drawButton();
}

void CEndOfDayState::DrawBackground()
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

	//three rectangle
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glPushMatrix();
			glTranslatef(25, 20, 0);
			glScalef((static_cast<GLfloat>(0.25)), (static_cast<GLfloat>(0.4)), 1);
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
			glTranslatef(SCREEN_WIDTH/2 - 100, 20, 0);
			glScalef((static_cast<GLfloat>(0.25)), (static_cast<GLfloat>(0.4)), 1);
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
			glTranslatef(SCREEN_WIDTH - 230, 20, 0);
			glScalef((static_cast<GLfloat>(0.25)), (static_cast<GLfloat>(0.4)), 1);
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

	if(theButton[eNext]->isInside(x, y))
		mouseOverNext = true;
	else
		mouseOverNext = false;
}

void CEndOfDayState::MouseClick(int button, int state, int x, int y) {
	switch (button) {

		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) 
			{
				se->play2D("audio/click.wav",false);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//save the game
				if(theButton[save]->isInside(x, y))
					CGameStateManager::getInstance()->ChangeState(CSaveState::Instance());

				//back to buyMaskState
				if(theButton[eNext]->isInside(x, y))
				{
					if(!reinit) {
						CPlayState::Instance()->forecasting->setCurrentDay(CPlayState::Instance()->forecasting->getCurrentDay() + 1);
						CPlayState::Instance()->day = CPlayState::Instance()->forecasting->getCurrentDay();
						reinit = true;
					}
					if (CLoadState::Instance()->getLoaded())
						CLoadState::Instance()->getLoadData()->off();
					CPlayState::Instance()->firstDay = false;
					CPlayState::Instance()->maskInStock = 0;
					CPlayState::Instance()->resetValues();
					if(CPlayState::Instance()->day <= 7)
						CInGameStateManager::getInstance()->ChangeState(CBuyMaskState::Instance());
					else {
						EndGameState::Instance()->SetMoney(CPlayState::Instance()->newMoneyValue);
						CGameStateManager::getInstance()->ChangeState(EndGameState::Instance());
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

void CEndOfDayState::MouseWheel(int button, int dir, int x, int y) {

}

void CEndOfDayState::drawInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			//print shop number
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw (80, 80, 0, "SHOP1");
			printw (50, 200, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[0]->getTotalMaskSold());
			printw (50, 230, 0, "Money Earned: $%d", CPlayState::Instance()->earned);

			printw (350, 80, 0, "SHOP2");
			printw (320, 200, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[1]->getTotalMaskSold());
			printw (320, 230, 0, "Money Earned: $%d", CPlayState::Instance()->earned2);

			printw (630, 80, 0, "SHOP3");
			printw (600, 200, 0, "Mask Sold: %d", CPlayState::Instance()->theStall[2]->getTotalMaskSold());
			printw (600, 230, 0, "Money Earned: $%d", CPlayState::Instance()->earned3);

			int totalEarn = CPlayState::Instance()->earned + CPlayState::Instance()->earned2 + CPlayState::Instance()->earned3;
			printw ((SCREEN_WIDTH/2)-150, SCREEN_HEIGHT/2 + 50, 0, "Total Money Earned Today: $%d", totalEarn); //

			if(mouseOverNext && CPlayState::Instance()->day < 7)
				printw ( static_cast<float>(theButton[eNext]->getButtonX()+50), static_cast<float>(theButton[eNext]->getButtonY()-3), 0, "Start next day");
			
			glColor3f( 0.5f, 0.0f, 0.8f);
			CPlayState::Instance()->newMoneyValue = CPlayState::Instance()->theMoney.getCurrentMoney() + totalEarn;
			printw ((SCREEN_WIDTH/2)+50, SCREEN_HEIGHT/2 + 150, 0, "Total Money: $%d", CPlayState::Instance()->newMoneyValue); //
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

