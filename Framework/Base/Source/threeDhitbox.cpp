/******************************************************************************/
/*!
\file	threeDhitbox.cpp
\author Jun Xiang
\brief
Hitbox creation and holds its properties. Collision checks included
*/
/******************************************************************************/
#include "threeDhitbox.h"

/******************************************************************************/
/*!
\brief
threeDhitbox default constructor
*/
/******************************************************************************/
threeDhitbox::threeDhitbox(void)
{
	m_v3MidPoint.Set(0, 0, 0);

	m_fLength = m_fHeight = m_fDepth = 1.0f;
	m_fHalfLength = m_fHalfHeight = m_fHalfDepth = 0.5f;

	m_v3UnitVecX.Set(0.0f, 0.0f, 0.0f);
	m_v3UnitVecY.Set(0.0f, 0.0f, 0.0f);
	m_v3UnitVecZ.Set(0.0f, 0.0f, 0.0f);

	m_sName = "DEFAULT_3D_HITBOX";
}

/******************************************************************************/
/*!
\brief
twoDhitbox default destructor
*/
/******************************************************************************/
threeDhitbox::~threeDhitbox(void)
{
}

/******************************************************************************/
/*!
\brief
overloaded twoDhitbox create function. Assuming the hitbox is parrallel to x, y and z axis.

\param midPoint
	centre point of the hitbox Vector2

\param length
	length of the hitbox float

\param height
	height of the hitbox float

\param depth
	depth of the hitbox float

\ param name
	name of the hitbox string
*/
/******************************************************************************/
void threeDhitbox::create3Dhitbox(Vector3 midPoint, float length, float height, float depth, const string name)
{
	
	Vector3 temp_v3FrontBottomRight, temp_v3FrontTopRight, temp_v3FrontBottomLeft, temp_v3BackBottomRight;

	this->m_v3MidPoint = midPoint;
	this->m_fLength = length;
	this->m_fHeight = height;
	this->m_fDepth = depth;
	this->m_sName = name;

	this->m_fHalfLength = length * 0.5f;
	this->m_fHalfHeight = height * 0.5f;
	this->m_fHalfDepth = depth * 0.5f;

	temp_v3FrontBottomRight.Set(m_v3MidPoint.x + m_fHalfLength, m_v3MidPoint.y - m_fHalfHeight, m_v3MidPoint.z + m_fHalfDepth);
	temp_v3FrontTopRight.Set(m_v3MidPoint.x + m_fHalfLength, m_v3MidPoint.y + m_fHalfHeight, m_v3MidPoint.z + m_fHalfDepth);
	temp_v3FrontBottomLeft.Set(m_v3MidPoint.x - m_fHalfLength, m_v3MidPoint.y - m_fHalfHeight, m_v3MidPoint.z + m_fHalfDepth);
	temp_v3BackBottomRight.Set(m_v3MidPoint.x + m_fHalfLength, m_v3MidPoint.y - m_fHalfHeight, m_v3MidPoint.z - m_fHalfDepth );

	this->m_v3UnitVecX = (temp_v3FrontBottomRight - temp_v3FrontBottomLeft).Normalized();
	this->m_v3UnitVecY = (temp_v3FrontTopRight - temp_v3FrontBottomRight).Normalized();
	this->m_v3UnitVecZ = (temp_v3FrontBottomRight - temp_v3BackBottomRight).Normalized();
}

/******************************************************************************/
/*!
\brief
overloaded twoDhitbox create function. Providing the corners of the hitbox to create

\param frontBottomRight
	front bottom right corner of the hitbox Vector3

\param frontTopRight
	front top right corner of the hitbox Vector3

\param frontTopLeft
	front top left corner of the hitbox Vector3

\param frontBottomLeft
	front bottom left corner of the hitbox Vector3

\param backBottomRight
	back bottom right corner of the hitbox Vector3

\param backTopRight
	back top right corner of the hitbox Vector3

\param backTopLeft
	back top left corner of the hitbox Vector3

\param backBottomLeft
	back bottom left corner of the hitbox Vector3

\ param name
	name of the hitbox string
*/
/******************************************************************************/
void threeDhitbox::create3Dhitbox(Vector3 frontBottomRight, Vector3 frontTopRight, Vector3 frontTopLeft, Vector3 frontBottomLeft, Vector3 backBottomRight, Vector3 backTopRight, Vector3 backTopLeft, Vector3 backBottomLeft, const string name)
{
	this->m_sName = name;

	this->m_fLength = (frontBottomRight - frontBottomLeft).Length();
	this->m_fHeight = (frontTopRight - frontBottomRight).Length();
	this->m_fDepth = (frontBottomRight - backBottomRight).Length();

	this->m_fHalfLength = m_fLength * 0.5f;
	this->m_fHalfHeight = m_fHeight * 0.5f;
	this->m_fHalfDepth = m_fDepth * 0.5f;

	this->m_v3UnitVecX = (frontBottomRight - frontBottomLeft).Normalized();
	this->m_v3UnitVecY = (frontTopRight - frontBottomRight).Normalized();
	this->m_v3UnitVecZ = (frontBottomRight - backBottomRight).Normalized();

	this->m_v3MidPoint.Set(frontBottomRight.x - m_fHalfLength, frontBottomRight.y + m_fHalfHeight, frontBottomRight.z - m_fHalfDepth);
}

