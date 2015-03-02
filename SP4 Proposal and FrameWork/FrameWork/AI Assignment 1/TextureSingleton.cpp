#include "TextureSingleton.h"


TextureSingleton::TextureSingleton()
{
	Init();
}


TextureSingleton::~TextureSingleton()
{
}
TextureSingleton * TextureSingleton::singleton = NULL;