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
#include "MatrixStack.h"

class FPcamera : Camera
{
public:
	FPcamera(void);
	~FPcamera(void);

	Vector3 defaultPostition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 right;
	Vector2 defaultFocalLength;
	float defaultMagnificationFactor;
	int defaultZoomDepth;
	bool defaultZoomEnabled;

	void Init(const Vector3& pos, const Vector3& target, const Vector3& up, const Vector2& focalLength);
	void Update(double dt);
	void Reset(void);
	void Zoom(void);


};

#endif