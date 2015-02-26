#include "PlayState.h"
#include "StartOfDayState.h"
#include "BuyMaskState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
	cout << "CPlayState::Init\n" << endl;

	//Enable Camera Orientation on Mouse Move
	CInputSystem::getInstance()->OrientCam = true;
	
	day = 1;

	maskInStock = 0;
	maskLeft = 0;
	oldMaskValue = 0;
	earned = 0;
	earned2 = 0;
	earned3 = 0;
	newMoneyValue = 0;
	firstDay = true;

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
	//Camera::getInstance()->SetHUD(true);
	//Camera::getInstance()->SetHUD(false);

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

