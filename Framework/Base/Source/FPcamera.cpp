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

static const float WALK_SPEED = 200.f;
static const float TURN_SPEED = 200.f;
static const float RUN_SPEED = 400.f;
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

	sCameraType = LAND_CAM;

	for (int i = 0; i < 255; ++i)
	{
		myKeys[i] = false;
	}

	m_bJumping = false;
	JumpVel = 0.0f;
	JUMPMAXSPEED = 200.f;
	JUMPACCEL = 100.f;
	GRAVITY = -200.f;
}

/******************************************************************************/
/*!
\brief	Camera Update function

\param	dt
the time passed since last update
*/
/******************************************************************************/
void FPcamera::Update(double dt, float heightOffset)
{
	if(myKeys['w'])
	{
		if(myKeys['z'])
		{
			if (!m_bJumping)
			{
				Run(dt, heightOffset);
			}
			else
			{
				Walk(dt, heightOffset);
			}
			myKeys['z'] = false;
		}
		else
		{
			Walk(dt, heightOffset);
		}
		myKeys['w'] = false;
	}

	if(myKeys['s'])
	{
		if(myKeys['z'])
		{
			Run(-dt, heightOffset);
			myKeys['z'] = false;
		}
		else
		{
			Walk(-dt, heightOffset);
		}
		myKeys['s'] = false;
	}

	if(myKeys['a'])
	{
		Strafe(-dt, heightOffset);
		myKeys['a'] = false;
	}

	if(myKeys['d'])
	{
		Strafe(dt, heightOffset);
		myKeys['d'] = false;
	}

	if(myKeys['q'])
	{
		moveUp(dt, 5.f);
		myKeys['q'] = false;
	}

	if(myKeys['e'])
	{
		moveDown(dt, 5.f);
		myKeys['e'] = false;
	}

	if(myKeys[32])
	{
		Jump(dt);
		myKeys[32] = false;
	}
	UpdateJump(dt, heightOffset);

	if(Application::camera_pitch != 0)
	{
		Pitch(dt);
	}
	if(Application::camera_yaw != 0)
	{
		Yaw(dt);
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

\param	dt
time passed since last update
\param heightOffset
terrain height
*/
/******************************************************************************/
void FPcamera::UpdateJump(const double dt, float heightOffset)
{
	if(m_bJumping)
	{
		// Factor in gravity
		JumpVel += GRAVITY * dt;

		// Update the camera and target position
		position.y += JumpVel * (float)dt;
		target.y += JumpVel * (float)dt;

		// check if the camera has reached the ground
		float yDiff = target.y - position.y;
		if(position.y <= heightOffset + 20.f)
		{
			position.y = heightOffset + 20.f;
			target.y = yDiff + position.y;
			JumpVel = 0.0f;
			m_bJumping = false;
		}
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

\param	sCameraType
camera type
*/
/******************************************************************************/
void FPcamera::SetCameraType(CAM_TYPE sCameraType)
{
	this->sCameraType = sCameraType;
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

\return	CAM_TYPE
camera type
*/
/******************************************************************************/
FPcamera::CAM_TYPE FPcamera::GetCameraType(void)
{
	return this->sCameraType;
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

// basic methods
void FPcamera::moveForward(const double dt, float heightOffset, bool run)
{
	float heightDiff = target.y - position.y;
	Vector3 targetY = target;
	targetY.y = position.y;

	Vector3 view = (target - position).Normalized();

	if (!run)
	{
		position += view * WALK_SPEED * (float)dt;
		target += view * WALK_SPEED * (float)dt;
	}

	else
	{
		position += view * RUN_SPEED * (float)dt;
		target += view * RUN_SPEED * (float)dt;
	}

	if(!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPcamera::moveBackward(const double dt, float heightOffset, bool run)
{
	float heightDiff = target.y - position.y;
	Vector3 targetY = target;
	targetY.y = position.y;

	Vector3 view = (target - position).Normalized();
	if (!run)
	{
		position -= view * WALK_SPEED * (float)dt;
		target -= view * WALK_SPEED * (float)dt;
	}
	else
	{
		position -= view * RUN_SPEED * (float)dt;
		target -= view * RUN_SPEED * (float)dt;
	}

	if(!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPcamera::moveLeft(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;
	Vector3 targetY = target;
	targetY.y = position.y;

	Vector3 view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * WALK_SPEED * (float)dt;
	target -= right * WALK_SPEED * (float)dt;

	if(!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPcamera::moveRight(const double dt, float heightOffset)
{
	float heightDiff = target.y - position.y;
	Vector3 targetY = target;
	targetY.y = position.y;

	Vector3 view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * WALK_SPEED * (float)dt;
	target += right * WALK_SPEED * (float)dt;

	if(!m_bJumping)
	{
		position.y = heightOffset + 20.f;
		target.y = position.y + heightDiff;
	}
}

void FPcamera::moveUp(const double dt, float heightOffset)
{
	position.y += WALK_SPEED * (float)dt + heightOffset * dt;
	target.y += WALK_SPEED * (float)dt + heightOffset * dt;
}

void FPcamera::moveDown(const double dt, float heightOffset)
{
	position.y -= WALK_SPEED * (float)dt + heightOffset * dt;
	target.y -= WALK_SPEED * (float)dt + heightOffset * dt;
}

void FPcamera::lookLeft(const double dt)
{
	//Update the camera direction based on mouse move
	// left-right rotate
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-TURN_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPcamera::lookRight(const double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-TURN_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

void FPcamera::lookUp(const double dt)
{
	float pitch = (float)(-TURN_SPEED * Application::camera_pitch * (float)dt);
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

void FPcamera::lookDown(const double dt)
{
	float pitch = (float)(-TURN_SPEED * Application::camera_pitch * (float)dt);
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

void FPcamera::lookUp(const double dt, float upValue)
{
	float pitch = (float)(-TURN_SPEED * upValue * (float)dt);
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

void FPcamera::lookDown(const double dt, float downValue)
{
	float pitch = (float)(-TURN_SPEED * downValue * (float)dt);
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

void FPcamera::SpinClockwise(const double dt)
{
	float angle = (float)(TURN_SPEED * (float)dt);
	Vector3 view = (target - position).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(angle, 0, 0, 1);
	view = rotation * view;
	target = position + view;
}

void FPcamera::SpinCounterClockwise(const double dt)
{
	float angle = (float)(-TURN_SPEED * (float)dt);
	Vector3 view = (target - position).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(angle, 0, 0, 1);
	view = rotation * view;
	target = position + view;
}

void FPcamera::Pitch(const double dt)
{
	if (Application::camera_pitch > 0.0)
	{
		lookUp(dt);
	}

	else if (Application::camera_pitch < 0.0)
	{
		lookDown(dt);
	}
}

void FPcamera::Yaw(const double dt)
{
	if (Application::camera_yaw > 0.0)
	{
		lookRight(dt);
	}

	else if (Application::camera_yaw < 0.0)
	{
		lookLeft(dt);
	}
}

void FPcamera::Walk(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveForward(dt, heightOffset);
	}
	else if (dt < 0)
	{
		moveBackward(abs(dt), heightOffset);
	}
	//SpinCounterClockwise(dt);
}

void FPcamera::Run(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveForward(dt, heightOffset, true);
	}
	else if (dt < 0)
	{
		moveBackward(abs(dt), heightOffset, true);
	}
}

void FPcamera::Strafe(const double dt, float heightOffset)
{
	if (dt > 0)
	{
		moveRight(dt, heightOffset);
	}
	else  if (dt < 0)
	{
		moveLeft(abs(dt), heightOffset);
	}
}

void FPcamera::Jump(const double dt)
{
	if (m_bJumping == false)
	{
		m_bJumping = true;

		// Calculate the jump velocity
		JumpVel = JUMPACCEL;

		if(JumpVel > JUMPMAXSPEED)
		{
			JumpVel -= JUMPMAXSPEED;
		}
	}
}

void FPcamera::Crouch(const double dt)
{

}