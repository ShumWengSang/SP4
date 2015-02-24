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

#define SEEDCOUNT 10

enum PLAYSTATE_BUTTON
{
	pause,
	shop,
	shop2,
	shop3
};

class CInputSystem;

class CGamePlayState : public CInGameState
{
private:
	CGamePlayState(void) { DayNumber = 0; };

	TextureImage button[4];
	TextureImage map[1];

	bool isPause;
	bool shopSelected;
	bool shop2Selected;
	bool shop3Selected;

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

	void buyMask(int stall, int maskNo);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CGamePlayState* Instance() {
		return &theGamePlayState;
	}

	int DayNumber;
	int HourNumber;

private:
	static CGamePlayState theGamePlayState;

	std::vector<Entity*> theListofEntities;
	std::vector<Tiles *> theSeededTiles;

	CTimer * theTimerInstance;
	int TimerKeySeed;

	int TimerKeyDay;

	void ClickCollision();

	CMoney theMoney;
	CButtons* theButton[4];
	CStalls* theStall[3];
	Grid* theGrid;
};

