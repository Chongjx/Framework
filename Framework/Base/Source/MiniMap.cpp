#include "Minimap.h"

Avatar::Avatar() :
	avatarMesh(NULL),
	xCoord(0.f),
	yCoord(0.f),
	angle(0.f),
	render(false)
{
}

Avatar::~Avatar()
{
}

// Set the Avatar mesh to this class
bool Avatar::setAvatar(Mesh* anAvatar)
{
	if (anAvatar != NULL)
	{
		avatarMesh = anAvatar;
		return true;
	}
	return false;
}

// Set angle of avatar
bool Avatar::setAngle(const float angle)
{
	this->angle = angle;
	return true;
}

// Set position of avatar in minimap
bool Avatar::setPosition(const float x, const float y)
{
	this->xCoord = x;
	this->yCoord = y;
	return true;
}

// Set the avatar to render
bool Avatar::setRender(bool render)
{
	this->render = render;
	return true;
}

// Get the Avatar mesh to this class
Mesh* Avatar::getAvatar(void) const
{
	return avatarMesh;
}

// Get angle
float Avatar::getAngle(void) const
{
	return angle;
}

// Get position x of avatar in minimap
float Avatar::getPosition_x(void)
{
	return xCoord;
}

// Get position y of avatar in minimap
float Avatar::getPosition_y(void)
{
	return yCoord;
}

bool Avatar::getRender(void) const
{
	return render;
}

MiniMap::MiniMap(void)
	: m_MiniMap_Background(NULL)
	, m_MiniMap_Border(NULL)
	, size_x(0)
	, size_y(0)
{
}

MiniMap::~MiniMap(void)
{
	enemyList.clear();
	statictList.clear();
}

// Set the background mesh to this class
bool MiniMap::setBackground(Mesh* aBackground)
{
	if (aBackground != NULL)
	{
		m_MiniMap_Background = aBackground;
		return true;
	}
	return false;
}

// Get the background mesh to this class
Mesh* MiniMap::getBackground(void)
{
	return m_MiniMap_Background;
}

// Set the Border mesh to this class
bool MiniMap::setBorder(Mesh* aBorder)
{
	if (aBorder != NULL)
	{
		m_MiniMap_Border = aBorder;
		return true;
	}
	return false;
}

// Get the Border mesh to this class
Mesh* MiniMap::getBorder(void)
{
	return m_MiniMap_Border;
}

// Set size of minimap (for calculation of avatar in minimap)
bool MiniMap::setSize(const float size_x, const float size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	return true;
}

// Get size of minimap (for calculation of avatar in minimap)
float MiniMap::getSize_x(void)
{
	return size_x;
}

// Get size of minimap (for calculation of avatar in minimap)
float MiniMap::getSize_y(void)
{
	return size_y;
}