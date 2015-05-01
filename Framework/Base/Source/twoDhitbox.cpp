/******************************************************************************/
/*!
\file	twoDhitbox.cpp
\author Jun Xiang
\brief
Hitbox creation and holds its properties. Collision checks included
*/
/******************************************************************************/
#include "twoDhitbox.h"

/******************************************************************************/
/*!
\brief
twoDhitbox default constructor
*/
/******************************************************************************/
twoDhitbox::twoDhitbox(void)
{
	m_v2MidPoint.Set(0, 0);
	
	m_fLength = m_fHeight = 1.0f;
	m_fHalfLength = m_fHalfHeight = 0.5f;

	m_v2UnitVecX.Set(0.0f, 0.0f);
	m_v2UnitVecY.Set(0.0f, 0.0f);

	m_sName = "DEFAULT_2D_HITBOX";
}

/******************************************************************************/
/*!
\brief
twoDhitbox default destructor
*/
/******************************************************************************/
twoDhitbox::~twoDhitbox(void)
{
}

/******************************************************************************/
/*!
\brief
overloaded twoDhitbox create function. Assuming the hitbox is parrallel to x and y axis.

\param midPoint
	centre point of the hitbox Vector2

\param length
	length of the hitbox float

\param height
	height of the hitbox float

\ param name
	name of the hitbox string
*/
/******************************************************************************/
void twoDhitbox::create2Dhitbox(Vector2 midPoint, float length, float height, const string name)
{
	Vector2 temp_v2BottomRight, temp_v2TopRight, temp_v2TopLeft;

	this->m_v2MidPoint = midPoint;
	this->m_fLength = length;
	this->m_fHeight = height;
	this->m_sName = name;

	this->m_fHalfLength = length * 0.5f;
	this->m_fHalfHeight = height * 0.5f;

	temp_v2BottomRight.Set(m_v2MidPoint.x + m_fHalfLength, m_v2MidPoint.y - m_fHalfHeight);
	temp_v2TopRight.Set(m_v2MidPoint.x + m_fHalfLength, m_v2MidPoint.y + m_fHalfHeight);
	temp_v2TopLeft.Set(m_v2MidPoint.x - m_fHalfLength, m_v2MidPoint.y + m_fHalfHeight);

	this->m_v2UnitVecX = (temp_v2TopRight - temp_v2TopLeft).Normalized();
	this->m_v2UnitVecY = (temp_v2TopRight - temp_v2BottomRight).Normalized();
}

