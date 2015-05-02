#include "Bullet.h"

Bullet::Bullet(void)
{
	m_BulletBox.create3Dhitbox(Vector3(0.f, 0.f, 0.f), 0.5f, 0.5f, 0.5f, "CLASSIC BULLET"); 
	m_fBulletSpeed = 100.f;
	m_v3Dir.Set(0.0f, 0.0f, 0.0f);
}

Bullet::~Bullet(void)
{
}

void Bullet::UpdateHitBox(void)
{
}