#pragma once
#include <iostream>
#include <vector>
#include "InGameState.h"
#include "InGameStateManager.h"
#include "Global.h"
#include "Input.h"
#include "InGameState.h"
#include "TextureImage.h"
#include "AudioPlayer.h"
#include "TextureSingleton.h"
#include "BuyMaskState.h"

using namespace std;

class CInputSystem;

class CTutorialState: public CInGameState
{
	TextureImage background[5];
	int screen;

public:

	CTutorialState(void);
	~CTutorialState(void);

	void Init();
	void Cleanup(){};

	void Pause(){};
	void Resume(){};

	void HandleEvents(CInGameStateManager* GSM){};
	void Update(CInGameStateManager* GSM);
	void Draw(CInGameStateManager* GSM);
	void keyboardUpdate(void);
	void LoadTextures();
	void MoveNewsPaper();
	void DrawNewsPaper();
	void DrawFirstScreen();
	void DrawSecondScreen();
	void DrawThirdScreen();
	void DrawLastScreen();
	void RenderPictures();

	//Inputs
	void MouseMove (int x, int y){};
	void MouseClick(int button, int state, int x, int y);
	void MouseWheel(int button, int dir, int x, int y){};

	static CTutorialState* Instance() {
		if (theTutorState == NULL)
			theTutorState = new CTutorialState();
		return theTutorState;
	}

	void Drop()
	{
		if (theTutorState != NULL)
		{
			delete theTutorState;
			theTutorState = NULL;
		}
	}

private:
	static CTutorialState * theTutorState;
	int rotate;
	int speed;
};