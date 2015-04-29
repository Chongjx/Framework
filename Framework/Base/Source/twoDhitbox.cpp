/******************************************************************************/
/*!
\file	twoDhitbox.cpp
\author Jun Xiang
\brief
Hitbox creation and holds its properties
*/
/******************************************************************************/
#include "twoDhitbox.h"

/******************************************************************************/
/*!
\brief
twoDhitbox default constructor
*/
/******************************************************************************/
twoDhitbox::twoDhitbox(void)
{
	origin.Set(0, 0);
	maxiPoint.Set(0.5f, 0.5f);
	maxiPoint.Set(-0.5f, -0.5f);

	length = width = 1.0f;

	halfLength = halfWidth = 0.5f;

	name = "DEFAULT_2D_HITBOX";
}

/******************************************************************************/
/*!
\brief
twoDhitbox default destructor
*/
/******************************************************************************/
twoDhitbox::~twoDhitbox(void)
{
}


void twoDhitbox::create2Dhitbox(Vector2 origin, float length, float width, const string name)
{
	this->origin = origin;
	this->length = length;
	this->width = width;
	this->name = name;

	halfLength = length * 0.5f;
	halfWidth = width * 0.5f;

	maxiPoint.Set(origin.x + halfLength, origin.y + halfWidth);
	miniPoint.Set(origin.x - halfLength, origin.y - halfWidth);
}

void twoDhitbox::create2Dhitbox(Vector2 maxiPoint, Vector2 miniPoint, const string name)
{
	this->maxiPoint = maxiPoint;
	this->miniPoint = miniPoint;
	this->name = name;

	length = maxiPoint.x - miniPoint.x;
	width = maxiPoint.y - miniPoint.y;

	halfLength = length * 0.5f;
	halfWidth = width * 0.5f;

	origin.Set(maxiPoint.x - halfLength, maxiPoint.y - halfWidth);
}

Vector2 twoDhitbox::getOrigin(void) const
{
	return origin;
}

Vector2 twoDhitbox::getMaxiPoint(void) const
{
	return maxiPoint;
}

Vector2 twoDhitbox::getMiniPoint(void) const
{
	return miniPoint;
}

float twoDhitbox::getLength(void) const
{
	return length;
}

float twoDhitbox::getWidth(void) const
{
	return width;
}

float twoDhitbox::getHalfLength(void) const
{
	return halfLength;
}

float twoDhitbox::getHalfWidth(void) const
{
	return halfWidth;
}

string twoDhitbox::getName(void) const
{
	return name;
}

void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.getMiniPoint().x <= target[i].getMaxiPoint().x &&
			user.getMaxiPoint().x >= target[i].getMiniPoint().x &&
			user.getMiniPoint().y <= target[i].getMaxiPoint().y &&
			user.getMaxiPoint().y >= target[i].getMiniPoint().y)

		{
			collide = true;
			boxName = target[i].getName();
			break;
		}
	}
}

void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.getMiniPoint().x <= target.getMaxiPoint().x &&
		user.getMaxiPoint().x >= target.getMiniPoint().x &&
		user.getMiniPoint().y <= target.getMaxiPoint().y &&
		user.getMaxiPoint().y >= target.getMiniPoint().y)

	{
		collide = true;
		boxName = target.getName();
	}
}

void check2DCollision(Vector2 &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	for (int i = 0; i < target.size(); ++i)
	{
		if (user.x <= target[i].getMaxiPoint().x &&
			user.x >= target[i].getMiniPoint().x &&
			user.y <= target[i].getMaxiPoint().y &&
			user.y >= target[i].getMiniPoint().y)

		{
			collide = true;
			boxName = target[i].getName();
		}
	}
}

void check2DCollision(Vector2 &user, twoDhitbox &target, bool &collide, string &boxName)
{
	if (user.x <= target.getMaxiPoint().x &&
		user.x >= target.getMiniPoint().x &&
		user.y <= target.getMaxiPoint().y &&
		user.y >= target.getMiniPoint().y)

	{
		collide = true;
		boxName = target.getName();
	}
}