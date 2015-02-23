#include "BuyMaskState.h"
#include "PlayState.h"
#include "StartOfDayState.h"

CBuyMaskState CBuyMaskState::theBuyMaskState;

void CBuyMaskState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/buyMaskState/next.tga");
}
void CBuyMaskState::LoadButtons()
{
	//buttons
	theButton[nextPage] = new CButtons(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 100, 200, 100, nextPage);
	theButton[nextPage]->setButtonTexture(button[0].texID);
}

void CBuyMaskState::Init()
{
	cout << "CBuyMaskState::Init\n" << endl;

	LoadTextures();
	LoadButtons();
	font_style = GLUT_BITMAP_HELVETICA_18;
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
					CInGameStateManager::getInstance()->ChangeState(CStartOfDayState::Instance());
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
			//print shop number
			glColor3f( 0.0f, 0.0f, 0.0f);
			printw ((SCREEN_WIDTH/2)-200, 50, 0, "Prepare to earn, Buy the mask!!");
			printw ((SCREEN_WIDTH / 2) - 200, SCREEN_HEIGHT/2, 0, "Mask in Stock: %d", 0);
			printw ((SCREEN_WIDTH/2)+50, SCREEN_HEIGHT/2, 0, "$: %d", 0);

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


