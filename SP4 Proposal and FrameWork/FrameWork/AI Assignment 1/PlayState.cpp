#include "PlayState.h"
#include "StartOfDayState.h"
#include "BuyMaskState.h"
#include "TutorialState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{

	cout << "CPlayState::Init\n" << endl;

	//Enable Camera Orientation on Mouse Move
	CInputSystem::getInstance()->OrientCam = true;
	
	day = StartDay;

	maskInStock = 0;
	maskLeft = 0;
	oldMaskValue = 0;
	earned = 0;
	earned2 = 0;
	earned3 = 0;
	newMoneyValue = 0;
	firstDay = true;

	shop1selected = false;
	shop2selected = false;
	shop3selected = false;

	theStall[0] = new CStalls(Vector3(25,0,25));
	theStall[1] = new CStalls(Vector3(15,0,45));
	theStall[2] = new CStalls(Vector3(45,0,15));

	forecasting = new CForecast;
	forecasting->init();
	forecasting->setActualArray(theHaze.GetHazeAvg());
	forecasting->forecasting();

	//Game State Manager
	IGSM = CInGameStateManager::getInstance();
	IGSM->Init("In Game State Manager");
	IGSM->ChangeState(CTutorialState::Instance());

	theHaze.GetHazeAvg();
}

void CPlayState::Cleanup()
{
	if (IGSM != NULL)
	{
		IGSM->Cleanup();
		delete IGSM;
		IGSM = NULL;
	}
}

void CPlayState::Pause()
{}

void CPlayState::Resume()
{}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{}

void CPlayState::Update(CGameStateManager* theGSM) 
{
	keyboardUpdate();

	//Handle the GSM events
	IGSM->HandleEvents();

	//Update GSM
	IGSM->Update();
}

void CPlayState::Draw(CGameStateManager* theGSM) 
{
	//Render
	IGSM->Draw();
}

void CPlayState::keyboardUpdate()
{
	if(CInputSystem::getInstance()->myKeys[VK_ESCAPE]) 
		exit(0);
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

void CPlayState::resetValues()
{
	for(int i = 0; i<3; ++i)
	{
		theStall[i]->setMaskNo(0);
		theStall[i]->setMaskPrice(0);
		theStall[i]->setMaskSold(0);
		theStall[i]->totalMaskSold = 0;
		cout << theStall[i]->getTotalMaskSold() << endl;
	}
}

