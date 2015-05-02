#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "threeDhitbox.h"

class Bullet : public GameObject
{
public:
	Bullet(void);
	~Bullet(void);

	Vector3 m_v3Dir;
	float m_fBulletSpeed;
	threeDhitbox m_BulletBox;

	void UpdateHitBox(void);
};

#endif