#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "threeDhitbox.h"
#include "FPcamera.h"

class Character : public GameObject
{
public:
	Character(void);
	~Character(void);

	FPcamera userCam;
	threeDhitbox body;

	//Weapon* 
};

#endif