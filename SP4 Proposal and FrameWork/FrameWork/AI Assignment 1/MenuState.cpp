#include "MenuState.h"
#include "PlayState.h"
#include "LoadState.h"
#include "helpState.h"
#include "TextureSingleton.h"

CMenuState CMenuState::theMenuState;

void CMenuState::LoadTextures()
{
	TextureSingleton * theTex = TextureSingleton::getInstance();

	background[1].texID = theTex->GetNumber(0);
	button[0].texID = theTex->GetNumber(2);
	button[1].texID = theTex->GetNumber(3);
	button[2].texID = theTex->GetNumber(4);
	button[3].texID = theTex->GetNumber(5);
}

void CMenuState::LoadButtons()
{
	//buttons
	theButton[start] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 400, 300, 80, start);
	theButton[start]->setButtonTexture(button[0].texID);
	
	theButton[loadGame] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 300, 300, 80, loadGame);
	theButton[loadGame]->setButtonTexture(button[1].texID);
	
	theButton[options] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 200, 300, 80, options);
	theButton[options]->setButtonTexture(button[2].texID);
	
	theButton[quit] = new CButtons(SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT - 100, 300, 80, quit);
	theButton[quit]->setButtonTexture(button[3].texID);
}

void CMenuState::Init()
{
	cout << "CMenuState::Init\n" << endl;

	LoadTextures();
	LoadButtons();

	isPassed = false;
	skip = false;
	exponent = 0;

	turbulencenum = 64;

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Audio Player
	se = createIrrKlangDevice();
	generatenoise();
	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;
	sound = AudioPlayer::Instance();
	playSound();
}

void CMenuState::Cleanup()
{
	//cout << "CMenuState::Cleanup\n" << endl;
}

void CMenuState::Pause()
{
	//cout << "CMenuState::Pause\n" << endl;
}

void CMenuState::Resume()
{
	//cout << "CMenuState::Resume\n" << endl;
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{

}

void CMenuState::Update(CGameStateManager* theGSM) 
{
	keyboardUpdate();
	Camera::getInstance()->newUpdate();
	checkCameraPos();
	if(isPassed)
		Camera::getInstance()->Walk(0);
	else
		Camera::getInstance()->Walk(static_cast<GLfloat>(pow(10,exponent)));
	exponent+=0.01;
}

void CMenuState::checkCameraPos()
{
	Vector3 pos;
	pos.Set(0, -50, 320);
	if(skip)
		Camera::getInstance()->SetPos(Vector3(0, -50, 320));
	if(Camera::getInstance()->GetPos().z >= pos.z)
	{
		isPassed = true;
	}
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	drawMap();

	if(isPassed || skip)
	{
		Camera::getInstance()->SetHUD(true);
		DrawBackground();
		DrawButtons();
		gameTitle();
		Camera::getInstance()->SetHUD(false);
	}
}

void CMenuState::DrawButtons()
{
	theButton[start]->drawButton();
	theButton[loadGame]->drawButton();
	theButton[options]->drawButton();
	theButton[quit]->drawButton();
}

void CMenuState::DrawBackground()
{
	glPushMatrix();
	double t = timeGetTime() / 40.0;
	int number = SCREEN_WIDTH / mWidth;
	int number2 = SCREEN_HEIGHT/ mHeight;
	for (int i = 0; i < (mHeight - 1 * number2); ++i)
	{
		glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);					//BEGIN DRAWING OF THE NOISE POOL.
		for (int k = 0; k < mWidth * number; ++k)
		{
			double nextB;
			double inter = turbulence(k, i, t, turbulencenum);

			nextB = turbulence(k, i + 1, t, turbulencenum);

			blue =   (static_cast<float>(inter / 2));

			Rh = 23, Gs = 5, Bl = 100 - blue;	//SET HSL COLORS. USING HSL BECAUSE IT IS EASIER TO MOVE THE COLORS AROUND FROM BLUE TO WHITE
			HSLtoRGB(Rh, Gs, Bl);	//CONVERT FROM HSL TO RGB
			glColor3f(Rh, Gs, Bl);
			glVertex2f((static_cast<GLfloat>(k * number2)), (static_cast<GLfloat>(i  * number)));
			glVertex2f((static_cast<GLfloat>(k * number2)), (static_cast<GLfloat>((i + 1) * number)));
		}
		glEnd();
		glPopMatrix();
	}
	glColor3f(1, 1, 1);
	glPopMatrix();
}

