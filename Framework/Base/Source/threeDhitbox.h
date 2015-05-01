/******************************************************************************/
/*!
\file	threeDhitbox.h
\author Jun Xiang
\brief
Create a 3D hitbox
*/
/******************************************************************************/
#ifndef THREE_D_HITBOX_H
#define THREE_D_HITBOX_H

#include <string>
#include <vector>

#include "Vector3.h"
#include "MyMath.h"

using std::string;
using std::vector;
using namespace Math;

/******************************************************************************/
/*!
		Class threeDhitbox:
\brief	To store hitbox midpoint, length, height, depth and unit vectors
*/
/******************************************************************************/
class threeDhitbox
{
private:
    Vector3 m_v3MidPoint;

	float m_fLength;
	float m_fHeight;
	float m_fDepth;

	float m_fHalfLength;
	float m_fHalfHeight;
	float m_fHalfDepth;

	Vector3 m_v3UnitVecX;
	Vector3 m_v3UnitVecY;
	Vector3 m_v3UnitVecZ;

    string m_sName;
public:
	threeDhitbox(void);
	~threeDhitbox(void);

	void create3Dhitbox(Vector3 midPoint, float length, float height, float depth, const string name);
	void create3Dhitbox(Vector3 frontBottomRight, Vector3 frontTopRight, Vector3 frontTopLeft, Vector3 frontBottomLeft, Vector3 backBottomRight, Vector3 backTopRight, Vector3 backTopLeft, Vector3 backBottomLeft, const string name);

	Vector3 getMidPoint(void) const;
	float getLength(void) const;
	float getHeight(void) const;
	float getDepth(void) const;

	float getHalfLength(void) const;
	float getHalfHeight(void) const;
	float getHalfDepth(void) const;
	
	string getName(void) const;

	friend void check3DCollision(threeDhitbox &user, vector<threeDhitbox> &target, bool &collide, string &boxName);
	friend void check3DCollision(threeDhitbox &user, threeDhitbox &target, bool &collide, string &boxName);
};

#endif