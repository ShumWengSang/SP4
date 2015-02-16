#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"

using namespace std;

class CInputSystem;

class CGamePlayState : public CInGameState
{
private:
	CGamePlayState(void) {};

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);

	static CGamePlayState* Instance() {
		return &theGamePlayState;
	}

private:
	static CGamePlayState theGamePlayState;

};

