#include "EndGameState.h"

EndGameState *EndGameState::singleton = NULL;

EndGameState::EndGameState(void)
{
}

EndGameState::~EndGameState(void)
{
	Drop();
}

void EndGameState::Drop()
{
	if (sound != NULL)
	{
		delete sound;
		sound = NULL;
	}
}

void EndGameState::outcome ()
{
	profitLoss->calcOutcome(money);
	result = profitLoss->GetResult();
	if (result == true)
	{
		sound->setFileName("audio/win.mp3");
	}
	else
	{
		sound->setFileName("audio/lose.mp3");
	}

}

void EndGameState::SetMoney(int money)
{
	this->money = money;
}

void EndGameState::LoadTextures()
{
	TextureSingleton * theInstance = TextureSingleton::getInstance();
	background[0].texID = theInstance->GetNumber(40);
	background[1].texID = theInstance->GetNumber(41);
	background[2].texID = theInstance->GetNumber(51);
	highscore_text.texID = theInstance->GetNumber(52);
	highscore_box.texID = theInstance->GetNumber(53);
}

void EndGameState::DrawBackground()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,alpha);
		glEnable(GL_TEXTURE_2D);
		if(result == true)
		{
			glBindTexture(GL_TEXTURE_2D, background[0].texID);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, background[1].texID);
		}
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

void EndGameState::DrawHighscore()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background[2].texID);
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

		for (auto i = highscore.HighScoreList.begin(); i != highscore.HighScoreList.end(); i++)
		{
			glPushMatrix();
				glColor3f(1,1,1);
				printw (50, SCREEN_HEIGHT/2+(i - highscore.HighScoreList.begin())*20, 0, "\nUsername:\t%s\tHighScore:\t%i", (*i).User.c_str(), (*i).HighScore);
			glPopMatrix();
		}

		if(KeyInHighscore)
		{
			glPushMatrix();
				glColor3f(1,1,1);
				printw (80, SCREEN_HEIGHT/3, 0, "\nUsername:\t%s\tHighScore:\t%i", input.c_str(), profit);
			glPopMatrix();
		}
	glPopMatrix();
}

void EndGameState::Init()
{
	LoadTextures();
	profitLoss = new WinLose();
	profit = money - StartMoney;
	font_style = GLUT_BITMAP_HELVETICA_18;

	//Audio Player
	sound = AudioPlayer::Instance();
	outcome();
	sound->playSoundThreaded();
	alpha = 0.0f;
	KeyInHighscore = false;
	drawHighscore = false;
	doneInput = false;
	
	Speed = 2;
	Dir = 1;
	input = "PLAYER";
}

void EndGameState::Pause()
{

}

void EndGameState::Resume()
{

}

void EndGameState::HandleEvents(CGameStateManager * GSM)
{

}

void EndGameState::Update(CGameStateManager * GSM)
{
	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);

	alpha += Speed * Dir * CTimer::getInstance()->getDelta();
	if(alpha > 1)
	{
		alpha = 1;
		Dir *= -1;
	}
	else if(alpha < 0)
	{
		alpha = 0;
		Dir *= 0;
	}

	//Input mode
	if(Dir == 0)
	{
		if(!doneInput) {
			for (auto i = highscore.HighScoreList.begin(); i != highscore.HighScoreList.end(); i++)
			{
				if(profit >= (*i).HighScore) {
					KeyInHighscore = true;
					break;
				}
			}
		}
		drawHighscore = true;
	}

	if(KeyInHighscore){
		if(!doneInput)
			InputUsername();
	}

}

void EndGameState::Draw(CGameStateManager * GSM)
{
		Camera::getInstance()->SetHUD(true);
			DrawBackground();
			if(drawHighscore)
				DrawHighscore();
		Camera::getInstance()->SetHUD(false);
}

void EndGameState::MouseMove (int x, int y)
{

}

void EndGameState::MouseClick(int button, int state, int x, int y)
{
}

void EndGameState::MouseWheel(int button, int dir, int x, int y)
{

}

void EndGameState::printw (float x, float y, float z, char* format, ...)
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

void EndGameState::InputUsername()
{
	if(CInputSystem::getInstance()->myKeys[VK_BACK] && input.size() > 0) {
		input.pop_back();
		CInputSystem::getInstance()->myKeys[VK_BACK] = false;
	}
	if(CInputSystem::getInstance()->myKeys[VK_RETURN] && input.size() > 0){
		SetHighscore(input);
		KeyInHighscore = false;
		doneInput = true;
		CInputSystem::getInstance()->myKeys[VK_RETURN] = false;
	}
	for(int i = 32; i < 127; i++)
	{
		if(CInputSystem::getInstance()->myKeys[i] && input.size() < 25) {
			input.push_back(i);
			CInputSystem::getInstance()->myKeys[i] = false;
		}
	}
}

void EndGameState::SetHighscore(string username)
{
	highscore.InsertHighScore(profit,input);
	highscore.SaveHighScore();
}

