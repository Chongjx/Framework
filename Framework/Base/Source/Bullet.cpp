#include "Bullet.h"

Bullet::Bullet()
{
	m_v3Dir.Set(0.f, 0.f, 1.f);
	m_BulletBox.create3Dhitbox(Vector3(0, 0, 0), 1.f, 1.f, 1.f, "CLASSIC BULLET");
}

Bullet::~Bullet()
{
}