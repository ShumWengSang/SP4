#include "PlayState.h"
#include "StartOfDayState.h"
#include "BuyMaskState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
	cout << "CPlayState::Init\n" << endl;

	//Enable Camera Orientation on Mouse Move
	CInputSystem::getInstance()->OrientCam = true;
	
	maskInStock = 0;
	theStall[0] = new CStalls();
	theStall[1] = new CStalls();
	theStall[2] = new CStalls();

	forecasting = new CForecast;
	forecasting->init();
	forecasting->setActualArray(theHaze.GetHazeAvg());
	forecasting->forecasting();

	//Game State Manager
	IGSM = CInGameStateManager::getInstance();
	IGSM->Init("In Game State Manager");
	IGSM->ChangeState(CBuyMaskState::Instance());

	theHaze.GetHazeAvg();
}

void CPlayState::Cleanup()
{
	//cout << "CPlayState::Cleanup\n" << endl;
	if (IGSM != NULL)
	{
		IGSM->Cleanup();
		delete IGSM;
		IGSM = NULL;
	}
}

void CPlayState::Pause()
{
	//cout << "CPlayState::Pause\n" << endl;
}

void CPlayState::Resume()
{
	//cout << "CPlayState::Resume\n" << endl;
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{

}

void CPlayState::Update(CGameStateManager* theGSM) 
{
	//cout << "CPlayState::Update\n" << endl;
	keyboardUpdate();

	//Handle the GSM events
	IGSM->HandleEvents();

	//Update GSM
	IGSM->Update();

}

void CPlayState::Draw(CGameStateManager* theGSM) 
{
	//CApplication::getInstance()->theCamera->SetHUD(true);
	//CApplication::getInstance()->theCamera->SetHUD(false);

	//Render
	IGSM->Draw();
}

void CPlayState::keyboardUpdate()
{

	//Esc Key
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
		//CGameStateManager::getInstance()->ChangeState(CMenuState::Instance());
}

//Inputs
void CPlayState::MouseMove (int x, int y) {

	IGSM->GetCurrentState()->MouseMove(x, y);

}

void CPlayState::MouseClick(int button, int state, int x, int y) {

	IGSM->GetCurrentState()->MouseClick(button, state, x, y);

}

void CPlayState::MouseWheel(int button, int dir, int x, int y) {

	IGSM->GetCurrentState()->MouseWheel(button, dir, x, y);

}

