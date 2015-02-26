#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "freeglut.h"
#include "Global.h"

class Camera
{
public:
	enum CAM_TYPE { LAND_CAM, AIR_CAM };

private:
	CAM_TYPE CameraType;
	Vector3 Position;
	Vector3 Along;		//100
	Vector3 Up;			//010
	Vector3 Forward;

	static Camera *instance;
	Camera();
	Camera(CAM_TYPE ct);

	Vector3 camPos;		//Position	position of cam
	Vector3 camPoint;	//			position cam is pointing at
	Vector3 camDir;		//Forward	direction cam is pointing to

public:
	static Camera* getInstance();
	~Camera();

	float camDist_max;	//Max zoom dist of cam
	float camDist;		//zoom dist of cam
	float angle;		//angle of cam along y-axis
	float VEL_X;		//speed of camera rotation along y-axis
	float VEL_Y;		//speed of camera rotation upwards/downwards
	float MAX_Y;		//maximum speed of VEL_Y
	float MAXSPEED_MOVE;//Maximum movement speed

	void SetCameraType(CAM_TYPE ct);
	void Reset();
	void Update();
	Vector3 GetPosition();
	// Get the direction of the camera
	Vector3 GetDirection();
	void SetPosition( GLfloat x, GLfloat y, GLfloat z );
	void SetDirection( GLfloat x, GLfloat y, GLfloat z );

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta);//, bool Wall[4]);
	void Strafe(GLfloat delta);//, bool Wall[4]);
	void Fly(GLfloat delta);
	// Toggle HUD mode
	void SetHUD(bool m_bHUDmode);
	// Toggle ORTHO Mode
	void SetORTHO(bool mode);

	//=====================================

	void SetPos(Vector3 newPos)	{camPoint.Set(newPos);}
	Vector3 GetPos()			{return camPoint;}
	void SetDir(Vector3 newDir)	{camDir.Set(newDir);}
	Vector3 GetDir()			{return camDir;}

	void newUpdate(){
		camPos.Set( camPoint - camDir*camDist );}
	void newRender(){Vector3 ActCamDir((camPoint - camPos).Normalized());	//For rendering
						gluLookAt(	camPos.x, camPos.y, camPos.z, 
								camPos.x + ActCamDir.x, camPos.y + ActCamDir.y, camPos.z + ActCamDir.z, 
								0.0f,1.0f,0.0f);}

};

#endif
