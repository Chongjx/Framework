#ifndef BULLET_H
#define BULLET_H

#include "threeDObject.h"

class Bullet : public threeDObject
{
private:
	bool m_bStatus;
	Vector3 m_v3Dir;
	float m_fBulletSpeed;
	float m_fLifeTime;

public:
	Bullet(void);
	~Bullet(void);

	void setStatus(const bool status);
	bool getStatus(void) const;

	void setDir(const Vector3 dir);
	Vector3 getDir(void) const;

	void setBulletSpeed(const float speed);
	float getBulletSpeed(void) const;

	void setLifeTime(const float lifeTime);
	float getLifeTime(void) const;

	void Update(const double dt);
	void Shot(const Vector3 position, const Vector3 dir, const float speed, const float lifeTime);
};

#endif