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
public:
	FPcamera();
	~FPcamera();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt, float floorLevel);
	void Reset(void);

	void setPosition(Vector3 position);
	void setTarget(Vector3 target);
	void setUp(Vector3 up);
	void setSensitivity(float sensitivity);

	Vector3 getPosition(void) const;
	Vector3 getTarget(void) const;
	Vector3 getUp(void) const;
	Vector3 getRight(void) const;
	float getSensitivity(void) const;
};

#endif