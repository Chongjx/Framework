#ifndef PARTICLE_H
#define PARTICLE_H

#include "threeDObject.h"

class Particle : public threeDObject
{
private:
	bool m_bGravity;
public:
	Particle(void);
	~Particle(void);

	virtual void setGravity(bool gravity);
	virtual bool getGravity(void) const;

	virtual void Update(double dt);
};

#endif