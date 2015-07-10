#include "Particle.h"

Particle::Particle(void)
{
}

Particle::~Particle(void)
{
}

void Particle::setGravity(bool gravity)
{
	this->m_bGravity = gravity;
}

bool Particle::getGravity(void) const
{
	return this->m_bGravity;
}

void Particle::Update(double dt)
{
}