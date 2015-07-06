//=================================================================================================
// 3D vector class
//-------------------------------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=================================================================================================
// Edited by Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Precompiled Headers
#include "stdafx.h"

//CMGfx
#include "Vector3.h"
#include "MiniMath.h"

//=================================================================================================
// Statics
//=================================================================================================

CVector3 CVector3::xAxis( 1.0f, 0.0f, 0.0f );
CVector3 CVector3::yAxis( 0.0f, 1.0f, 0.0f );
CVector3 CVector3::zAxis( 0.0f, 0.0f, 1.0f );
CVector3 CVector3::origin( 0.0f, 0.0f, 0.0f );

//=================================================================================================
//Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------------------------
CVector3::CVector3(const CVector3& other)
: x( other.x )
, y( other.y )
, z( other.z )
{
}

//-------------------------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------------------------
CVector3& CVector3::operator=(const CVector3& other)
{
	// if same object
	if(this == &other)
	{
		return *this;
	}

	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

//=================================================================================================
//Overloaded operators
//=================================================================================================

bool CVector3::operator==(const CVector3& other) const
{
	if( ::IvAreEqual(other.x, x) &&
		::IvAreEqual(other.y, y) &&
		::IvAreEqual(other.z, z) )
	{
		return true;
	}
	
	return false;
}

//-------------------------------------------------------------------------------------------------

bool CVector3::operator!=(const CVector3& other) const
{
	if( ::IvAreEqual(other.x, x) &&
		::IvAreEqual(other.y, y) &&
		::IvAreEqual(other.z, z) )
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------

// Add vector to self and return
CVector3 CVector3::operator+(const CVector3& other) const
{
	return CVector3(x + other.x, y + other.y, z + other.z);
}

//-------------------------------------------------------------------------------------------------

// Add vector to self, store in self
CVector3& operator+=(CVector3& self, const CVector3& other)
{
	self.x += other.x;
	self.y += other.y;
	self.z += other.z;

	return self;
}

//-------------------------------------------------------------------------------------------------

// Subtract vector from self and return
CVector3 CVector3::operator-(const CVector3& other) const
{
	return CVector3(x - other.x, y - other.y, z - other.z);
}

//-------------------------------------------------------------------------------------------------

// Subtract vector from self, store in self
CVector3& operator-=(CVector3& self, const CVector3& other)
{
	self.x -= other.x;
	self.y -= other.y;
	self.z -= other.z;

	return self;
}

//-------------------------------------------------------------------------------------------------

// Negate self and return
CVector3 CVector3::operator-() const
{
	return CVector3(-x, -y, -z);
}

//-------------------------------------------------------------------------------------------------

// Scalar multiplication
CVector3 CVector3::operator*(float scalar)
{
	return CVector3(scalar*x, scalar*y, scalar*z);

}

//-------------------------------------------------------------------------------------------------

// Scalar multiplication
CVector3 operator*(float scalar, const CVector3& vector)
{
	return CVector3(scalar*vector.x, scalar*vector.y, scalar*vector.z);
}

//-------------------------------------------------------------------------------------------------

// Scalar multiplication by self
CVector3& CVector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	
	return *this;
}

//-------------------------------------------------------------------------------------------------

// Scalar division
CVector3 CVector3::operator/(float scalar)
{
	return CVector3(x/scalar, y/scalar, z/scalar);
}

//-------------------------------------------------------------------------------------------------

// Scalar division by self
CVector3& CVector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

//-------------------------------------------------------------------------------------------------
//General Functions
//-------------------------------------------------------------------------------------------------

// Point distance
float Distance(const CVector3& p0, const CVector3& p1)
{
	float x = p0.x - p1.x;
	float y = p0.y - p1.y;
	float z = p0.z - p1.z;

	return ::IvSqrt(x*x + y*y + z*z);
}

//-------------------------------------------------------------------------------------------------

// Point distance
float DistanceSquared(const CVector3& p0, const CVector3& p1)
{
	float x = p0.x - p1.x;
	float y = p0.y - p1.y;
	float z = p0.z - p1.z;

	return (x*x + y*y + z*z);
}

//-------------------------------------------------------------------------------------------------

float CVector3::Length() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

//-------------------------------------------------------------------------------------------------

float CVector3::LengthSquared() const
{
	return ((x * x) + (y * y) + (z * z));
}

//-------------------------------------------------------------------------------------------------

void CVector3::Normalize()
{
	float lengthsq = LengthSquared();

	//if the length is 0
	if(::IsZero(lengthsq))
	{
		//sets all elements to 0
		Zero();
	}
	else
	{
		//1 over the length squared
		float factor = (1.0f / sqrtf(lengthsq));

		//Normalize
		x *= factor;
		y *= factor;
		z *= factor;
	}
}

//-------------------------------------------------------------------------------------------------

float CVector3::Dot(const CVector3& vector) const
{
	return ((x * vector.x) + (y * vector.y) + (z * vector.z));
}

//-------------------------------------------------------------------------------------------------

CVector3 CVector3::Cross(const CVector3& vector) const
{
	return CVector3((y * vector.z)-(vector.y * z), -(x * vector.z)-(vector.x * z), (x * vector.y)-(vector.x * y));
}

//-------------------------------------------------------------------------------------------------

// Check for zero vector
bool CVector3::IsZero() const
{
	return ::IsZero(x*x + y*y + z*z);
}

//-------------------------------------------------------------------------------------------------

// Check for unit vector
bool CVector3::IsUnit() const
{
	return ::IsZero(1.0f - x*x - y*y - z*z);
}

//-------------------------------------------------------------------------------------------------

// Set elements close to zero equal to zero
void CVector3::Clean()
{
	if(::IsZero(x))
	{
		x = 0.0f;
	}
	if(::IsZero(y))
	{
		y = 0.0f;
	}
	if(::IsZero(z))
	{
		z = 0.0f;
	}
}