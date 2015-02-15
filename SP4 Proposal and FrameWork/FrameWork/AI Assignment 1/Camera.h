#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "freeglut.h"

class Camera
{
public:
	enum CAM_TYPE { LAND_CAM, AIR_CAM };

private:
	CAM_TYPE CameraType;
	Vector3 Position;
	Vector3 Along;
	Vector3 Up;
	Vector3 Forward;

public:
	Camera();
	Camera(CAM_TYPE ct);
	~Camera();

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
private:
	// Maximum movement speed
	float MAXSPEED_MOVE;
};

#endif
