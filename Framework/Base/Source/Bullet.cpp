#include "Bullet.h"

Bullet::Bullet(void) : m_bStatus(false), m_fBulletSpeed(0), m_fLifeTime(0)
{
	m_BulletBox.create3Dhitbox(Vector3(0.f, 0.f, 0.f), 0.5f, 0.5f, 0.5f, "CLASSIC BULLET"); 
	m_v3Dir.Set(0.0f, 0.0f, 0.0f);
}

Bullet::~Bullet(void)
{
}

void Bullet::setStatus(const bool status)
{
	this->m_bStatus = status;
}

bool Bullet::getStatus(void) const
{
	return this->m_bStatus;
}

void Bullet::setDir(const Vector3 dir)
{
	this->m_v3Dir = dir;
}

Vector3 Bullet::getDir(void) const
{
	return this->m_v3Dir;
}

void Bullet::setBulletSpeed(const float speed)
{
	this->m_fBulletSpeed = speed;
}

float Bullet::getBulletSpeed(void) const
{
	return this->m_fBulletSpeed;
}

void Bullet::setLifeTime(const float lifeTime)
{
	this->m_fLifeTime = lifeTime;
}

float Bullet::getLifeTime(void) const
{
	return this->m_fLifeTime;
}

void Bullet::setBulletBox(threeDhitbox bulletBox)
{
	this->m_BulletBox = bulletBox;
}

threeDhitbox Bullet::getBulletBox(void)
{
	return this->m_BulletBox;
}

void Bullet::Update(const double dt)
{
	if (getStatus() == true)
	{
		setPosition(getPosition() + getDir() * getBulletSpeed() * dt);

		this->getHitBox();

		setLifeTime(getLifeTime() - dt);

		if (getLifeTime() < 0)
		{
			setStatus(false);
		}
	}
}

void Bullet::Shot(const Vector3 position, const Vector3 dir, const float speed, const float lifeTime)
{
	this->m_v3Position = position;
	this->m_v3Dir = dir;
	this->m_fBulletSpeed = speed;
	this->m_fLifeTime = lifeTime;
	this->m_bStatus = true;
}