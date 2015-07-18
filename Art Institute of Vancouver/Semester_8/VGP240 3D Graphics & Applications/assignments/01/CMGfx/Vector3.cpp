//=============================================================================
// @ CVector3.cpp
// 3D vector class
// ----------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=============================================================================

//=============================================================================
//Dependencies
//=============================================================================

#include "StdAfx.h"
#include "Vector3.h"
#include "MiniMath.h"

//=============================================================================
//Statics
//=============================================================================

CVector3 CVector3::xAxis(1.0f, 0.0f, 0.0f);
CVector3 CVector3::yAxis(0.0f, 1.0f, 0.0f);
CVector3 CVector3::zAxis(0.0f, 0.0f, 1.0f);
CVector3 CVector3::origin(0.0f, 0.0f, 0.0f);

//=============================================================================
//Class Definitions
//=============================================================================

// Copy constructor
CVector3::CVector3(const CVector3& other)
: x(other.x)
, y(other.y)
, z(other.z)
{
}

// ----------------------------------------------------------------------------

// Assignment operator
CVector3& CVector3::operator=(const CVector3& other)
{
	//if same object
	if(this == &other)
	{
		return *this;
	}

	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

// ----------------------------------------------------------------------------

// Point distance
float Distance(const CVector3& p0, const CVector3& p1)
{
	float x = p0.x - p1.x;
	float y = p0.y - p1.y;
	float z = p0.z - p1.z;

	return ::IvSqrt(x*x + y*y + z*z);
}


// ----------------------------------------------------------------------------

// Point distance
float DistanceSquared(const CVector3& p0, const CVector3& p1)
{
	float x = p0.x - p1.x;
	float y = p0.y - p1.y;
	float z = p0.z - p1.z;

	return ((x * x) + (y * y) + (z * z));
}

// ----------------------------------------------------------------------------

// Vector length

float CVector3::Length() const
{
	return IvSqrt(LengthSquared());
}

// ----------------------------------------------------------------------------

// Vector length squared (avoids square root)

float CVector3::LengthSquared() const
{
	return (x*x + y*y + z*z);
}

// ----------------------------------------------------------------------------

// Comparison operator
bool CVector3::operator==(const CVector3& other) const
{
	if	(
			::IvAreEqual(other.x, x) &&
			::IvAreEqual(other.y, y) &&
			::IvAreEqual(other.z, z)
		)
		{
			return true;
		}

	return false;
}

// ----------------------------------------------------------------------------

// Comparison operator
bool CVector3::operator!=(const CVector3& other) const
{
	if	(
			::IvAreEqual(other.x, x) &&
			::IvAreEqual(other.y, y) &&
			::IvAreEqual(other.z, z)
		)
		{
			return false;
		}

	return true;
}

// ----------------------------------------------------------------------------

// Check for zero vector
bool CVector3::IsZero() const
{
	return ::IsZero(x*x + y*y + z*z);
}

// ----------------------------------------------------------------------------

// Check for unit vector
bool CVector3::IsUnit() const
{
	return ::IsZero(1.0f - x*x - y*y - z*z);
}

// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------

// Set to unit vector
void CVector3::Normalize()
{
	float lengthsq = x*x + y*y + z*z;

	if(::IsZero(lengthsq))
	{
		Zero();
	}
	else
	{
		//float factor = IvInvSqrt( lengthsq );
		//x *= factor;
		//y *= factor;
		//z *= factor;
		*this *= IvInvSqrt(lengthsq);
	}
}

// ----------------------------------------------------------------------------

// Add vector to self and return
CVector3 CVector3::operator+(const CVector3& other) const
{
	return CVector3(x + other.x, y + other.y, z + other.z);
}

// ----------------------------------------------------------------------------

// Add vector to self, store in self
CVector3& operator+=(CVector3& self, const CVector3& other)
{
	self.x += other.x;
	self.y += other.y;
	self.z += other.z;

	return self;
}

// ----------------------------------------------------------------------------

// Subtract vector from self and return
CVector3 CVector3::operator-(const CVector3& other) const
{
	return CVector3(x - other.x, y - other.y, z - other.z);
}

// ----------------------------------------------------------------------------

// Subtract vector from self, store in self
CVector3& operator-=(CVector3& self, const CVector3& other)
{
	self.x -= other.x;
	self.y -= other.y;
	self.z -= other.z;

	return self;
}

// ----------------------------------------------------------------------------

// Negate self and return
CVector3 CVector3::operator-() const
{
	return CVector3(-x, -y, -z);
}

// ----------------------------------------------------------------------------

// Scalar multiplication
CVector3 CVector3::operator*(float scalar)
{
	return CVector3(scalar*x, scalar*y, scalar*z);
}

// ----------------------------------------------------------------------------

// Scalar multiplication
CVector3 operator*(float scalar, const CVector3& vector)
{
	return CVector3(scalar*vector.x, scalar*vector.y, scalar*vector.z);
}

// ----------------------------------------------------------------------------

// Scalar multiplication by self
CVector3& CVector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

// ----------------------------------------------------------------------------

// Scalar division
CVector3 CVector3::operator/(float scalar)
{
	return CVector3(x / scalar, y / scalar, z / scalar);
}

// ----------------------------------------------------------------------------

// Scalar division by self
CVector3& CVector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

// ----------------------------------------------------------------------------

// Dot product by self
float CVector3::Dot(const CVector3& vector) const
{
	return ((x * vector.x) + (y * vector.y) + (z * vector.z));
}

// ----------------------------------------------------------------------------

// Dot product friend operator
float Dot(const CVector3& vector1, const CVector3& vector2)
{
	return ((vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z));
}

//-------------------------------------------------------------------------------

//Cross
CVector3& CVector3::Cross(const CVector3& v, const CVector3& w)
{
	CVector3 r;

	r.x = (v.y * w.z) - (w.y * v.z);
	r.y = (v.z * w.x) - (w.z * v.x);
	r.z = (v.x * w.y) - (w.x * v.y);

	return r;
}