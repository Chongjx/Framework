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

	halfLength = length/2;
	halfWidth = width/2;

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

	halfLength = length/2;
	halfWidth = width/2;

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