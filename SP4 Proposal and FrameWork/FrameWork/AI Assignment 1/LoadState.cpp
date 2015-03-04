#include "LoadState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "TextureSingleton.h"

CLoadState *CLoadState::theLoadState = NULL;

CSaveLoad* CLoadState::getLoadData()
{
	return loadedFiles[saveNum-1];	
}
bool CLoadState::getLoaded()
{
	if (saveNum > 0)
	{
		return loadedFiles[saveNum-1]->getHere();
	}
	else
		return false;
}
bool CLoadState::skipThis()
{
	return true;
}


void CLoadState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	background[0].texID = theInstance->GetNumber(38);
	button[0].texID = theInstance->GetNumber(13);
	button[1].texID = theInstance->GetNumber(21);
}
void CLoadState::LoadButtons()
{
	theButton[load1] = new CButtons(SCREEN_WIDTH/2 - 150, 200, 350, 100, load1);
	theButton[load1]->setButtonTexture(button[0].texID);
	
	theButton[load2] = new CButtons(SCREEN_WIDTH/2 - 150, 300, 350, 100, load2);
	theButton[load2]->setButtonTexture(button[0].texID);
	
	theButton[load3] = new CButtons(SCREEN_WIDTH/2 - 150, 400, 350, 100, load3);
	theButton[load3]->setButtonTexture(button[0].texID);
	
	theButton[backToMenu] = new CButtons(0, 0, 64, 64, backToMenu);
	theButton[backToMenu]->setButtonTexture(button[1].texID);
}
void CLoadState::LoadLoadData()
{
	loadedFiles[0] = new CSaveLoad();
	loadedFiles[0]->init();

	loadedFiles[0]->Load("save01.txt");

	loadedFiles[1] = new CSaveLoad();
	loadedFiles[1]->init();

	loadedFiles[1]->Load("save02.txt");

	loadedFiles[2] = new CSaveLoad();
	loadedFiles[2]->init();

	loadedFiles[2]->Load("save03.txt");
}

void CLoadState::Init()
{
	se = createIrrKlangDevice();
	LoadTextures();
	LoadButtons();
	LoadLoadData();

	saveNum = 0;

	font_style = GLUT_BITMAP_HELVETICA_18;

	//Enable Camera Orientation on Mouse Move
	CInputSystem::getInstance()->OrientCam = true;

}

void CLoadState::Cleanup()
{}

void CLoadState::Pause()
{}

void CLoadState::Resume()
{}

void CLoadState::HandleEvents(CGameStateManager* theGSM)
{}

void CLoadState::Update(CGameStateManager* theGSM) 
{
	keyboardUpdate();
}

void CLoadState::Draw(CGameStateManager* theGSM) 
{
	Camera::getInstance()->SetHUD(true);

	DrawBackground();
	DrawButtons();
	DrawLoadInfo();
	Camera::getInstance()->SetHUD(false);
}

void CLoadState::DrawLoadInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);
			glColor3f( 0.0f, 0.0f, 0.0f);
			if (loadedFiles[0]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 140, 225.0, 0, "Day: %d", loadedFiles[0]->getDay());
			printw (SCREEN_WIDTH/2 - 140, 275.0, 0, "Money: %d", loadedFiles[0]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 140, 225.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 140, 275.0, 0, "Money: ---");
			}

			if (loadedFiles[1]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 140, 325.0, 0, "Day: %d", loadedFiles[1]->getDay());
			printw (SCREEN_WIDTH/2 - 140, 375.0, 0, "Money: %d", loadedFiles[1]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 140, 325.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 140, 375.0, 0, "Money: ---");
			}

			if (loadedFiles[2]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 140, 425.0, 0, "Day: %d", loadedFiles[2]->getDay());
			printw (SCREEN_WIDTH/2 - 140, 475.0, 0, "Money: %d", loadedFiles[2]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 140, 425.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 140, 475.0, 0, "Money: ---");

			}
		glPopAttrib();
	glPopMatrix();
}

void CLoadState::DrawButtons()
{
	theButton[load1]->drawButton();
	theButton[load2]->drawButton();
	theButton[load3]->drawButton();
	theButton[backToMenu]->drawButton();
}

void CLoadState::DrawBackground()
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

void CLoadState::keyboardUpdate()
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}

//Inputs
void CLoadState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CLoadState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				se->play2D("audio/click.wav",false);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//load files
				if(theButton[load1]->isInside(x, y) && loadedFiles[0]->getHere())
				{
					saveNum = 1;
					CGameStateManager::getInstance()->ChangeState(CPlayState::Instance(true));
				}
				if(theButton[load2]->isInside(x, y) && loadedFiles[1]->getHere())
				{
					saveNum = 2;
					CGameStateManager::getInstance()->ChangeState(CPlayState::Instance(true));
				}
				if(theButton[load3]->isInside(x, y) && loadedFiles[2]->getHere())
				{
					saveNum = 3;
					CGameStateManager::getInstance()->ChangeState(CPlayState::Instance(true));
				}

				//go back
				if(theButton[backToMenu]->isInside(x, y))
					CGameStateManager::getInstance()->PopState();

			}
			else
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = true;
			break;

		case GLUT_RIGHT_BUTTON:
			CGameStateManager::getInstance()->PopState();
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CLoadState::MouseWheel(int button, int dir, int x, int y) {

}

void CLoadState::printw (float x, float y, float z, char* format, ...)
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
