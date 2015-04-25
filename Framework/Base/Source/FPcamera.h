/******************************************************************************/
/*!
\file	FPCamera.h
\author Chong Jun Xiang
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
class FPcamera : Camera
{
private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 right;
	Vector2 defaultFocalLength;
	int defaultZoomDepth;
	bool defaultZoomEnabled;
	float defaultSensitivity;
public:
	FPcamera();
	~FPcamera();

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up, const Vector2& focalLength);
	void Update(double dt, float floorLevel);
	void Reset(void);
	void Zoom(void);

	void setPosition(Vector3 position);
	void setTarget(Vector3 target);
	void setUp(Vector3 up);
	void setFocalLength(Vector2 focalLength);
	void setMagnificationFactor(float magnificationFactor);
	void setZoomEnabled(bool zoomEnabled);
	void setSensitivity(float sensitivity);

	Vector3 getPosition(void) const;
	Vector3 getTarget(void) const;
	Vector3 getUp(void) const;
	Vector2 getFocalLength(void) const;
	float getMagnificationFactor(void);
	int getZoomDepth(void);
	bool getZoomEnabled(void) const;
	float getSensitivity(void) const;
};

#endif