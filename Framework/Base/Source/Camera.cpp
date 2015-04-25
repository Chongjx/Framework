/******************************************************************************/
/*!
\file	Camera.cpp
\author Chong Jun Xiang
\brief
Camera funtions that calculate and return the latest position of the camera.
*/
/******************************************************************************/
#include "Camera.h"

/******************************************************************************/
/*!
\brief
Camera default constructor
*/
/******************************************************************************/
Camera::Camera()
{
	Reset();
}

/******************************************************************************/
/*!
\brief
Camera default destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief	Camera Init function

\param	pos
	position vector3
\param	target
	target vector3
\param	up
	up vector3
\param focalLength
	focal length vector2
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up, const Vector2& focalLength)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->focalLength = focalLength;
	
	magnificationFactor = focalLength.y / focalLength.x;
	zoomDepth = 1;
	zoomEnabled = true;
	sensitivity = 1.0f;
}

/******************************************************************************/
/*!
\brief	reset position
*/
/******************************************************************************/
void Camera::Reset()
{
	position.Set(0, 0, 1);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);

	focalLength.Set(30, 300);
	magnificationFactor = 10.0f;
	zoomDepth = 1;
	zoomEnabled = true;
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	dt
    the time passed since last update
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	if(Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A'))
	{
		position.x -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))
	{
		position.x += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W'))
	{
		position.y += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S'))
	{
		position.y -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
}

/******************************************************************************/
/*!
\brief	Camera Zoom function
*/
/******************************************************************************/
void Camera::Zoom(void)
{

}

/******************************************************************************/
/*!
\brief	Camera Setter function

\param	position
	position vector3
*/
/******************************************************************************/
void Camera::setPosition(Vector3 position)
{
	this->position = position;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	target
	target vector3
*/
/******************************************************************************/
void Camera::setTarget(Vector3 target)
{
	this->target = target;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	up
	up vector3
*/
/******************************************************************************/
void Camera::setUp(Vector3 up)
{
	this->up = up;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	focalLength
	focalLength vector2
*/
/******************************************************************************/
void Camera::setFocalLength(Vector2 focalLength)
{
	this->focalLength = focalLength;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	target
	magnificationFactor float
*/
/******************************************************************************/
void Camera::setMagnificationFactor(float magnificationFactor)
{
	this->magnificationFactor = magnificationFactor;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	zoomEnabled
	Enable zoom bool
*/
/******************************************************************************/
void Camera::setZoomEnabled(bool zoomEnabled)
{
	this->zoomEnabled = zoomEnabled;
}

/******************************************************************************/
/*!
\brief	Camera Setter functions

\param	sensitivity
	Enable zoom bool
*/
/******************************************************************************/
void Camera::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	Vector3
	position vector3
*/
/******************************************************************************/
Vector3 Camera::getPosition(void) const
{
	return position;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	Vector3
	target vector3
*/
/******************************************************************************/
Vector3 Camera::getTarget(void) const
{
	return target;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	Vector3
	up vector3
*/
/******************************************************************************/
Vector3 Camera::getUp(void) const
{
	return up;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	Vector2
	focalLength vector2
*/
/******************************************************************************/
Vector2 Camera::getFocalLength(void) const
{
	return focalLength;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	float
	magnificationFactor float
*/
/******************************************************************************/
float Camera::getMagnificationFactor(void)
{
	return focalLength.y / focalLength.x;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	int
	zoomDepth int
*/
/******************************************************************************/
int Camera::getZoomDepth(void)
{
	return zoomDepth;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	bool
	zoomEnabled bool
*/
/******************************************************************************/
bool Camera::getZoomEnabled(void) const
{
	return zoomEnabled;
}

/******************************************************************************/
/*!
\brief	Camera Getter functions

\return	float
	sensitivity float
*/
/******************************************************************************/
float Camera::getSensitivity(void) const
{
	return sensitivity;
}