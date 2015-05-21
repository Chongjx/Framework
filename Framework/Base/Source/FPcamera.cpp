/******************************************************************************/
/*!
\file	FPcamera.cpp
\author Jun Xiang
\brief
Camera funtions that calculate and return the latest position of the camera.
*/
/******************************************************************************/
#include "FPcamera.h"
#include "Application.h"
#include "Mtx44.h"

static const float CAMERA_SPEED = 200.f;
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

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}
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
	if(myKeys['a'])
	{
		moveLeft(dt, floorLevel);
		myKeys['a'] = false;
	}

	if(myKeys['d'])
	{
		moveRight(dt, floorLevel);
		myKeys['d'] = false;
	}

	if(myKeys['w'])
	{
		moveForward(dt, floorLevel);
		myKeys['w'] = false;
	}

	if(myKeys['s'])
	{
		moveBackward(dt, floorLevel);	
		myKeys['s'] = false;
	}

	if(myKeys['q'])
	{
		moveUp(dt);
		myKeys['q'] = false;
	}

	if(myKeys['e'])
	{
		moveDown(dt);
		myKeys['e'] = false;
	}

	if(myKeys['i'])
	{
		turnUp(dt);
	}

	if(myKeys['j'])
	{
		turnDown(dt);
	}

	if(myKeys['j'])
	{
		turnLeft(dt);
	}

	if(myKeys['k'])
	{
		turnRight(dt);
	}

	if(myKeys['r'])
	{
		Reset();
		myKeys['r'] = false;
	}
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	key
	reflect the key that is pressed
*/
/******************************************************************************/
void FPcamera::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
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

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}
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

void FPcamera::moveForward(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	Vector3 view = (target - position).Normalized();
	position += view * CAMERA_SPEED * (float)dt;
	target += view * CAMERA_SPEED * (float)dt;

	position.y = heightOffset + 20.f;
	target.y = position.y + heightDiff;
}

void FPcamera::moveBackward(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	Vector3 view = (target - position).Normalized();
	position -= view * CAMERA_SPEED * (float)dt;
	target -= view * CAMERA_SPEED * (float)dt;

	position.y = heightOffset + 20.f;
	target.y = position.y + heightDiff;
}

void FPcamera::moveLeft(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * CAMERA_SPEED * (float)dt;
	target -= right * CAMERA_SPEED * (float)dt;

	position.y = heightOffset + 20.f;
	target.y = position.y + heightDiff;
}

void FPcamera::moveRight(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * CAMERA_SPEED * (float)dt;
	target += right * CAMERA_SPEED * (float)dt;

	position.y = heightOffset + 20.f;
	target.y = position.y + heightDiff;
}

void FPcamera::moveUp(double dt)
{
	position.y += CAMERA_SPEED * (float)dt;
	target.y += CAMERA_SPEED * (float)dt;
}

void FPcamera::moveDown(double dt)
{
	position.y -= CAMERA_SPEED * (float)dt;
	target.y -= CAMERA_SPEED * (float)dt;
}

void FPcamera::turnLeft(double dt)
{
	//Update the camera direction based on mouse move
	// left-right rotate
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPcamera::turnRight(double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPcamera::turnUp(double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

void FPcamera::turnDown(double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}