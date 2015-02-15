#include "PlayState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
	//cout << "CPlayState::Init\n" << endl;

	//Input System
	InputSystem = CInputSystem::getInstance();

	//Enable Camera Orientation on Mouse Move
	InputSystem->OrientCam = true;

	player = new GameObject;
	player->type = GAMEOBJECT_TYPE::GO_PLAYER;
	player->pos.Set(10,10,0);
	player->vel.Set(0.1,0.1,0);
	player->color.Set(1,0,0);
	player->hp = 100;
	player->active = true;
	v_Total.push_back(player);

	police = new GameObject;
	police->type = GAMEOBJECT_TYPE::GO_PLAYER;
	police->pos.Set(30,30,0);
	police->vel.Set(0.1,0.1,0);
	police->color.Set(0,0,1);
	police->hp = 30;
	police->active = true;
	v_Total.push_back(police);

}

void CPlayState::Cleanup()
{
	//cout << "CPlayState::Cleanup\n" << endl;
	if (InputSystem != NULL)
	{
		delete InputSystem;
		InputSystem = NULL;
	}

	while(v_Total.size() > 0)
	{
		GameObject *to = v_Total.back();
		delete to;
		v_Total.pop_back();
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
	/*int m_iUserChoice = -1;

	do {
		cout << "CPlayState: Choose one <0> Go to Menu State, <1> Go to Play State : " ;
		cin >> m_iUserChoice;
		cin.get();

		switch (m_iUserChoice) {
			case 0:
				//theGSM->ChangeState( CMenuState::Instance() );
				break;
			case 1:
				//theGSM->ChangeState( CPlayState::Instance() );
				break;
			default:
				cout << "Invalid choice!\n";
				m_iUserChoice = -1;
				break;
		}
	} while (m_iUserChoice == -1);*/
}

void CPlayState::Update(CGameStateManager* theGSM) 
{
	//cout << "CPlayState::Update\n" << endl;
	keyboardUpdate();
	
	for(std::vector<GameObject *>::iterator it = v_Total.begin(); it != v_Total.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			go->pos.operator+=(go->vel);
		}
	}

}

void CPlayState::Draw(CGameStateManager* theGSM) 
{
	CApplication::getInstance()->theCamera->SetHUD(true);

	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
			glBegin(GL_QUADS);
				int height = 100 * 1.333/1.5;
				glVertex2f(0,SCREEN_HEIGHT);
				glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);
				glVertex2f(SCREEN_WIDTH,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	
	for(std::vector<GameObject *>::iterator it = v_Total.begin(); it != v_Total.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderCharacter(go);
		}
	}

	CApplication::getInstance()->theCamera->SetHUD(false);
}

void CPlayState::keyboardUpdate()
{
	//WASD Movement
	/*if(InputSystem->myKeys['w'] || InputSystem->myKeys['W'])
		InputSystem->moveMeForward(true, 1.0f);
	if(InputSystem->myKeys['a'] || InputSystem->myKeys['A'])
		InputSystem->moveMeSideway(true, 1.0f);
	if(InputSystem->myKeys['s'] || InputSystem->myKeys['S'])
		InputSystem->moveMeForward(false, 1.0f);
	if(InputSystem->myKeys['d'] || InputSystem->myKeys['D'])
		InputSystem->moveMeSideway(false, 1.0f);

	//WASD Released
	if(!InputSystem->myKeys['w'] && !InputSystem->myKeys['W'] &&
	   !InputSystem->myKeys['a'] && !InputSystem->myKeys['A'] &&
	   !InputSystem->myKeys['s'] && !InputSystem->myKeys['S'] &&
	   !InputSystem->myKeys['d'] && !InputSystem->myKeys['D'])
		InputSystem->previousVelocity = 0;*/

	//Esc Key
	if(InputSystem->myKeys[VK_ESCAPE]) 
		exit(0);
		//CGameStateManager::getInstance()->ChangeState(CMenuState::Instance());
}

void CPlayState::RenderCharacter(GameObject* go){

	glPushMatrix();
	
	switch(go->type){

	case GAMEOBJECT_TYPE::GO_PLAYER:
		glColor3f(go->color.x,go->color.y,go->color.z);
		glTranslatef(go->pos.x,go->pos.y,go->pos.z);
		glutSolidSphere(10,10,10);
		break;

	case GAMEOBJECT_TYPE::GO_CIVILIAN:
		glColor3f(go->color.x,go->color.y,go->color.z);
		glTranslatef(go->pos.x,go->pos.y,go->pos.z);
		glutSolidSphere(10,10,10);
		break;

	case GAMEOBJECT_TYPE::GO_POLICE:
		glColor3f(go->color.x,go->color.y,go->color.z);
		glTranslatef(go->pos.x,go->pos.y,go->pos.z);
		glutSolidSphere(10,10,10);
		break;

	}

	glColor3f(1,1,1);
	glPopMatrix();

}

