#include "threeDhitbox.h"

threeDhitbox::threeDhitbox(void)
{
	origin.Set(0, 0, 0);
	maxiPoint.Set(0.5f, 0.5f, 0.5f);
	miniPoint.Set(-0.5f, -0.5f, -0.5f);

	length = height = width = 1.0f;

	halfLength = halfHeight = halfWidth = 0.5f;

	name = "DEFAULT_3D_HITBOX";
}

threeDhitbox::threeDhitbox(Vector3 origin, float length, float height, float width, const string name)
{
	this->origin = origin;
	this->length = length;
	this->height = height;
	this->width = width;
	this->name = name;

	halfLength = length/2;
	halfHeight = height/2;
	halfWidth = width/2;

	maxiPoint.Set(origin.x + halfLength, origin.y + halfHeight, origin.z + halfWidth);
	miniPoint.Set(origin.x - halfLength, origin.y - halfHeight, origin.z - halfWidth);
}

threeDhitbox::threeDhitbox(Vector3 maxiPoint, Vector3 miniPoint, const string name)
{
	this->maxiPoint = maxiPoint;
	this->miniPoint = miniPoint;
	this->name = name;

	length = maxiPoint.x - miniPoint.x;
	height = maxiPoint.y - miniPoint.y;
	width = maxiPoint.z - miniPoint.z;

	halfLength = length/2;
	halfHeight = height/2;
	halfWidth = width/2;

	origin.Set(maxiPoint.x - halfLength, maxiPoint.y - halfHeight, maxiPoint.z - halfWidth);
}

threeDhitbox::~threeDhitbox(void)
{
}

Vector3 threeDhitbox::getOrigin(void) const
{
	return origin;
}

Vector3 threeDhitbox::getMaxiPoint(void) const
{
	return maxiPoint;
}

Vector3 threeDhitbox::getMiniPoint(void) const
{
	return miniPoint;
}

float threeDhitbox::getLength(void) const
{
	return length;
}

float threeDhitbox::getHeight(void) const
{
	return height;
}

float threeDhitbox::getWidth(void) const
{
	return width;
}

float threeDhitbox::getHalfLength(void) const
{
	return halfLength;
}

float threeDhitbox::getHalfHeight(void) const
{
	return halfHeight;
}

float threeDhitbox::getHalfWidth(void) const
{
	return halfWidth;
}

string threeDhitbox::getName(void) const
{
	return name;
}