#include "InGameStateManager.h"
#include "InGameState.h"

CInGameStateManager* CInGameStateManager::instance = NULL;

//Only returns one Instance of CInGameStateManager
CInGameStateManager* CInGameStateManager::getInstance()
{
	//Singleton Structure
	if (instance == NULL)
		instance = new CInGameStateManager;
	return instance;
}

void CInGameStateManager::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
	m_fullscreen = fullscreen;
	m_running = true;

	//cout << "CInGameStateManager::Init\n" << endl;
}

void CInGameStateManager::Cleanup()
{
	// cleanup the all states
	while ( !StackOfStates_InGame.empty() ) {
		StackOfStates_InGame.back()->Cleanup();
		StackOfStates_InGame.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_fullscreen ) {
	}

	//cout << "CInGameStateManager::Cleanup\n" << endl;
}

void CInGameStateManager::ChangeState(CInGameState* state) 
{
	// cleanup the current state (Calls Destructor, destroys InputSystem, causes crash)
	/*if ( !StackOfStates_InGame.empty() ) {
		StackOfStates_InGame.back()->Cleanup();
		StackOfStates_InGame.pop_back();
	}*/

	// store and init the new state
	StackOfStates_InGame.push_back(state);
	StackOfStates_InGame.back()->Init();
	//cout << "CInGameStateManager::ChangeState\n" << endl;
}

void CInGameStateManager::PushState(CInGameState* state)
{
	// pause current state
	if ( !StackOfStates_InGame.empty() ) {
		StackOfStates_InGame.back()->Pause();
	}

	// store and init the new state
	StackOfStates_InGame.push_back(state);
	StackOfStates_InGame.back()->Init();
	//cout << "CInGameStateManager::PushState\n" << endl;
}

void CInGameStateManager::PopState()
{
	// cleanup the current state
	if ( !StackOfStates_InGame.empty() ) {
		StackOfStates_InGame.back()->Cleanup();
		StackOfStates_InGame.pop_back();
	}

	// resume previous state
	if ( !StackOfStates_InGame.empty() ) {
		StackOfStates_InGame.back()->Resume();
	}
	//cout << "CInGameStateManager::PopState\n" << endl;
}

void CInGameStateManager::HandleEvents() 
{
	// let the state handle events
	StackOfStates_InGame.back()->HandleEvents(this);
	//cout << "CInGameStateManager::HandleEvents\n" << endl;
}

void CInGameStateManager::Update() 
{
	// let the state update the theGSM
	StackOfStates_InGame.back()->Update(this);
	//cout << "CInGameStateManager::Update\n" << endl;
}

void CInGameStateManager::Draw() 
{
	// let the state draw the screen
	StackOfStates_InGame.back()->Draw(this);
	//cout << "CInGameStateManager::Draw\n" << endl;
}

CInGameState* CInGameStateManager::GetCurrentState()
{
	return StackOfStates_InGame.back();
}

