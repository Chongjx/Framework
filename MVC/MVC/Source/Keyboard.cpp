#include "Keyboard.h"

#include <Windows.h>

// handle error if key input exceed range
bool error_handler(unsigned short key)
{
	if (key >= 256)
		return false;

	return true;
}

Keyboard::Keyboard(void)
{
	for (int i = 0; i < 256; ++i)
	{
		keys[i] = false;
	}
}

Keyboard::~Keyboard(void)
{
}

void Keyboard::Init(void)
{
	for (int i = 0; i < 256; ++i)
	{
		keys[i] = false;
	}
}

// Auto switch the status of the key
bool Keyboard::SwitchKeyStatus(unsigned short key)
{
	if (!error_handler(key))
		return false;

	keys[key] = !getKeyStatus(key);
	return true;
}

// Mannually set the key status
bool Keyboard::setKeyStatus(unsigned short key, bool status)
{
	if (!error_handler(key))
		return false;

	keys[key] = status;
	return true;
}

// Get the status of the key
bool Keyboard::getKeyStatus(unsigned short key)
{
	if (!error_handler(key))
		return false;

	return keys[key];
}

// Basic method for checking keyboard 
bool Keyboard::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}