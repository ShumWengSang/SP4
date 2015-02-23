#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"
#include "Money.h"
#include "TextureImage.h"
#include "Buttons.h"
#include "Grid.h"
#include "Stalls.h"

using namespace std;

enum PLAYSTATE_BUTTON
{
	pause
};

class CInputSystem;

class CGamePlayState : public CInGameState
{
private:
	CGamePlayState(void) {};

	TextureImage button[4];
	TextureImage map[1];

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);
	void LoadTextures();
	void LoadButtons();
	void DrawButtons();

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CGamePlayState* Instance() {
		return &theGamePlayState;
	}

private:
	static CGamePlayState theGamePlayState;

	CMoney theMoney;
	CButtons* theButton[4];
	CStalls* theStall[3];
	Grid myLoc;
};

