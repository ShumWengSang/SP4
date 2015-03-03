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

void EndGameState::Init()
{
	LoadTextures();
	profitLoss = new WinLose();

	//Audio Player
	sound = AudioPlayer::Instance();
	outcome();
	sound->playSoundThreaded();
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
}

void EndGameState::Draw(CGameStateManager * GSM)
{
		Camera::getInstance()->SetHUD(true);
			DrawBackground();
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
