#ifndef THREE_D_OBJECT_H
#define THREE_D_OBJECT_H

#include "GameObject.h"
#include "threeDhitbox.h"

class threeDObject : public GameObject
{
private:
	threeDhitbox m_3Dhitbox;
	string objectName;
public:
	threeDObject(void);
	~threeDObject(void);

	void setObjName(string name);
	string getObjName(void) const;

	void setHitBox(threeDhitbox threeDhitbox);
	threeDhitbox getHitBox(void);
};

#endif