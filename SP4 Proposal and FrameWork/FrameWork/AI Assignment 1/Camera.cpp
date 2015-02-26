#include "Camera.h"
#include <iostream>

Camera* Camera::instance = NULL;

Camera::Camera()
: MAXSPEED_MOVE(0)
{
	SetCameraType(AIR_CAM);
	Reset();
}

Camera::Camera(CAM_TYPE ct)
{
	SetCameraType(ct);
	Reset();
}

//Singleton Structure
Camera* Camera::getInstance()
{
	//Only allows one instance of InputSystem
	if (instance == NULL)
		instance = new Camera;
	return instance;
}

Camera::~Camera() {}

void Camera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void Camera::Reset()
{
	Position = Vector3(0.0, 0.0, 0.0);
	Along = Vector3(1.0, 0.0, 0.0);
	Up = Vector3(0.0, 1.0, 0.0);
	Forward = Vector3(0.0, 0.0, -1.0);

	MAXSPEED_MOVE = 1.0f;

	camPoint.Set(0,0,0);
	camPos.Set(50.0, 50.0, -70.0);
	camDir = (camPoint-camPos).Normalized();
	camDist = 50;
	camDist_max = 100;
	VEL_X = 0.2f;
	VEL_Y = 0.01f;
	MAX_Y = 2.5f;
	angle = VEL_X * 3.142f / 180.0f;
}

void Camera::Update() {
	gluLookAt(Position.x, Position.y, Position.z, 
			  Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, 
			  0.0f,1.0f,0.0f);
}

Vector3 Camera::GetPosition() {
	return Position;
}

void Camera::SetPosition( GLfloat x, GLfloat y, GLfloat z )
{
	this->Position.Set( x, y, z );
}

void Camera::SetDirection( GLfloat x, GLfloat y, GLfloat z )
{
	this->Forward.Set( x, y, z );
}

void Camera::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}
void Camera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void Camera::Roll(GLfloat theta)
{
}
void Camera::Walk(GLfloat delta)
{
	if (delta > MAXSPEED_MOVE)
		delta = MAXSPEED_MOVE;
	if (delta < -MAXSPEED_MOVE)
		delta = -MAXSPEED_MOVE;
	if(CameraType == CAM_TYPE::LAND_CAM) {
		//Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
		camPoint.Set( camPoint.x + camDir.x * delta, camPoint.y + camDir.y * delta, camPoint.z + camDir.z * delta );
	}else{
		//Position.Set( Position.x + Forward.x * delta, Position.y, Position.z + Forward.z * delta );
		camPoint.Set( camPoint.x + camDir.x * delta, camPoint.y, camPoint.z + camDir.z * delta );
	}
}
void Camera::Strafe(GLfloat delta)
{
	Along = camDir.Cross( Up );
	Along.Normalize();
	//Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
	camPoint.Set( camPoint.x + Along.x * delta, camPoint.y + Along.y * delta, camPoint.z + Along.z * delta );
}
void Camera::Fly(GLfloat delta)
{
}

// Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode == true)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -10, 10 );      
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Disable Texture Mapping ( NEW )
	}
	else
	{
//		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable( GL_DEPTH_TEST );
	}
}
void Camera::SetORTHO(bool mode)
{
	if (mode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		int w = glutGet(GLUT_SCREEN_WIDTH);
		int h = glutGet(GLUT_SCREEN_HEIGHT);
		gluOrtho2D(0.0, w, 0.0, h);

		glMatrixMode(GL_MODELVIEW);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		
		glPushMatrix();
		glLoadIdentity();
	}
	else
	{
		//glDisable(GL_TEXTURE_2D);
		////glDisable(GL_BLEND);

		//glDisable(GL_BLEND);
		//glMatrixMode(GL_PROJECTION);
		//glPopMatrix();

		//glMatrixMode(GL_MODELVIEW);
		//glEnable( GL_DEPTH_TEST );

		glPopMatrix();
		//glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}
}

// Get the direction of the camera
Vector3 Camera::GetDirection()
{
	return Forward;
}

