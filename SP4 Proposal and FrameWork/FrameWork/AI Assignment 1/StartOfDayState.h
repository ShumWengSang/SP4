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

using namespace std;

enum STARTSTATE_BUTTON
{
	go
};

class CInputSystem;

class CStartOfDayState : public CInGameState
{
private:
	CStartOfDayState(void) {};

	TextureImage button[1];
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

	static CStartOfDayState* Instance() {
		return &theStartOfDayState;
	}

private:
	static CStartOfDayState theStartOfDayState;
	CButtons* theButton[4];

};

