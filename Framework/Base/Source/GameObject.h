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

static const Vector3 GRAVITY(0, -9.8, 0);

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

/******************************************************************************/
/*!
		Struct properties:
\brief	Consists of translation, rotation and scale of a basic object
*/
/******************************************************************************/
struct Properties
{
	Mtx44 modelProperties, translation, rotation, scale;

	Properties()
	{
		modelProperties.SetToIdentity();
		translation.SetToIdentity();
		rotation.SetToIdentity();
		scale.SetToIdentity();
	}
};

class GameObject
{
protected:
	GAMEOBJECT_TYPE m_GOType;
	Mesh* m_pMesh;
	Vector3 m_v3Position;
	Properties TRS;
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
	virtual void setTRS(Properties _TRS);
	virtual void setVelocity(Vector3 velocity);
	virtual void setMass(float mass);
	virtual void setRender(bool render);
	virtual void setReflectLight(bool lighting);
	
	virtual GAMEOBJECT_TYPE getGOTYPE(void) const;
	virtual Mesh* getMesh(void) const;
	virtual Vector3 getPosition(void) const;
	virtual Properties getProperties(void);
	virtual Vector3 getVelocity(void) const;
	virtual float getMass(void) const;
	virtual bool getRender(void) const;
	virtual bool getReflectLight(void) const;
};

#endif