//HSL: Hue, Saturation, lightness
void CMenuState::HSLtoRGB(float &Rh, float &Gs, float &Bl)
{
	//float min, max;
	Gs /= 100;
	Bl /= 100;
	float R, G, B;
	//IF NO SATURATION, ITS GREY.
	if (Gs == 0)
	{
		R = Bl * 255;
		G = Bl * 255;
		B = Bl * 255;
	}
	else
	{
		float temp1;
		float temp2;
		//USE RIGHT FORMULA TO FIND RGB
		if (Bl < 0.5)
		{
			temp1 = Bl * (static_cast<float>((1.0 + Gs)) );
		}
		else if (Bl >= (static_cast<float>(0.5)) )
		{
			temp1 = Bl + Gs - Bl * Gs;
		}
		temp2 = 2 * Bl - temp1;
		
		Rh /= 360;

		R = Rh + static_cast<float>(0.333);
		G = Rh;
		B = Rh - static_cast<float>(0.333);

		//SET ALL VALUES TO BETWEEN 0 AND 1
		if (R > 1)
			R -= 1;
		else if (R < 1)
			R += 1;
		if (G > 1)
			G -= 1;
		else if (G < 1)
			G += 1;
		if (B > 1)
			B -= 1;
		else if (B < 1)
			B += 1;
		//NOW START TO FIND THE NUMBERS FOR RGB WITH THESE TESTS. 3 TESTS TO DETERMINE WHAT FORMULA TO USE
		//RED SEARCH
		if (6 * R < 1)
		{
			R = temp2 + (temp1 - temp2) * 6 * R;
		}
		else if (2 * R < 1)
		{
			R = temp1;
		}
		else if (3 * R < 2)
		{
			R = temp2 + (temp1 - temp2) * static_cast<float>(0.6666 - R) * 6;
		}
		else
		{
			R = temp2;
		}
		//NOW DO BLUE
		if (6 * B < 1)
		{
			B = temp2 + (temp1 - temp2) * 6 * B;
		}
		else if (2 * B < 1)
		{
			B = temp1;
		}
		else if (3 * B < 2)
		{
			B = temp2 + (temp1 - temp2) * static_cast<float>(0.6666 - B) * 6;
		}
		else
		{
			B = temp2;
		}
		//NOW DO GREEN
		if (6 * G < 1)
		{
			G = temp2 + (temp1 - temp2) * 6 * G;
		}
		else if (2 * G < 1)
		{
			G = temp1;
		}
		else if (3 * G < 2)
		{
			G = temp2 + (temp1 - temp2) * static_cast<float>(0.6666 - G) * 6;
		}
		else
		{
			G = temp2;
		}
		//NOW RGB IS REALLY RGB IN DECIMAL FORM. 
		Rh = R; Gs = G; Bl = B;
	}
}

//The effects
double CMenuState::turbulence(double x, double y, double z, double size)
{
	double value = 0.0, initialSize = size;

	while (size >= 1)		//ADD TOGETHER ALL THE ZOOMS TO MAKE TURBULANCE
	{
		value += interpolation(x / size, y / size, z / size) * size;
		size /= 2.0;
	}

	return((128.0 * value / initialSize));
}

