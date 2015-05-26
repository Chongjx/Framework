#include "Minimap.h"

MiniMap::MiniMap(void)
	: m_MiniMap_Background(NULL)
	, m_MiniMap_Border(NULL)
	, m_MiniMap_Avatar(NULL)
	, angle(0)
	, x(0)
	, y(0)
	, size_x(0)
	, size_y(0)
{
}

MiniMap::~MiniMap(void)
{
}

// Set the background mesh to this class
bool MiniMap::SetBackground(Mesh* aBackground)
{
	if (aBackground != NULL)
	{
		m_MiniMap_Background = aBackground;
		return true;
	}
	return false;
}

// Get the background mesh to this class
Mesh* MiniMap::GetBackground(void)
{
	return m_MiniMap_Background;
}

// Set the Border mesh to this class
bool MiniMap::SetBorder(Mesh* aBorder)
{
	if (aBorder != NULL)
	{
		m_MiniMap_Border =
			aBorder;
		return true;
	}
	return false;
}

// Get the Border mesh to this class
Mesh* MiniMap::GetBorder(void)
{
	return m_MiniMap_Border;
}

// Set the Avatar mesh to this class
bool MiniMap::SetAvatar(Mesh* anAvatar)
{
	if (anAvatar != NULL)
	{
		m_MiniMap_Avatar = anAvatar;
		return true;
	}
	return false;
}

// Get the Avatar mesh to this class
Mesh* MiniMap::GetAvatar(void)
{
	return m_MiniMap_Avatar;
}

// Set angle of avatar
bool MiniMap::SetAngle(const int angle)
{
	this->angle = angle;
	return true;
}

// Get angle
int MiniMap::GetAngle(void)
{
	return angle;
}

// Set position of avatar in minimap
bool MiniMap::SetPosition(const int x, const int y)
{
	this->x = x;
	this->y = y;
	return true;
}

// Get position x of avatar in minimap
int MiniMap::GetPosition_x(void)
{
	return x;
}

// Get position y of avatar in minimap
int MiniMap::GetPosition_y(void)
{
	return y;
}

// Set size of minimap (for calculation of avatar in minimap)
bool MiniMap::SetSize(const int size_x, const int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	return true;
}

// Get size of minimap (for calculation of avatar in minimap)
int MiniMap::GetSize_x(void)
{
	return size_x;
}

// Get size of minimap (for calculation of avatar in minimap)
int MiniMap::GetSize_y(void)
{
	return size_y;
}