/******************************************************************************/
/*!
\brief
overloaded twoDhitbox create function. Providing the corners of the hitbox to create

\param bottomRight
	bottom right corner of the hitbox Vector2

\param topRight
	top right corner of the hitbox Vector2

\param topLeft
	top left corner of the hitbox Vector2

\param bottomLeft
	bottom left corner of the hitbox Vector2

\param name
	name of the hitbox string

*/
/******************************************************************************/
void twoDhitbox::create2Dhitbox(Vector2 bottomRight, Vector2 topRight, Vector2 topLeft, Vector2 bottomLeft, const string name)
{
	this->m_sName = name;

	this->m_fLength = (topRight - topLeft).Length();
	this->m_fHeight = (topRight - bottomRight).Length();

	this->m_fHalfLength = m_fLength * 0.5f;
	this->m_fHalfHeight = m_fHeight * 0.5f;

	this->m_v2UnitVecX = (topRight - topLeft).Normalized();
	this->m_v2UnitVecY = (topRight - bottomRight).Normalized();

	this->m_v2MidPoint.Set(bottomRight.x - m_fHalfLength, bottomRight.y + m_fHalfHeight);
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	Vector2
    Mid Point of the hitbox
*/
/******************************************************************************/
Vector2 twoDhitbox::getMidPoint(void) const
{
	return this->m_v2MidPoint;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
    Length of the hitbox
*/
/******************************************************************************/
float twoDhitbox::getLength(void) const
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
float twoDhitbox::getHeight(void) const
{
	return this->m_fHeight;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	float
    Half length of the hitbox
*/
/******************************************************************************/
float twoDhitbox::getHalfLength(void) const
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
float twoDhitbox::getHalfHeight(void) const
{
	return this->m_fHalfHeight;
}

/******************************************************************************/
/*!
\brief	twoDhitbox getter functions

\return	string
    name of the hitbox
*/
/******************************************************************************/
string twoDhitbox::getName(void) const
{
	return this->m_sName;
}

/******************************************************************************/
/*!
\brief	overloaded 2D collision checking function using Separating Axis Theorem
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
void check2DCollision(twoDhitbox &user, vector<twoDhitbox> &target, bool &collide, string &boxName)
{
	Vector2 v2MidPointDiff;
	Vector2 v2UnitVec[4];

	bool bNotCollideCases[4];

	int iTestCases = 0;

	for (unsigned int i = 0; i < target.size(); ++i)
    {
		v2MidPointDiff = target[i].m_v2MidPoint - user.m_v2MidPoint;

		v2UnitVec[0] = user.m_v2UnitVecX;
		v2UnitVec[1] = user.m_v2UnitVecY;
		v2UnitVec[2] = target[i].m_v2UnitVecX;
		v2UnitVec[3] = target[i].m_v2UnitVecY;

		for (int j = 0; j < 4; ++j)
		{
			if (FAbs(v2MidPointDiff.Dot(v2UnitVec[j])) > 
				FAbs((user.m_fHalfLength * user.m_v2UnitVecX).Dot(v2UnitVec[j])) + 
				FAbs((user.m_fHalfHeight * user.m_v2UnitVecY).Dot(v2UnitVec[j])) + 
				FAbs((target[i].m_fHalfLength * target[i].m_v2UnitVecX).Dot(v2UnitVec[j])) +
				FAbs((target[i].m_fHalfHeight * target[i].m_v2UnitVecY).Dot(v2UnitVec[j])))
			{
				bNotCollideCases[j] = true;
			}

			else
			{
				bNotCollideCases[j] = false;
			}
		}

		for (int j = 0; j < 4; ++j)
		{
			if (bNotCollideCases[j] == false)
			{
				++iTestCases;
			}
		}

		if (iTestCases == 4)
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
\brief	overloaded 2D collision checking function using Separating Axis Theorem
		checking a hitbox against 1 specific hitbox only

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
void check2DCollision(twoDhitbox &user, twoDhitbox &target, bool &collide, string &boxName)
{
	Vector2 v2MidPointDiff;
	Vector2 v2UnitVec[4];

	bool bNotCollideCases[4];

	int iTestCases = 0;

	v2MidPointDiff = target.m_v2MidPoint - user.m_v2MidPoint;

	v2UnitVec[0] = user.m_v2UnitVecX;
	v2UnitVec[1] = user.m_v2UnitVecY;
	v2UnitVec[2] = target.m_v2UnitVecX;
	v2UnitVec[3] = target.m_v2UnitVecY;

	for (int j = 0; j < 4; ++j)
	{
		if (FAbs(v2MidPointDiff.Dot(v2UnitVec[j])) > 
			FAbs((user.m_fHalfLength * user.m_v2UnitVecX).Dot(v2UnitVec[j])) + 
			FAbs((user.m_fHalfHeight * user.m_v2UnitVecY).Dot(v2UnitVec[j])) + 
			FAbs((target.m_fHalfLength * target.m_v2UnitVecX).Dot(v2UnitVec[j])) +
			FAbs((target.m_fHalfHeight * target.m_v2UnitVecY).Dot(v2UnitVec[j])))
		{
			bNotCollideCases[j] = true;
		}

		else
		{
			bNotCollideCases[j] = false;
		}
	}

	for (int j = 0; j < 4; ++j)
	{
		if (bNotCollideCases[j] == false)
		{
			++iTestCases;
		}
	}

	if (iTestCases == 4)
	{
		collide = true;
		boxName = target.m_sName;
	}

	else
	{
		collide = false;
	}
}