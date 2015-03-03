#pragma once
#include <iostream>
#include "Application.h"
class TextureSingleton
{
	TextureSingleton();
	~TextureSingleton();
	static TextureSingleton * singleton;
public:
	static TextureSingleton * getInstance()
	{
		if (singleton == NULL)
			singleton = new TextureSingleton;
		return singleton;
	}

	void Drop()
	{
		if (singleton != NULL)
		{
			delete singleton;
			singleton = NULL;
		}
	}

	std::vector<int> TextureInts;

	int GetNumber(unsigned int number)
	{
		if (number <= TextureInts.size())
			return TextureInts[number];
		return 0;
	}

	void Init()
	{
		//Start from 0 to 5 MENU
		LoadTexture("images/menuState/gameTitle.tga");
		LoadTexture("images/menuState/map.tga");
		LoadTexture("images/menuState/start.tga");
		LoadTexture("images/menuState/loadGame.tga");
		LoadTexture("images/menuState/options.tga");
		LoadTexture("images/menuState/quit.tga");

		//6  to 12 BUY MASK
		LoadTexture("images/background.tga");
		LoadTexture("images/buyMaskState/box.tga");
		LoadTexture("images/buyMaskState/box2.tga");
		LoadTexture("images/buyMaskState/next.tga");
		LoadTexture("images/buyMaskState/50.tga");
		LoadTexture("images/buyMaskState/100.tga");
		LoadTexture("images/buyMaskState/200.tga");

		//13 - 28 START OF DAY
		LoadTexture("images/startState/box.tga");
		LoadTexture("images/startState/go.tga");
		LoadTexture("images/startState/50.tga");
		LoadTexture("images/startState/100.tga");
		LoadTexture("images/startState/200.tga");
		LoadTexture("images/startState/10.tga");
		LoadTexture("images/startState/12.tga");
		LoadTexture("images/startState/15.tga");
		LoadTexture("images/startState/back.tga");
		LoadTexture("images/startState/reset.tga");
		LoadTexture("images/startState/shop.tga");
		LoadTexture("images/startState/shop2.tga");
		LoadTexture("images/startState/shop3.tga");
		LoadTexture("images/startState/shopSelected.tga");
		LoadTexture("images/startState/shop2Selected.tga");
		LoadTexture("images/startState/shop3Selected.tga");

		//29 - 37
		//Textures GAMEPLAYSTATE
		LoadTexture("images/playState/pause.tga");
		LoadTexture("images/playState/SkyBox/skybox_near.tga");
		LoadTexture("images/playState/SkyBox/skybox_far.tga");
		LoadTexture("images/playState/SkyBox/skybox_left.tga");
		LoadTexture("images/playState/SkyBox/skybox_right.tga");
		LoadTexture("images/playState/SkyBox/skybox_top.tga");
		LoadTexture("images/playState/SkyBox/skybox_bottom.tga");
		LoadTexture("images/Gress_Texture.tga");
		LoadTexture("images/playState/x.tga");

		//38 - 39 END OF DAY
		LoadTexture("images/endState/background.tga");
		LoadTexture("images/endState/save.tga");

		//help state 40 - 43
		LoadTexture("images/.tga"); // Vol up Button 
		LoadTexture("images/.tga"); // Vol down Button
		LoadTexture("images/.tga"); // Information Button
		LoadTexture("images/description.tga"); //help state Background image

		//end game state 44 - 45
		LoadTexture("images/win.tga");
		LoadTexture("images/lose.tga");

		//SAVE 68 - 71

		//Load 72 - 75



	}
	int LoadTexture(std::string filename)
	{
		TextureImage theImg;
		CApplication::getInstance()->LoadTGA(&theImg, (char*)filename.c_str());
		TextureInts.push_back(theImg.texID);
		return TextureInts.size() - 1;
	}

	
	

};

