#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "AudioPlayer.h"

using namespace std;

enum ENDSTATE_BUTTON
{
	save,
	eNext,
	eShop1,
	eShop2,
	eShop3
};

class CInputSystem;

class CEndOfDayState : public CInGameState
{
private:
	CEndOfDayState(void):reinit(false) {};

	TextureImage button[5];
	TextureImage background[2];

	bool mouseOverNext;

public:

	bool reinit;

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();
	void DrawBackground();
	void keyboardUpdate(void);
	void drawInfo();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CEndOfDayState* Instance() {
		if (theEndOfDayState == NULL)
			theEndOfDayState= new CEndOfDayState();
		return 	theEndOfDayState;
	}

	void Drop()
	{
		for (int i = 0; i < 4; i++)
		{
			if(theButton[i] != NULL)
			{
				delete theButton[i];
				theButton[i] = NULL;
			}
		}

		if (se != NULL)
		{
			delete se;
			se = NULL;
		}

		/*if (sound != NULL)
		{
			delete sound;
			sound = NULL;
		}*/

		if (theEndOfDayState != NULL)
		{
			delete theEndOfDayState;
			theEndOfDayState = NULL;
		}

	}

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

private:
	static CEndOfDayState *theEndOfDayState;
	CButtons* theButton[4];
	AudioPlayer * sound;
	ISoundEngine *se;
};

