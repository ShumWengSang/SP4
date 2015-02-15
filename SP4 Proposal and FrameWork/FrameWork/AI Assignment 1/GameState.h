#pragma once
#include "GameStateManager.h"

class CGameState
{
protected:

	CGameState(void) {};

public:

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(CGameStateManager * GSM) = 0;
	virtual void Update(CGameStateManager * GSM) = 0;
	virtual void Draw(CGameStateManager * GSM) = 0;
	void ChangeState(CGameStateManager* GSM, CGameState* state) {
		GSM->ChangeState(state);
	}

};

