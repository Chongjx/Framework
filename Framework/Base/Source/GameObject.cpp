#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue) : m_GOType(typeValue), m_bRender(false), m_fMass(1.f)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::setType(GAMEOBJECT_TYPE type)
{
	this->m_GOType = type;
}

void GameObject::setMesh(Mesh* mesh)
{
	this->m_pMesh = mesh;
}

void GameObject::setProperties(Properties TRS)
{
	this->m_TRS = TRS;
}

void GameObject::setPosition(Vector3 position)
{
	this->m_v3Position = position;
}

void GameObject::setVelocity(Vector3 velocity)
{
	this->m_v3Velocity = velocity;
}

void GameObject::setSize(Dimension size)
{
	this->m_Size = size;
}

void GameObject::setMass(float mass)
{
	this->m_fMass = mass;
}

void GameObject::setRender(bool render)
{
	this->m_bRender = render;
}

void GameObject::setReflectLight(bool lighting)
{
	this->m_bReflectLight = lighting;
}

GAMEOBJECT_TYPE GameObject::getGOTYPE(void) const
{
	return this->m_GOType;
}

Mesh* GameObject::getMesh(void) const
{
	return this->m_pMesh;
}

Properties GameObject::getTRS(void) const
{
	return this->m_TRS;
}

Vector3 GameObject::getPosition(void) const
{
	return this->m_v3Position;
}

Vector3 GameObject::getVelocity(void) const
{
	return this->m_v3Velocity;
}

Dimension GameObject::getSize(void) const
{
	return this->m_Size;
}

float GameObject::getMass(void) const
{
	return this->m_fMass;
}

bool GameObject::getRender(void) const
{
	return this->m_bRender;
}

bool GameObject::getReflectLight(void) const
{
	return this->m_bReflectLight;
}