#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "threeDhitbox.h"
#include "FPcamera.h"
#include "Inventory.h"

class Character : public GameObject
{
public:
	Character(void);
	~Character(void);

	int m_iID;
	int m_iHealth;

	float m_fDeathTimer;
	float m_fDeathTime;

	Character* enemyTarget;

	FPcamera camera;
	threeDhitbox body;
	
	Inventory bagpack;
};

#endif