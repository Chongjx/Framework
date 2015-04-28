/******************************************************************************/
/*!
\file	twoDhitbox.h
\author Jun Xiang
\brief
Create a 2D hitbox
*/
/******************************************************************************/
#ifndef TWO_D_HITBOX_H
#define TWO_D_HITBOX_H

#include "Vector2.h"
#include <string>

using std::string;

/******************************************************************************/
/*!
		Class twoDhitbox:
\brief	To store hitbox position, origin, maximum and minimum points, length and width.
*/
/******************************************************************************/
class twoDhitbox
{
private:
    Vector2 origin;
    Vector2 maxiPoint;
	Vector2 miniPoint;

	float length;
	float width;

	float halfLength;
	float halfWidth;

    string name;
public:
	twoDhitbox(void);
	~twoDhitbox(void);

	void create2Dhitbox(Vector2 origin, float length, float width, const string name);
	void create2Dhitbox(Vector2 maxiPoint, Vector2 miniPoint, const string name);

	Vector2 getOrigin(void) const;
	Vector2 getMaxiPoint(void) const;
	Vector2 getMiniPoint(void) const;

	float getLength(void) const;
	float getWidth(void) const;

	float getHalfLength(void) const;
	float getHalfWidth(void) const;
	
	string getName(void) const;
};

#endif