#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue) : m_GOType(typeValue), m_bRender(false), m_fMass(1.f), m_v3Position(0, 0, 0), m_v3Scale(1, 1, 1)
{
	m_matRotation.SetToIdentity();
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

void GameObject::setPosition(Vector3 position)
{
	this->m_v3Position = position;
}

void GameObject::setRotation(Mtx44 rotation)
{
	this->m_matRotation = rotation;
}

void GameObject::setScale(Vector3 scale)
{
	this->m_v3Scale = scale;
}

void GameObject::setVelocity(Vector3 velocity)
{
	this->m_v3Velocity = velocity;
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

Vector3 GameObject::getPosition(void) const
{
	return this->m_v3Position;
}

Mtx44 GameObject::getRotation(void) const
{
	return this->m_matRotation;
}

Vector3 GameObject::getScale(void) const
{
	return this->m_v3Scale;
}

Vector3 GameObject::getVelocity(void) const
{
	return this->m_v3Velocity;
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