#include "Application.h"
#include <mmsystem.h>
#include "PlayState.h"

CApplication* CApplication::instance = NULL;

bool CApplication::Init()
{
	//Set camera position
	theCamera = Camera::getInstance();
	theCamera->Reset();
	theCamera->SetCameraType(Camera::LAND_CAM);
	theCamera->SetPosition(0.0, -50.0, -20.0);
	theCamera->SetDirection(0.0, 0.0, 1.0);

	//Game State Manager
	GSM = CGameStateManager::getInstance();
	GSM->Init("Game State Manager");
	GSM->ChangeState(CMenuState::Instance());

	//Real-Time Loop Control
	timelastcall = timeGetTime();
	frequency = 70.0f;
	CTimer::getInstance()->init();

	return true;
}

void CApplication::Update() 
{
	//Calculate the framerate
	timelastcall = timeGetTime();

	//Update Time
	CTimer::getInstance()->updateTime();

	//Handle the GSM events
	GSM->HandleEvents();

	//Update GSM
	GSM->Update();
}

void CApplication::renderScene() {

	//Clear the Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	//Constrain Update
	if ((timeGetTime()-timelastcall) > 1000.f / frequency) //"timeGetTime()-timelastcall" is DeltaTime
		Update(); //Update Game

	//theCamera->Update();
	theCamera->newRender();

	//Render
	GSM->Draw();
	
	theCamera->SetHUD(true);
	//CTimer::getInstance()->drawFPS();
	theCamera->SetHUD(false);

	//Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	//Swapping the buffers causes the rendering above to be shown
	if (!clickCheck){
		glutSwapBuffers();
		clickCheck = false;
	}
	if (clickCheck)
		clickCheck = false;
}

void CApplication::changeSize(int w, int h) {

	//Prevent a divide by zero, when window is too short
	//(you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	//Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

//Returns only one Instance of CApplication
CApplication* CApplication::getInstance()
{
	//Singleton Structure
	if (instance == NULL)
		instance = new CApplication();
	return instance;
}

//Exit
void CApplication::drop()
{
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
	if (GSM != NULL)
	{
		GSM->Cleanup();
		delete GSM;
		GSM = NULL;
	}
	if(CTimer::getInstance() != NULL)
	{
		CTimer::drop();
	}
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

//Inputs
void CApplication::MouseMove (int x, int y) {

	GSM->GetCurrentState()->MouseMove(x,y);
}

void CApplication::MouseClick(int button, int state, int x, int y) {

	GSM->GetCurrentState()->MouseClick(button, state, x, y);
}

void CApplication::MouseWheel(int button, int dir, int x, int y) {

	GSM->GetCurrentState()->MouseWheel(button, dir, x, y);
}

bool CApplication::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
   
   FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}

bool CApplication::getClickCheck() {
	return clickCheck;
}

void CApplication::setClickCheck(bool clickChecking) {
	clickCheck = clickChecking;
}

