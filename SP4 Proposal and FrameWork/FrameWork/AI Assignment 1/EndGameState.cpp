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
	CApplication::getInstance()->LoadTGA(&background[0],"images/win.tga");
	CApplication::getInstance()->LoadTGA(&background[1],"images/lose.tga");
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
	for (auto i = highscore.HighScoreList.begin(); i != highscore.HighScoreList.end(); i++)
	{
		cout << "\nUsername:\t" << (*i).User << "\tHighScore:\t" << (*i).HighScore << endl;
		glPushMatrix();
			glColor3f(1,1,1);
			printw (50, 20+(i - highscore.HighScoreList.begin())*20, 0, "\nUsername:\t%s\tHighScore:\t%i", (*i).User.c_str(), (*i).HighScore);
		glPopMatrix();
	}
}

void EndGameState::Init()
{
	LoadTextures();
	profitLoss = new WinLose();
	profit = money - WinMoneyCondition;
	font_style = GLUT_BITMAP_HELVETICA_18;

	//Audio Player
	sound = AudioPlayer::Instance();
	outcome();
	sound->playSoundThreaded();
	time = 0.0f;
	alpha = 1.0f;
	fadein = true;
	
	/*string temp = "Anon1";
	highscore.InsertHighScore(10,temp);
	string temp = "Anon2";
	highscore.InsertHighScore(20,temp);
	temp = "Anon3";
	highscore.InsertHighScore(30,temp);*/
	highscore.SaveHighScore();
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
	if(fadein){
		if(alpha < 1){
			time+=0.1;
			alpha = pow(time,2);
		}else{
			alpha = 1;
			time = 0;
			fadein = false;
		}
	}else{
		if(alpha > 0 && time > 0){
			time+=0.01;
			alpha = 1-pow(time,2);
		}else{
			alpha = 0;
			time = -1;
		}
	}
}

void EndGameState::Draw(CGameStateManager * GSM)
{
		Camera::getInstance()->SetHUD(true);
			DrawBackground();
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

}

void EndGameState::SetHighscore(string username)
{

}

