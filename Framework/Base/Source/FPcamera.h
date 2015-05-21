/******************************************************************************/
/*!
\file	FPCamera.h
\author Jun Xiang
\brief
FPS camera system
*/
/******************************************************************************/
#ifndef FP_CAMERA_H
#define FP_CAMERA_H

#include "Camera.h"

/******************************************************************************/
/*!
		Class FPcamera:
\brief	First Person Camera System
*/
/******************************************************************************/
class FPcamera : public Camera
{
private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 right;
	float defaultSensitivity;
	bool myKeys[255];
public:
	FPcamera();
	~FPcamera();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float floorLevel);
	virtual void UpdateStatus(const unsigned char key);
	virtual void Reset(void);

	virtual void setPosition(Vector3 position);
	virtual void setTarget(Vector3 target);
	virtual void setUp(Vector3 up);
	virtual void setSensitivity(float sensitivity);

	virtual Vector3 getPosition(void) const;
	virtual Vector3 getTarget(void) const;
	virtual Vector3 getUp(void) const;
	virtual Vector3 getRight(void) const;
	virtual float getSensitivity(void) const;

	virtual void moveForward(const double dt, float heightOffset);
	virtual void moveBackward(const double dt, float heightOffset);
	virtual void moveLeft(const double dt, float heightOffset);
	virtual void moveRight(const double dt, float heightOffset);
	virtual void moveUp(const double dt);
	virtual void moveDown(const double dt);
	virtual void turnLeft(const double dt);
	virtual void turnRight(const double dt);
	virtual void turnUp(const double dt);
	virtual void turnDown(const double dt);
};

#endif