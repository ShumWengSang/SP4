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
#include "Stalls.h"

using namespace std;

enum STARTSTATE_BUTTON
{
	go,
	fifty,
	hundred,
	twohundred,
	fifty2,
	hundred2,
	twohundred2,
	fifty3,
	hundred3,
	twohundred3
};

class CInputSystem;

class CStartOfDayState : public CInGameState
{
private:
	CStartOfDayState(void) {};

	TextureImage button[4];
	TextureImage background[1];

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void DrawButtons();
	void DrawBackground();
	void keyboardUpdate(void);
	void mouseClick(void);

	//Inputs
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y);

	static CStartOfDayState* Instance() {
		return &theStartOfDayState;
	}

private:
	static CStartOfDayState theStartOfDayState;
	CMoney theMoney;
	CButtons* theButton[10];
	CStalls* theStall[3];

};

