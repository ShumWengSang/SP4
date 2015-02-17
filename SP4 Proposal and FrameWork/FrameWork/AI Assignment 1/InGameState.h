#pragma once
#include "InGameStateManager.h"

class CInGameState
{
protected:

	CInGameState(void) {};

public:

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(CInGameStateManager * PS) = 0;
	virtual void Update(CInGameStateManager * PS) = 0;
	virtual void Draw(CInGameStateManager * PS) = 0;

	//Inputs
	virtual void MouseMove (int x, int y) = 0;
	virtual void MouseClick(int button, int state, int x, int y) = 0;
	virtual void MouseWheel(int button, int dir, int x, int y) = 0;
	void ChangeState(CInGameStateManager* PS, CInGameState* state) {
		PS->ChangeState(state);
	}
};