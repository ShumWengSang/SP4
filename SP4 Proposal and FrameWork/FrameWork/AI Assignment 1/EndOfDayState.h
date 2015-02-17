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

class CEndOfDayState : public CInGameState
{
private:
	CEndOfDayState(void) {};

public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CInGameStateManager* GSM);
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);

	static CEndOfDayState* Instance() {
		return &theEndOfDayState;
	}

private:
	static CEndOfDayState theEndOfDayState;

};

