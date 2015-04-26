/******************************************************************************/
/*!
\file	FPcamera.cpp
\author Jun Xiang
\brief
Camera funtions that calculate and return the latest position of the camera.
*/
/******************************************************************************/
#include "FPcamera.h"

/******************************************************************************/
/*!
\brief
FPcamera default constructor
*/
/******************************************************************************/
FPcamera::FPcamera()
{
}

/******************************************************************************/
/*!
\brief
FPcamera default destructor
*/
/******************************************************************************/
FPcamera::~FPcamera()
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
*/
/******************************************************************************/
void FPcamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
    right = view.Cross(up).Normalized();
	right.y = 0;
    right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->sensitivity = defaultSensitivity = 1.0f;
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	dt
    the time passed since last update
*/
/******************************************************************************/
void FPcamera::Update(double dt, float floorLevel)
{
	static const float CAMERA_SPEED = 200.f;
	
	if(Application::IsKeyPressed('A'))
	{
		Vector3 tempPosition = position;
		Vector3 tempTarget = target;
		
		Vector3 view = (target - position).Normalized();
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED * (float)dt;
		target -= right * CAMERA_SPEED * (float)dt;

		position.y = tempPosition.y;
		target.y = tempTarget.y;
	}

	if(Application::IsKeyPressed('D'))
	{
		Vector3 tempPosition = position;
		Vector3 tempTarget = target;

		Vector3 view = (target - position).Normalized();
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED * (float)dt;
		target += right * CAMERA_SPEED * (float)dt;

		position.y = tempPosition.y;
		target.y = tempTarget.y;
	}

	if(Application::IsKeyPressed('W'))
	{
		Vector3 tempPosition = position;
		Vector3 tempTarget = target;

		Vector3 view = (target - position).Normalized();
		position += view * CAMERA_SPEED * (float)dt;
		target += view * CAMERA_SPEED * (float)dt;

		position.y = tempPosition.y;
		target.y = tempTarget.y;

	}

	if(Application::IsKeyPressed('S'))
	{
		Vector3 tempPosition = position;
		Vector3 tempTarget = target;

		Vector3 view = (target - position).Normalized();
		position -= view * CAMERA_SPEED * (float)dt;
		target -= view * CAMERA_SPEED * (float)dt;

		position.y = tempPosition.y;
		target.y = tempTarget.y;
	}

	//Update the camera direction based on mouse move
	// left-right rotate
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt * sensitivity);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
	}

	{
		float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt * sensitivity);
		Vector3 view = (target - position).Normalized();
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

/******************************************************************************/
/*!
\brief	reset position
*/
/******************************************************************************/
void FPcamera::Reset(void)
{
	this->position = defaultPosition;
	this->target = defaultTarget;
	this->up = defaultUp;
	this->sensitivity = defaultSensitivity;

	Vector3 view = (target - position).Normalized();
    right = view.Cross(up).Normalized();
	right.y = 0;
    right.Normalize();
}

/******************************************************************************/
/*!
\brief	FPcamera Setter function

\param	position
	position vector3
*/
/******************************************************************************/
void FPcamera::setPosition(Vector3 position)
{
	this->position = position;
}

/******************************************************************************/
/*!
\brief	FPcamera Setter functions

\param	target
	target vector3
*/
/******************************************************************************/
void FPcamera::setTarget(Vector3 target)
{
	this->target = target;
}

/******************************************************************************/
/*!
\brief	FPcamera Setter functions

\param	up
	up vector3
*/
/******************************************************************************/
void FPcamera::setUp(Vector3 up)
{
	this->up = up;
}

/******************************************************************************/
/*!
\brief	FPcamera Setter functions

\param	sensitivity
	sensitivty of the mouse float
*/
/******************************************************************************/
void FPcamera::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

/******************************************************************************/
/*!
\brief	FPcamera Getter functions

\return	Vector3
	position vector3
*/
/******************************************************************************/
Vector3 FPcamera::getPosition(void) const
{
	return position;
}

/******************************************************************************/
/*!
\brief	FPcamera Getter functions

\return	Vector3
	target vector3
*/
/******************************************************************************/
Vector3 FPcamera::getTarget(void) const
{
	return target;
}

/******************************************************************************/
/*!
\brief	FPcamera Getter functions

\return	Vector3
	up vector3
*/
/******************************************************************************/
Vector3 FPcamera::getUp(void) const
{
	return up;	
}

/******************************************************************************/
/*!
\brief	FPcamera Getter functions

\return	Vector3
	right vector3
*/
/******************************************************************************/
Vector3 FPcamera::getRight(void) const
{
	return right;
}

/******************************************************************************/
/*!
\brief	FPcamera Getter functions

\return	float
	mouse sensitivity float
*/
/******************************************************************************/
float FPcamera::getSensitivity(void) const
{
	return sensitivity;
}