#include "InGameStateManager.h"
#include "InGameState.h"
#include "EndOfDayState.h"
#include "BuyMaskState.h"
#include "StartOfDayState.h"
#include "GamePlayState.h"

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
	state->Init();
	GameStateID temp = state->thisState;
	for (auto i = StackOfStates_InGame.begin(); i != StackOfStates_InGame.end();)
	{
		if ((*i)->thisState == state->thisState)
		{
			(*i)->Cleanup();
			(*i)->Drop();
			i = StackOfStates_InGame.erase(i);
			state = NULL;
			break;
		}
		else
		{
			i++;
		}
	}
	if(state != NULL)
		state->Drop();
	switch (temp)
	{
		case BuyMaskState:
		state = CBuyMaskState::Instance();
		break;
		case StartofDayState:
		state = CStartOfDayState::Instance();
		break;
		case PlayGameState:
		state = CGamePlayState::Instance();

		break;
		case EndofDayState:
		state = CEndOfDayState::Instance();
		break;
	}
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

