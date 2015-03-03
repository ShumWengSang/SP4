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
#include "Stalls.h"
#include "AudioPlayer.h"

using namespace std;

enum STARTSTATE_BUTTON
{
	go,
	back,
	reset,
	fifty,
	hundred,
	twohundred,
	ten,
	twelve,
	fifteen,
	sShop1,
	sShop2,
	sShop3
};

class CInputSystem;

class CStartOfDayState : public CInGameState
{
private:
	CStartOfDayState(void) {};

	TextureImage button[17];
	TextureImage background[2];

	bool mouseOverReset;
	bool mouseOverBack;

	float r, g, b;
	float r2, g2, b2;
	float r3, g3, b3;

public:
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
	void mouseClick(void);
	void drawInfo();
	void ChangeColor();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CStartOfDayState* Instance() {
		if (theStartOfDayState == NULL)
			theStartOfDayState = new CStartOfDayState();
		return theStartOfDayState;
	}
	void Drop()
	{
		for (int i = 0; i < 20; i++)
		{
			if(theButton[i] != NULL)
			{
				delete theButton[i];
				theButton[i] = NULL;
			}
		}

		if (sound != NULL)
		{
			delete sound;
			sound = NULL;
		}

		if (se != NULL)
		{
			delete se;
			se = NULL;
		}
		
		if (theStartOfDayState != NULL)
		{
			delete theStartOfDayState;
			theStartOfDayState = NULL;
		}

	}

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

private:
	static CStartOfDayState *theStartOfDayState;
	CButtons* theButton[20];
	AudioPlayer * sound;
	ISoundEngine *se;
};

