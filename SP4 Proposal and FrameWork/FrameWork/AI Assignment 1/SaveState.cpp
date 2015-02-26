#include "SaveState.h"
#include "PlayState.h"
#include "EndOfDayState.h"

CSaveState CSaveState::theSaveState;


void CSaveState::LoadTextures()
{
	//Textures
	CApplication::getInstance()->LoadTGA(&background[0],"images/background.tga");
	CApplication::getInstance()->LoadTGA(&button[0],"images/buyMaskState/box.tga");
	CApplication::getInstance()->LoadTGA(&button[1],"images/startState/back.tga");
}
void CSaveState::LoadButtons()
{
	//buttons
	theButton[save1] = new CButtons(SCREEN_WIDTH/2 - 150, 200, 350, 100, save1);
	theButton[save1]->setButtonTexture(button[0].texID);
	
	theButton[save2] = new CButtons(SCREEN_WIDTH/2 - 150, 300, 350, 100, save2);
	theButton[save2]->setButtonTexture(button[0].texID);
	
	theButton[save3] = new CButtons(SCREEN_WIDTH/2 - 150, 400, 350, 100, save3);
	theButton[save3]->setButtonTexture(button[0].texID);
	
	theButton[back] = new CButtons(0, 0, 64, 64, back);
	theButton[back]->setButtonTexture(button[1].texID);
}
void CSaveState::LoadLoadData()
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
void CSaveState::UpdateLoadData()
{
	loadedFiles[0]->Load("save01.txt");

	loadedFiles[1]->Load("save02.txt");

	loadedFiles[2]->Load("save03.txt");
}

void CSaveState::Init()
{
	cout << "CSaveState::Init\n" << endl;

	LoadTextures();
	LoadButtons();
	LoadLoadData();
	font_style = GLUT_BITMAP_HELVETICA_18;

	//Enable Camera Orientation on Mouse Move
	CInputSystem::getInstance()->OrientCam = true;

}

void CSaveState::Cleanup()
{
	//cout << "CSaveState::Cleanup\n" << endl;
	/*if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}*/
}

void CSaveState::Pause()
{
	//cout << "CSaveState::Pause\n" << endl;
}

void CSaveState::Resume()
{
	//cout << "CSaveState::Resume\n" << endl;
}

void CSaveState::HandleEvents(CGameStateManager* theGSM)
{

}

void CSaveState::Update(CGameStateManager* theGSM) 
{
	//cout << "CSaveState::Update\n" << endl;
	keyboardUpdate();

	
	UpdateLoadData();
}

void CSaveState::Draw(CGameStateManager* theGSM) 
{
	Camera::getInstance()->SetHUD(true);

	DrawBackground();
	DrawButtons();
	DrawLoadInfo();
	Camera::getInstance()->SetHUD(false);
}

void CSaveState::DrawLoadInfo()
{
	glPushMatrix();
		glPushAttrib(GL_DEPTH_TEST);

			glColor3f( 0.0f, 0.0f, 0.0f);
			if (loadedFiles[0]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 150, 225.0, 0, "Day: %d", loadedFiles[0]->getDay());
			printw (SCREEN_WIDTH/2 - 150, 275.0, 0, "Money: %d", loadedFiles[0]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 150, 225.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 150, 275.0, 0, "Money: ---");
			}

			if (loadedFiles[1]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 150, 325.0, 0, "Day: %d", loadedFiles[1]->getDay());
			printw (SCREEN_WIDTH/2 - 150, 375.0, 0, "Money: %d", loadedFiles[1]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 150, 325.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 150, 375.0, 0, "Money: ---");
			}

			if (loadedFiles[2]->getHere())
			{
			printw (SCREEN_WIDTH/2 - 150, 425.0, 0, "Day: %d", loadedFiles[2]->getDay());
			printw (SCREEN_WIDTH/2 - 150, 475.0, 0, "Money: %d", loadedFiles[2]->getMoney());
			}
			else
			{
			printw (SCREEN_WIDTH/2 - 150, 425.0, 0, "Day: ---");
			printw (SCREEN_WIDTH/2 - 150, 475.0, 0, "Money: ---");
			}

		glPopAttrib();
	glPopMatrix();
}

void CSaveState::DrawButtons()
{
	theButton[save1]->drawButton();
	theButton[save2]->drawButton();
	theButton[save3]->drawButton();
	theButton[back]->drawButton();
}

void CSaveState::DrawBackground()
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

void CSaveState::keyboardUpdate()
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
}

//Inputs
void CSaveState::MouseMove (int x, int y) {
	CInputSystem::getInstance()->mouseInfo.lastX = x;
	CInputSystem::getInstance()->mouseInfo.lastY = y;
}

void CSaveState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	se = createIrrKlangDevice();

	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				se->play2D("audio/click.wav",false);
				CInputSystem::getInstance()->mouseInfo.mLButtonUp = false;
				CInputSystem::getInstance()->mouseInfo.clickedX = x;
				CInputSystem::getInstance()->mouseInfo.clickedY = y;

				//load files
				if(theButton[save1]->isInside(x, y))
					loadedFiles[0]->overwriteData("save01.txt", CPlayState::Instance()->day,CPlayState::Instance()->theMoney.getCurrentMoney(), CPlayState::Instance()->maskInStock);
					
				if(theButton[save2]->isInside(x, y))
					loadedFiles[1]->overwriteData("save02.txt", CPlayState::Instance()->day,CPlayState::Instance()->theMoney.getCurrentMoney(), CPlayState::Instance()->maskInStock);
					
				if(theButton[save3]->isInside(x, y))
					loadedFiles[2]->overwriteData("save03.txt", CPlayState::Instance()->day,CPlayState::Instance()->theMoney.getCurrentMoney(), CPlayState::Instance()->maskInStock);
					

				//go back
				if(theButton[back]->isInside(x, y))
					CGameStateManager::getInstance()->PopState();

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

void CSaveState::MouseWheel(int button, int dir, int x, int y) {

	if (dir > 0) {//Zoom In
		/*if(camDist-zoomSpeed*15 > 0)
			camDist -= zoomSpeed;*/
		Vector3 temp = Camera::getInstance()->GetPosition() + Camera::getInstance()->GetDirection();
		Camera::getInstance()->SetPosition(temp.x,temp.y,temp.z);
	}
    else {//Zoom Out
		//camDist += zoomSpeed;
		Vector3 temp = Camera::getInstance()->GetPosition() - Camera::getInstance()->GetDirection();
		Camera::getInstance()->SetPosition(temp.x,temp.y,temp.z);
	}
}

void CSaveState::printw (float x, float y, float z, char* format, ...)
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