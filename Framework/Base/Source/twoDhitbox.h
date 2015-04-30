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

#include <string>
#include <vector>

#include "Vector2.h"

using std::string;
using std::vector;

/******************************************************************************/
/*!
		Class twoDhitbox:
\brief	To store hitbox position, origin, maximum and minimum points, length and width.
*/
/******************************************************************************/
class twoDhitbox
{
private:
	Vector2 m_v2MidPoint;
	Vector2 m_v2BottomRight, m_v2TopRight, m_v2TopLeft, m_v2BottomLeft;

	float m_fLength;
	float m_fHeight;

	float m_fHalfLength;
	float m_fHalfHeight;

    string m_sName;
public:
	twoDhitbox(void);
	~twoDhitbox(void);

	void create2Dhitbox(Vector2 midPoint, float length, float width, const string name);
	void create2Dhitbox(Vector2 bottomRight, Vector2 topRight, Vector2 topLeft, Vector2 bottomLeft, const string name);

	float getLength(void) const;
	float getHeight(void) const;

	float getHalfLength(void) const;
	float getHalfHeight(void) const;
	
	string getName(void) const;

	friend void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName);
	friend void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName);
	friend void check2DCollision(Vector2 &user, vector<twoDhitbox> &target, bool &collide, string &boxName);
	friend void check2DCollision(Vector2 &user, twoDhitbox &target, bool &collide, string &boxName);
};

#endif