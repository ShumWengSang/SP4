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
#include "Money.h"
#include "AudioPlayer.h"

using namespace std;

enum BUYSTATE_BUTTON
{
	nextPage,
	bFifty,
	bHundred,
	bTwohundred
};

class CInputSystem;

class CBuyMaskState : public CInGameState
{
private:
	CBuyMaskState(void) {};

	TextureImage button[4];
	TextureImage background[3];

	bool needMoney;
public:

	void Init();
	void Cleanup(){};

	void Pause(){};
	void Resume(){};

	void HandleEvents(CInGameStateManager* GSM){};
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();
	void DrawBackground();

	void drawInfo();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y){};

	static CBuyMaskState* Instance() {
		if (theBuyMaskState == NULL)
			theBuyMaskState = new CBuyMaskState();
		return theBuyMaskState;
	}

	void Drop()
	{
		if (theBuyMaskState != NULL)
		{
			delete theBuyMaskState;
			theBuyMaskState = NULL;
		}

		for (int i = 0; i < 4; i++)
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
	}

	void *font_style;
	void printw(float x, float y, float z, char* format, ...);

private:
	static CBuyMaskState * theBuyMaskState;
	CMoney theMoney;
	CButtons *theButton[4];
	AudioPlayer *sound;
	ISoundEngine *se;
	//ISound *obj;
};