//the values of the turbulence
double CMenuState::interpolation(double x, double y, double z)
{
	//get fractional part of x and y
	double fractX = x - int(x);
	double fractY = y - int(y);
	double fractZ = z - int(z);

	//wrap around
	int x1 = (int(x) + mWidth) % mWidth;
	int y1 = (int(y) + mHeight) % mHeight;
	int z1 = (int(z) + mDepth) % mDepth;

	//neighbor values
	int x2 = (x1 + mWidth - 1) % mWidth;
	int y2 = (y1 + mHeight - 1) % mHeight;
	int z2 = (z1 + mDepth - 1) % mDepth;

	//smooth the noise with bilinear interpolation
	double value = 0.0;
	value += fractX       * fractY       * fractZ       * noise[x1][y1][z1];
	value += fractX       * (1 - fractY) * fractZ       * noise[x1][y2][z1];
	value += (1 - fractX) * fractY       * fractZ       * noise[x2][y1][z1];
	value += (1 - fractX) * (1 - fractY) * fractZ       * noise[x2][y2][z1];

	value += fractX       * fractY       * (1 - fractZ) * noise[x1][y1][z2];
	value += fractX       * (1 - fractY) * (1 - fractZ) * noise[x1][y2][z2];
	value += (1 - fractX) * fractY       * (1 - fractZ) * noise[x2][y1][z2];
	value += (1 - fractX) * (1 - fractY) * (1 - fractZ) * noise[x2][y2][z2];

	return value;
}

void CMenuState::drawMap()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(0.5f, 0.5f, 1);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(-210, -300, -260);
		glBindTexture(GL_TEXTURE_2D, map[0].texID);
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1);  glVertex3f(0, 0.0f, 420);
			glTexCoord2f(0, 1);  glVertex3f(420, 0.0f, 420); 
			glTexCoord2f(0, 0);	 glVertex3f(420, 0.0f, 0);
			glTexCoord2f(1, 0);	 glVertex3f(0, 0.0f, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CMenuState::gameTitle()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[1].texID);
		glTranslatef(SCREEN_WIDTH/2 - 235, 100, 0);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);	glVertex2f(0, 75);
				glTexCoord2f(1, 0);	glVertex2f(470, 75);
				glTexCoord2f(1, 1);	glVertex2f(470, 0);
				glTexCoord2f(0, 1);	glVertex2f(0, 0);			
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CMenuState::keyboardUpdate()
{
	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
}

//Inputs
void CMenuState::MouseMove (int x, int y) {
	InputSystem->mouseInfo.lastX = x;
	InputSystem->mouseInfo.lastY = y;
}

void CMenuState::MouseClick(int button, int state, int x, int y) {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	switch (button) {
		case GLUT_LEFT_BUTTON:
			
			if (state == GLUT_DOWN)
			{
				skip = true;
				se->play2D("audio/click.wav",false);
				InputSystem->mouseInfo.mLButtonUp = false;
				InputSystem->mouseInfo.clickedX = x;
				InputSystem->mouseInfo.clickedY = y;

				if(isPassed)
				{
					//go to start of the day
					if(theButton[start]->isInside(x, y))
					{
						CGameStateManager::getInstance()->ChangeState(CPlayState::Instance());
					}

					//load game
					if(theButton[loadGame]->isInside(x, y))
						CGameStateManager::getInstance()->ChangeState(CLoadState::Instance());

					if (theButton[options]->isInside(x,y))
						CGameStateManager::getInstance()->ChangeState(helpState::Instance());

					//quit game
					if(theButton[quit]->isInside(x, y))
						exit(0);
				}
			}
			else
				InputSystem->mouseInfo.mLButtonUp = true;
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

void CMenuState::MouseWheel(int button, int dir, int x, int y) {
}

void CMenuState::playSound()
{
	sound->setFileName("audio/Sims.mp3");
	sound->playSoundThreaded();
}

void CMenuState::generatenoise()
{
	for (int x = 0; x < mWidth; ++x)
	{
		for (int y = 0; y < mHeight; ++y)
		{
			for (int z = 0; z < mDepth; ++z)
			{
				noise[x][y][z] = (rand() % 32768) / 32768.0;	//GEN BETWEEN  0 AND 1
			}
		}
	}
}