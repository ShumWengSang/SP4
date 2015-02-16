#include "Camera.h"
#include <iostream>

Camera::Camera()
: MAXSPEED_MOVE(0)
{
	SetCameraType(LAND_CAM);
	Reset();
}

Camera::Camera(CAM_TYPE ct)
{
	SetCameraType(ct);
	Reset();
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
//	Update();

	MAXSPEED_MOVE = 2.0f;
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

	Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
}
void Camera::Strafe(GLfloat delta)
{
	Along = Forward.Cross( Up );
	Along.Normalize();
	Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
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
