#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "threeDhitbox.h"
#include "FPcamera.h"

class Character : GameObject
{
public:
	Character(void);
	~Character(void);

	FPcamera userCam;
	threeDhitbox body;

};

#endif