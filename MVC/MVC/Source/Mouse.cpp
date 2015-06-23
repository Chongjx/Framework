#include "Mouse.h"

#include <GLFW/glfw3.h>

GLFWwindow* m_window;

Mouse::Mouse(void) :
	current_x(0.0),
	current_y(0.0),
	last_x(0.0),
	last_y(0.0),
	diff_x(0.0),
	diff_y(0.0),
	mouse_yaw(0.f),
	mouse_pitch(0.f),
	sensitivity(1.f),
	bLButtonState(false),
	bRButtonState(false),
	bMButtonState(false),
	dead_zone(200.f)
{
}

Mouse::~Mouse(void)
{
}

void Mouse::Init(void)
{
	this->current_x = 0.0;
	this->current_y = 0.0;

	this->last_x = 0.0;
	this->last_y = 0.0;

	this->diff_x = 0.0;
	this->diff_y = 0.0;

	this->mouse_yaw = this->diff_x * 0.0174555555;	// * 3.142f / 180.f
	this->mouse_pitch = this->diff_y * 0.0174555555;	// * 3.142f / 180.f

	this->sensitivity = 1.f;

	this->bLButtonState = false;
	this->bRButtonState = false;
	this->bMButtonState = false;

	this->dead_zone = 200.f;
}

bool Mouse::Update(void)
{
	int width, height;
	glfwGetCursorPos(m_window, &current_x, &current_y);
	glfwGetWindowSize(m_window, &width, &height);

	// Calculate the difference in positions
	this->diff_x = this->current_x - this->last_x;
	this->diff_y = this->current_y - this->last_y;

	// Calculate yaw and pitch
	this->mouse_yaw = this->diff_x * 0.0174555555;	// * 3.142f / 180.f 
	this->mouse_pitch = this->diff_y * 0.0174555555;	// * 3.142f / 180.f

	// Do a wraparound if the mouse cursor has gone out of the dead zone
	if((this->current_x < this->dead_zone) || (this->current_x > width - this->dead_zone))
	{
		this->current_x = width >> 1;
		glfwSetCursorPos(m_window, current_x, current_y);
	}

	if((this->current_y < this->dead_zone) || (this->current_y > height - this->dead_zone))
	{
		this->current_y = height >> 1;
		glfwSetCursorPos(m_window, current_x, current_y);
	}

	// Store the current position as the last position
	this->last_x = this->current_x;
	this->last_y = this->current_y;

	return true;
}

bool Mouse::IsMousePressed(unsigned short key)	// 0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}

void Mouse::setMousePos(double new_x, double new_y)
{
	glfwSetCursorPos(m_window, new_x, new_y);
}

void Mouse::getMousePos(void)
{
	glfwGetCursorPos(m_window, &current_x, &current_y);
}

double Mouse::getCurrentX(void) const
{
	return this->current_x;
}

double Mouse::getCurrentY(void) const
{
	return this->current_y;
}

double Mouse::getLastX(void) const
{
	return this->last_x;
}

double Mouse::getLastY(void) const
{
	return this->last_y;
}

double Mouse::getDiffX(void) const
{
	return this->diff_x;
}

double Mouse::getDiffY(void) const
{
	return this->diff_y;
}

double Mouse::getMouseYaw(void) const
{
	return this->mouse_yaw;
}

double Mouse::getMousePitch(void) const
{
	return this->mouse_pitch;
}

void Mouse::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

float Mouse::getSensitivity(void) const
{
	return this->sensitivity;
}

void Mouse::setLButtonState(bool state)
{
	this->bLButtonState = state;
}

bool Mouse::getLButtonState(void) const
{
	return this->bLButtonState;
}

void Mouse::setRButtonState(bool state)
{
	this->bRButtonState = state;
}

bool Mouse::getRButtonState(void) const
{
	return this->bRButtonState;
}

void Mouse::setMButtonState(bool state)
{
	this->bMButtonState = state;
}

bool Mouse::getMButtonState(void) const
{
	return this->bMButtonState;
}