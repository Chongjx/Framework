/******************************************************************************/
/*!
\file	GameObject.h
\author Chong Jun Xiang
\brief
Create a game object class which stores all its variables
*/
/******************************************************************************/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

#include "MatrixStack.h"
#include "MeshBuilder.h"
#include "Vector3.h"

using std::string;

/******************************************************************************/
/*!
		ENUM GAMEOBJECT_TYPE:
\brief	Define each unique OBJ in the scene
*/
/******************************************************************************/
enum GAMEOBJECT_TYPE
{
		GO_NONE = 0,
		GO_CHARACTER,
		GO_WEAPON,
		GO_BULLET,
		GO_ENVIRONMENT,
		GO_TOTAL, //must be last
};

class GameObject
{
protected:
	GAMEOBJECT_TYPE m_GOType;
	Mesh* m_pMesh;
	Vector3 m_v3Position;
	Mtx44 m_matRotation;
	Vector3 m_v3Scale;
	Vector3 m_v3Velocity;
	float m_fMass;
	bool m_bRender;
	bool m_bReflectLight;
public:
	GameObject(GAMEOBJECT_TYPE typeValue = GO_NONE);
	~GameObject(void);

	virtual void setType(GAMEOBJECT_TYPE type);
	virtual void setMesh(Mesh* mesh);
	virtual void setPosition(Vector3 position);
	virtual void setRotation(Mtx44 rotation);
	virtual void setScale(Vector3 scale);
	virtual void setVelocity(Vector3 velocity);
	virtual void setMass(float mass);
	virtual void setRender(bool render);
	virtual void setReflectLight(bool lighting);
	
	virtual GAMEOBJECT_TYPE getGOTYPE(void) const;
	virtual Mesh* getMesh(void) const;
	virtual Vector3 getPosition(void) const;
	virtual Mtx44 getRotation(void) const;
	virtual Vector3 getScale(void) const;
	virtual Vector3 getVelocity(void) const;
	virtual float getMass(void) const;
	virtual bool getRender(void) const;
	virtual bool getReflectLight(void) const;
};

#endif