
#include "freeglut.h"
#include "Global.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Application.h"

void changeSize(int w, int h) {
	CApplication::getInstance()->changeSize(w,h);
}
void renderScene() {
	CApplication::getInstance()->renderScene();
}

void KeyboardDown(unsigned char key, int x, int y){
	CInputSystem::getInstance()->KeyboardDown(key,x,y);
}
void KeyboardUp(unsigned char key, int x, int y){
	CInputSystem::getInstance()->KeyboardUp(key,x,y);
}
void MouseMove(int x, int y){
	CInputSystem::getInstance()->MouseMove(x,y);
}
void MouseClick(int button, int state, int x, int y){
	CInputSystem::getInstance()->MouseClick(button, state, x, y);
}

void MouseWheel(int button, int dir, int x, int y) {
	CInputSystem::getInstance()->MouseWheel(button, dir, x, y);
}

void CleanUpUponExit()
{
	CApplication::getInstance()->drop();
}

int main( int argc, char **argv ){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("AI");

	glutReshapeFunc(changeSize);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);
	glutMouseWheelFunc(MouseWheel);

	atexit(CleanUpUponExit);

	if (CApplication::getInstance()->Init())
		glutMainLoop(); 
	else
	{
		printf("Error Initialising Program\n");
		return false;
	}

	return true;
}

