#include "EndGameState.h"


EndGameState::EndGameState(void)
{
	result = false;
	outcome();
}


EndGameState::~EndGameState(void)
{
}


void EndGameState::outcome ()
{
	result = profitLoss->GetResult();
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