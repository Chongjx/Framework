#include "Character.h"

Character::Character(void)
{
	m_iID = 0;
	m_iHealth = 100; 
	m_fDeathTimer = 5.f;
	m_fDeathTime = 0.f;
	enemyTarget = NULL;
}

Character::~Character(void)
{
}
