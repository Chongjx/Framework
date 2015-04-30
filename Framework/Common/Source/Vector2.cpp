#include <cmath>
#include "Vector2.h"
/******************************************************************************/
/*!
\brief	Vector2 default constructor

\param	a
	x value
\param	b
	y value
*/
/******************************************************************************/
Vector2::Vector2( float a, float b ) : x(a), y(b)
{
}

/******************************************************************************/
/*!
\brief	Vector2 copy constructor

\param	rhs
	Vector to copy from
*/
/******************************************************************************/
Vector2::Vector2( const Vector2 &rhs ) : x(rhs.x), y(rhs.y)
{
}

/******************************************************************************/
/*!
\brief	Set the elements of this vector

\param	a
	x value
\param	b
	y value
*/
/******************************************************************************/
void Vector2::Set( float a, float b )
{
	x = a;
	y = b;
}

/******************************************************************************/
/*!
\brief
operator+ overload for vector addition

\param rhs
	Vector3 to add with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector2 Vector2::operator+( const Vector2& rhs ) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

/******************************************************************************/
/*!
\brief
operator- overload for vector subtraction

\param rhs
	Vector2 to subtract with
\return Resulting vector
*/
/******************************************************************************/
Vector2 Vector2::operator-( const Vector2& rhs ) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

/******************************************************************************/
/*!
\brief
operator- overload for unary negation

\return 
	Resulting vector
*/
/******************************************************************************/
Vector2 Vector2::operator-( void ) const
{
	return Vector2(-x, -y);
}

/******************************************************************************/
/*!
\brief
operator* overload for scalar multiplication

\param scalar - float to multiply with
 
\exception None
\return Resulting vector
*/
Vector2 Vector2::operator*( float scalar ) const
{
	return Vector2(scalar * x, scalar * y);
}

/******************************************************************************/
/*!
\brief
Return length of vector

\return 
	Length
*/
/******************************************************************************/
float Vector2::Length( void ) const
{
	return sqrt(x * x + y * y);
}

/******************************************************************************/
/*!
\brief
Dot product of 2 vectors

\param rhs
	Point to calculate dot product with
\return 
	float value of dot product
*/
/******************************************************************************/
float Vector2::Dot( const Vector2& rhs ) const
{
	return x * rhs.x + y * rhs.y;
}

/******************************************************************************/
/*!
\brief
Return a copy of this vector, normalized

\param rhs
	Point to calculate distance from
\exception Divide by zero 
	thrown if normalizing a zero vector
\return 
	Resulting normalized vector
*/
/******************************************************************************/
Vector2 Vector2::Normalized( void )
{
	float d = Length();
	return Vector2(x/d, y/d);
}

/******************************************************************************/
/*!
\brief
Scalar product of scalar with vector

\param scalar
	scalar value
\param vector
	vector
\return 
	Resulting vector
*/
/******************************************************************************/
Vector2 operator*( float scalar, const Vector2& rhs )
{
	return rhs * scalar;
}