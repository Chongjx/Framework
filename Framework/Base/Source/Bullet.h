#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "threeDhitbox.h"

class Bullet : GameObject
{
public:
	Bullet(void);
	~Bullet(void);

	Vector3 m_v3Dir;
	threeDhitbox m_BulletBox;
}

#endif