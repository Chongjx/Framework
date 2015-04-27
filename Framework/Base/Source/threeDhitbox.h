#ifndef THREE_D_HITBOX_H
#define THREE_D_HITBOX_H

#include "Vector3.h"
#include <string>

using std::string;

class threeDhitbox
{
private:
    Vector3 origin;
    Vector3 maxiPoint;
	Vector3 miniPoint;

	float length;
	float height;
	float width;

	float halfLength;
	float halfHeight;
	float halfWidth;

    string name;
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
};

#endif