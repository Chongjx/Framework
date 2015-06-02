#include "threeDObject.h"

threeDObject::threeDObject(void)
{
}

threeDObject::~threeDObject(void)
{
}

void threeDObject::setObjName(string name)
{
	this->objectName = name;
}

string threeDObject::getObjName(void) const
{
	return this->objectName;
}

void threeDObject::setHitBox(threeDhitbox hitbox)
{
	this->m_3Dhitbox = hitbox;
}

threeDhitbox threeDObject::getHitBox(void)
{
	return this->m_3Dhitbox;
}

void threeDObject::updateHitbox(void)
{
	m_3Dhitbox.setMidPoint(this->m_v3Position);
	Mtx44 vertex = this->getProperties().modelProperties;

	m_3Dhitbox.create3Dhitbox
		(vertex * Vector3(m_3Dhitbox.getHalfLength(), -m_3Dhitbox.getHalfHeight(), m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(m_3Dhitbox.getHalfLength(), m_3Dhitbox.getHalfHeight(),m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(-m_3Dhitbox.getHalfLength(), m_3Dhitbox.getHalfHeight(), m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(-m_3Dhitbox.getHalfLength(), -m_3Dhitbox.getHalfHeight(), m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(m_3Dhitbox.getHalfLength(), -m_3Dhitbox.getHalfHeight(), -m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(m_3Dhitbox.getHalfLength(), m_3Dhitbox.getHalfHeight(), -m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(-m_3Dhitbox.getHalfLength(), m_3Dhitbox.getHalfHeight(), -m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(),
		vertex * Vector3(-m_3Dhitbox.getHalfLength(), -m_3Dhitbox.getHalfHeight(), -m_3Dhitbox.getHalfDepth()) + m_3Dhitbox.getMidPoint(), m_3Dhitbox.getName());
}