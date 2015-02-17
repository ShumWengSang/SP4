#pragma once
#include <vector>
#include <iostream>

using namespace std;

class CInGameState;

class CInGameStateManager
{
public:
	
	static CInGameStateManager* getInstance();

	void Init(const char* title, int width=640, int height=480, int bpp=32, bool fullscreen=false);
	void Cleanup();

	void ChangeState(CInGameState* state);
	void PushState(CInGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();
	bool Running() { 
		return m_running; 
	}
	void Quit() { 
		m_running = false; 
	}

private:
	static CInGameStateManager *instance;

	// the stack of states
	vector<CInGameState*> StackOfStates_InGame;

	bool m_running;
	bool m_fullscreen;

};

