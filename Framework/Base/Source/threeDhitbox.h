#ifndef THREE_D_HITBOX_H
#define THREE_D_HITBOX_H

#include <string>
#include <vector>

#include "Vector3.h"
#include "MyMath.h"

using std::string;
using std::vector;
using namespace Math;

class threeDhitbox
{
private:
    Vector3 m_v3MidPoint;
	Vector3 m_v3BottomRight, m_v3TopRight, m_v3TopLeft, m_v3BottomLeft;

	float m_fLength;
	float m_fHeight;

	float m_fHalfLength;
	float m_fHalfHeight;

	Vector3 m_v2UnitVecX;
	Vector3 m_v2UnitVecY;

    string m_sName;
public:
	threeDhitbox(void);
	threeDhitbox(Vector3 origin, float length, float height, float width, const string name);
	threeDhitbox(Vector3 maxiPoint, Vector3 miniPoint, const string name);
	~threeDhitbox(void);

	Vector3 getOrigin(void) const;
	Vector3 getMaxiPoint(void) const;
	Vector3 getMiniPoint(void) const;

	float getLength(void) const;
	float getHeight(void) const;
	float getWidth(void) const;

	float getHalfLength(void) const;
	float getHalfHeight(void) const;
	float getHalfWidth(void) const;
	
	string getName(void) const;

	friend void check3DCollision(threeDhitbox &user, vector<threeDhitbox> &target, bool &collide, string &boxName);
	friend void check3DCollision(threeDhitbox &user, threeDhitbox &target, bool &collide, string &boxName);
};

#endif