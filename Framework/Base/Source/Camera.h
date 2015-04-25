/******************************************************************************/
/*!
\file	Camera.h
\author Chong Jun Xiang
\brief
To store camera position, target and up. With additional zoom function.
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Application.h"
#include "Vector3.h"
#include "Vector2.h"
#include "MatrixStack.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
		Class Camera:
\brief	To store camera position, target and up. With additional zoom function.
*/
/******************************************************************************/
class Camera
{
protected:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector2 focalLength;
	float magnificationFactor;
	int zoomDepth;
	bool zoomEnabled;
	float sensitivity;
public:
	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, const Vector2& focalLength);
	virtual void Reset(void);
	virtual void Update(double dt);
	virtual void Zoom(void);

	virtual void setPosition(Vector3 position);
	virtual void setTarget(Vector3 target);
	virtual void setUp(Vector3 up);
	virtual void setFocalLength(Vector2 focalLength);
	virtual void setMagnificationFactor(float magnificationFactor);
	virtual void setZoomEnabled(bool zoomEnabled);
	virtual void setSensitivity(float sensitivity);

	virtual Vector3 getPosition(void) const;
	virtual Vector3 getTarget(void) const;
	virtual Vector3 getUp(void) const;
	virtual Vector2 getFocalLength(void) const;
	virtual float getMagnificationFactor(void) = 0;
	virtual int getZoomDepth(void) = 0;
	virtual bool getZoomEnabled(void) const;
	virtual float getSensitivity(void) const;
};

#endif