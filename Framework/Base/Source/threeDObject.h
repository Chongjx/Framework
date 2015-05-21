#ifndef THREE_D_OBJECT_H
#define THREE_D_OBJECT_H

#include "GameObject.h"
#include "threeDhitbox.h"

class threeDObject : public GameObject
{
private:
	threeDhitbox m_3Dhitbox;
public:
	threeDObject(void);
	~threeDObject(void);

	void setHitBox(threeDhitbox threeDhitbox);
	threeDhitbox getHitBox(void);
};

#endif