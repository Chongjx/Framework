#include "threeDObject.h"

threeDObject::threeDObject(void)
{
}

threeDObject::~threeDObject(void)
{
}

void threeDObject::setHitBox(threeDhitbox hitbox)
{
	this->m_3Dhitbox = hitbox;
}

threeDhitbox threeDObject::getHitBox(void)
{
	Mtx44 translation, rotation, scale;
	translation.SetToIdentity();
	rotation.SetToIdentity();
	scale.SetToIdentity();

	translation.SetToTranslation(this->getPosition().x, this->getPosition().y, this->getPosition().z);
	rotation = this->getRotation();
	scale.SetToScale(this->getScale().x, this->getScale().y, this->getScale().z);

	Mtx44 vertex = (translation * rotation *scale);

	updateHitBox(this->m_3Dhitbox, vertex);

	return this->m_3Dhitbox;
}