//========================================================================================================================================================================
// Filename:	Vector2.cpp
// Created by:	Daniel Schenker
//========================================================================================================================================================================

//========================================================================================================================================================================
// Includes
//========================================================================================================================================================================

#include "Vector2.h"
#include "math.h"

//========================================================================================================================================================================

float Magnitude(const Vector2& v)
{
	return ( sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)) );
}

//========================================================================================================================================================================

Vector2 Normalize(const Vector2& a)
{
	Vector2 aVector;
	aVector.x = a.x / Magnitude( a );
	aVector.y = a.y / Magnitude( a );
	aVector.z = a.z / Magnitude( a );

	return aVector;
	//return Vector2();
}

//========================================================================================================================================================================


Vector2 Invert(const Vector2& a)
{
	Vector2 aVector;
	aVector.x = a.x / Magnitude( a );
	aVector.y = a.y / Magnitude( a );
	aVector.z = a.z / Magnitude( a );

	return aVector;
	//return Vector2();
}

//========================================================================================================================================================================

//Vector2 Perpendicular(const Vector2& v)
float Perpendicular(const Vector2& a, const Vector2& b)
{
	float perp;

	perp = ( (a.y * b.z) + (b.y * a.z) + (a.x * b.z) + (b.x * a.z) + (a.x * b.y) + (b.x * a.y) );

	return perp;
}

//========================================================================================================================================================================


Vector2 Add(const Vector2& a, const Vector2& b)
{
	Vector2 aVector;
	aVector.x = a.x + b.x;
	aVector.y = a.y + b.y;
	aVector.z = a.z + b.z;

	return aVector;
	//return Vector2();
}

//========================================================================================================================================================================

Vector2 Sub(const Vector2& a, const Vector2& b)
{
	Vector2 aVector;
	aVector.x = a.x - b.x;
	aVector.y = a.y - b.y;
	aVector.z = a.z - b.z;

	return aVector;
	//return Vector2();
}

//========================================================================================================================================================================

Vector2 Scale(const Vector2& a, float scale)
{
	Vector2 aVector;
	aVector.x = a.x * scale;
	aVector.y = a.y * scale;
	aVector.z = a.z * scale;

	return aVector;
	//return Vector2();
}

//========================================================================================================================================================================

Vector2 Rotate(const Vector2& v, float rad)
{
	float cs = 0;
	float sn = 0;
	Vector2 aVector;

	cs = cos(rad);
	sn = sin(rad);
	aVector.x = (v.x * cs) - (v.y * sn);
	aVector.y = (v.x * sn) + (v.y * cs);
	aVector.z = 0;

	return aVector;
}

//========================================================================================================================================================================


float Dot(const Vector2& a, const Vector2& b)
{
	float dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;

	return dot;
}

//angle = acos( ((a.x * b.x)+(a.y * b.y)+(a.z * b.z))/(Magnitude(a) * Magnitude(b)) );