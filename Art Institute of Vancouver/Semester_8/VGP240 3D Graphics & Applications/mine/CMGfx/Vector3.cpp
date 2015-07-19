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

//-----------------------------------------------------------------------------
//Default Methods
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Copy Constructors

CVector3::CVector3(const CVector3& other)
: x(other.x)
, y(other.y)
, z(other.z)
{
}

//-----------------------------------------------------------------------------
// Copy-Assignment Operators

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

//-----------------------------------------------------------------------------
//Overridden Operators
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Logic

//-----------------------------------------------------------------------------
//  Comparison

bool CVector3::operator== (const CVector3& other) const
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

//-----------------------------------------------------------------------------

bool CVector3::operator!= (const CVector3& other) const
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

//-----------------------------------------------------------------------------
// Mathematical

//-----------------------------------------------------------------------------
//  Addition and Subtraction

//Add vector to self and return
CVector3 CVector3::operator+ (const CVector3& other) const
{
	return CVector3	(
						x + other.x,
						y + other.y,
						z + other.z
					);
}

//-----------------------------------------------------------------------------

//Add vector to self, store in self
CVector3& operator+= (CVector3& self, const CVector3& other)
{
	self.x += other.x;
	self.y += other.y;
	self.z += other.z;

	return self;
}

//-----------------------------------------------------------------------------

//Subtract vector from self and return
CVector3 CVector3::operator- (const CVector3& other) const
{
	return CVector3	(
						x - other.x,
						y - other.y,
						z - other.z
					);
}

//-----------------------------------------------------------------------------

//Subtract vector from self, store in self
CVector3& operator-= (CVector3& self, const CVector3& other)
{
	self.x -= other.x;
	self.y -= other.y;
	self.z -= other.z;

	return self;
}

//-----------------------------------------------------------------------------

//Negate self and return
CVector3 CVector3::operator- () const
{
	return CVector3	(
						-x,
						-y,
						-z
					);
}

//-----------------------------------------------------------------------------
//  Scalar Multiplication and Division

CVector3 CVector3::operator* (float scalar)
{
	return CVector3	(
						scalar * x,
						scalar * y,
						scalar * z
					);
}

//-----------------------------------------------------------------------------

CVector3 operator* (float scalar, const CVector3& vector)
{
	return CVector3	(
						scalar * vector.x,
						scalar * vector.y,
						scalar * vector.z
					);
}

//-----------------------------------------------------------------------------

CVector3& CVector3::operator*= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

//-----------------------------------------------------------------------------

CVector3 CVector3::operator/ (float scalar)
{
	return CVector3	(
						x / scalar,
						y / scalar,
						z / scalar
					);
}

//-----------------------------------------------------------------------------

CVector3& CVector3::operator/= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

//-----------------------------------------------------------------------------
//Calculations
//-----------------------------------------------------------------------------

float Distance(const CVector3& p0, const CVector3& p1)
{
	return ::IvSqrt(DistanceSquared(p0, p1));
}

//-----------------------------------------------------------------------------

float DistanceSquared(const CVector3& p0, const CVector3& p1)
{
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	float dz = p1.z - p0.z;

	return ((dx * dx) + (dy * dy) + (dz * dz));
}

//-----------------------------------------------------------------------------

//Vector length
float CVector3::Length() const
{
	return IvSqrt(LengthSquared());
}

//-----------------------------------------------------------------------------

//Vector length squared (avoids square root)
float CVector3::LengthSquared() const
{
	return ((x * x) + (y * y) + (z * z));
}

//-----------------------------------------------------------------------------

//self dot other
float CVector3::Dot(const CVector3& other) const
{
	return ((x * other.x) + (y * other.y) + (z * other.z));
}

//-----------------------------------------------------------------------------

//v dot w
float Dot(const CVector3& v, const CVector3& w)
{
	return ((v.x * w.x) + (v.y * w.y) + (v.z * w.z));
}

//-----------------------------------------------------------------------------

//self cross other
CVector3& CVector3::Cross(const CVector3& other)
{
	return CVector3	(
						(y * other.z) - (other.y * z),
						(z * other.x) - (other.z * x),
						(x * other.y) - (other.x * y)
					);
}

//-----------------------------------------------------------------------------

//v Cross w
CVector3& CVector3::Cross(const CVector3& v, const CVector3& w)
{
	return CVector3	(
						(v.y * w.z) - (w.y * v.z),
						(v.z * w.x) - (w.z * v.x),
						(v.x * w.y) - (w.x * v.y)
					);
}

//-----------------------------------------------------------------------------
//Comparison
//-----------------------------------------------------------------------------

//Check for zero vector
bool CVector3::IsZero() const
{
	return ::IsZero((x * x) + (y * y) + (z * z));
}

//-----------------------------------------------------------------------------

//Check for unit vector
bool CVector3::IsUnit() const
{
	return ::IsZero(1.0f - (x * x) - (y * y) - (z * z));
}

//-----------------------------------------------------------------------------
//Manipulators
//-----------------------------------------------------------------------------

//Set elements close to zero equal to zero
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

//-----------------------------------------------------------------------------

//Set to unit vector
void CVector3::Normalize()
{
	float lengthsq = LengthSquared();

	if(::IsZero(lengthsq))
	{
		Zero();
	}
	else
	{
		*this *= IvInvSqrt(lengthsq);
		/*
		The following is the expanded version of the above line:
		
		float factor = IvInvSqrt( lengthsq );
		x *= factor;
		y *= factor;
		z *= factor;
		*/
	}
}