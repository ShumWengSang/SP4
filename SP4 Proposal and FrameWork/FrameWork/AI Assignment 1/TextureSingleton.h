#pragma once
#include <iostream>
class TextureSingleton
{
	TextureSingleton();
	~TextureSingleton();
	static TextureSingleton * singleton;
public:
	TextureSingleton * getInstance()
	{
		if (singleton == NULL)
			singleton = new TextureSingleton;
		return singleton;
	}
	

};