/******************************************************************************/
/*!
\brief	threeDhitbox getter functions

\return	Vector3
    Mid Point of the hitbox
*/
/******************************************************************************/
Vector3 threeDhitbox::getMidPoint(void) const
{
	return this->m_v3MidPoint;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
    Length of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getLength(void) const
{
	return this->m_fLength;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
    Height of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getHeight(void) const
{
	return this->m_fHeight;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
    Depth of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getDepth(void) const
{
	return this->m_fDepth;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
     Half length of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getHalfLength(void) const
{
	return this->m_fHalfLength;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
     Half height of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getHalfHeight(void) const
{
	return this->m_fHalfHeight;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
     Half width of the hitbox
*/
/******************************************************************************/
float threeDhitbox::getHalfDepth(void) const
{
	return this->m_fHalfDepth;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	string
      name of the hitbox
*/
/******************************************************************************/
string threeDhitbox::getName(void) const
{
	return this->m_sName;
}

/******************************************************************************/
/*!
\brief	overloaded 3D collision checking function using Separating Axis Theorem
		checking a hitbox against a vector of hitbox

\param	user
    hitbox of the user

\param target
	hitbox of the target to check against with the user

\param collide
	bool that determines if the hitboxes collide

\param boxName
	name of the hitbox that the user collide with
*/
/******************************************************************************/
void check3DCollision(threeDhitbox &user, vector<threeDhitbox> &target, bool &collide, string &boxName)
{
	Vector3 v3MidPointDiff;
	Vector3 v3UnitVec[15];

	bool bNotCollideCases[15];

	int iTestCases = 0;

	for (unsigned int i = 0; i < target.size(); ++i)
    {
		v3MidPointDiff = target[i].m_v3MidPoint - user.m_v3MidPoint;

		v3UnitVec[0] = user.m_v3UnitVecX;
		v3UnitVec[1] = user.m_v3UnitVecY;
		v3UnitVec[2] = user.m_v3UnitVecZ;
		v3UnitVec[3] = target[i].m_v3UnitVecX;
		v3UnitVec[4] = target[i].m_v3UnitVecY;
		v3UnitVec[5] = target[i].m_v3UnitVecZ;
		v3UnitVec[6] = (user.m_v3UnitVecX).Cross(target[i].m_v3UnitVecX);
		v3UnitVec[7] = (user.m_v3UnitVecX).Cross(target[i].m_v3UnitVecY);
		v3UnitVec[8] = (user.m_v3UnitVecX).Cross(target[i].m_v3UnitVecZ);
		v3UnitVec[9] = (user.m_v3UnitVecY).Cross(target[i].m_v3UnitVecX);
		v3UnitVec[10] = (user.m_v3UnitVecY).Cross(target[i].m_v3UnitVecY);
		v3UnitVec[11] = (user.m_v3UnitVecY).Cross(target[i].m_v3UnitVecZ);
		v3UnitVec[12] = (user.m_v3UnitVecZ).Cross(target[i].m_v3UnitVecX);
		v3UnitVec[13] = (user.m_v3UnitVecZ).Cross(target[i].m_v3UnitVecY);
		v3UnitVec[14] = (user.m_v3UnitVecZ).Cross(target[i].m_v3UnitVecZ);

		for (int j = 0; j < 15; ++j)
		{
			if (FAbs(v3MidPointDiff.Dot(v3UnitVec[j])) >
				FAbs((user.m_fHalfLength * user.m_v3UnitVecX).Dot(v3UnitVec[j])) +
				FAbs((user.m_fHalfHeight * user.m_v3UnitVecY).Dot(v3UnitVec[j])) +
				FAbs((user.m_fHalfDepth * user.m_v3UnitVecZ).Dot(v3UnitVec[j])) +
				FAbs((target[i].m_fHalfLength * target[i].m_v3UnitVecX).Dot(v3UnitVec[j])) +
				FAbs((target[i].m_fHalfHeight * target[i].m_v3UnitVecY).Dot(v3UnitVec[j])) +
				FAbs((target[i].m_fHalfDepth * target[i].m_v3UnitVecZ).Dot(v3UnitVec[j])))
			{
				bNotCollideCases[j] = true;
			}

			else
			{
				bNotCollideCases[j] = false;
			}
		}

		for (int j = 0; j < 15; ++j)
		{
			if (bNotCollideCases[j] == false)
			{
				++iTestCases;
			}
		}

		if (iTestCases == 15)
		{
			collide = true;
			boxName = target[i].m_sName;
			break;
		}

		else
		{
			collide = false;
			iTestCases = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief	overloaded 3D collision checking function using Separating Axis Theorem
		checking a hitbox against a vector of hitbox

\param	user
    hitbox of the user

\param target
	hitbox of the target to check against with the user

\param collide
	bool that determines if the hitboxes collide

\param boxName
	name of the hitbox that the user collide with
*/
/******************************************************************************/
void check3DCollision(threeDhitbox &user, threeDhitbox &target, bool &collide, string &boxName)
{
	Vector3 v3MidPointDiff;
	Vector3 v3UnitVec[15];

	bool bNotCollideCases[15];

	int iTestCases = 0;

	v3MidPointDiff = target.m_v3MidPoint - user.m_v3MidPoint;

	v3UnitVec[0] = user.m_v3UnitVecX;
	v3UnitVec[1] = user.m_v3UnitVecY;
	v3UnitVec[2] = user.m_v3UnitVecZ;
	v3UnitVec[3] = target.m_v3UnitVecX;
	v3UnitVec[4] = target.m_v3UnitVecY;
	v3UnitVec[5] = target.m_v3UnitVecZ;
	v3UnitVec[6] = (user.m_v3UnitVecX).Cross(target.m_v3UnitVecX);
	v3UnitVec[7] = (user.m_v3UnitVecX).Cross(target.m_v3UnitVecY);
	v3UnitVec[8] = (user.m_v3UnitVecX).Cross(target.m_v3UnitVecZ);
	v3UnitVec[9] = (user.m_v3UnitVecY).Cross(target.m_v3UnitVecX);
	v3UnitVec[10] = (user.m_v3UnitVecY).Cross(target.m_v3UnitVecY);
	v3UnitVec[11] = (user.m_v3UnitVecY).Cross(target.m_v3UnitVecZ);
	v3UnitVec[12] = (user.m_v3UnitVecZ).Cross(target.m_v3UnitVecX);
	v3UnitVec[13] = (user.m_v3UnitVecZ).Cross(target.m_v3UnitVecY);
	v3UnitVec[14] = (user.m_v3UnitVecZ).Cross(target.m_v3UnitVecZ);

	for (int j = 0; j < 15; ++j)
	{
		if (FAbs(v3MidPointDiff.Dot(v3UnitVec[j])) >
			FAbs((user.m_fHalfLength * user.m_v3UnitVecX).Dot(v3UnitVec[j])) +
			FAbs((user.m_fHalfHeight * user.m_v3UnitVecY).Dot(v3UnitVec[j])) +
			FAbs((user.m_fHalfDepth * user.m_v3UnitVecZ).Dot(v3UnitVec[j])) +
			FAbs((target.m_fHalfLength * target.m_v3UnitVecX).Dot(v3UnitVec[j])) +
			FAbs((target.m_fHalfHeight * target.m_v3UnitVecY).Dot(v3UnitVec[j])) +
			FAbs((target.m_fHalfDepth * target.m_v3UnitVecZ).Dot(v3UnitVec[j])))
		{
			bNotCollideCases[j] = true;
		}

		else
		{
			bNotCollideCases[j] = false;
		}
	}

	for (int j = 0; j < 15; ++j)
	{
		if (bNotCollideCases[j] == false)
		{
			++iTestCases;
		}
	}

	if (iTestCases == 15)
	{
		collide = true;
		boxName = target.m_sName;
	}

	else
	{
		collide = false;
	}
}