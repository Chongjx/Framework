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
		GO_ENVIRONMENT,
		GO_TOTAL, //must be last
};

/******************************************************************************/
/*!
		Struct Properties:
\brief	Consists of translation, rotation and scale of a basic object
*/
/******************************************************************************/
struct Properties
{
	Mtx44 translation, rotation, scale;

	Properties()
	{
		translation.SetToIdentity();
		rotation.SetToIdentity();
		scale.SetToIdentity();
	}

	Properties& operator=(const Properties& rhs)
	{
		this->translation = rhs.translation;
		this->rotation = rhs.rotation;
		this->scale = rhs.scale;

		return *this;
	}
};

/******************************************************************************/
/*!
		Struct Dimension:
\brief	Consists of length, width and height of a basic object
*/
/******************************************************************************/
struct Dimension
{
	float fLength, fHeight, fDepth;

	Dimension()
	{
		fLength = fHeight = fDepth = 2.f;
	}

	Dimension(float _length, float _height, float _width)
	{
		fLength = _length;
		fHeight = _height;
		fDepth = _width;
	}

	void set(float _length, float _height, float _width = 0.f)
	{
		fLength = _length;
		fHeight = _height;
		fDepth = _width;
	}

	Dimension& operator=(const Dimension& rhs)
	{
		this->fLength = rhs.fLength;
		this->fHeight = rhs.fHeight;
		this->fDepth = rhs.fDepth;

		return *this;
	}
};

class GameObject
{
protected:
	GAMEOBJECT_TYPE m_GOType;
	Mesh* m_pMesh;
	Properties m_TRS;
	Vector3 m_v3Position;
	Vector3 m_v3Velocity;
	Dimension m_Size;
	float m_fMass;
	bool m_bRender;
	bool m_bReflectLight;
public:
	GameObject(GAMEOBJECT_TYPE typeValue = GO_NONE);
	~GameObject(void);

	void setType(GAMEOBJECT_TYPE type);
	void setMesh(Mesh* mesh);
	void setProperties(Properties TRS);
	void setPosition(Vector3 position);
	void setVelocity(Vector3 velocity);
	void setSize(Dimension size);
	void setMass(float mass);
	void setRender(bool render);
	void setReflectLight(bool lighting);
	
	GAMEOBJECT_TYPE getGOTYPE(void) const;
	Mesh* getMesh(void) const;
	Properties getTRS(void) const;
	Vector3 getPosition(void) const;
	Vector3 getVelocity(void) const;
	Dimension getSize(void) const;
	float getMass(void) const;
	bool getRender(void) const;
	bool getReflectLight(void) const;
};

#endif