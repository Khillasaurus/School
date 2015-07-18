//=============================================================================
// @ CVector2.cpp
// 2D vector class
// ----------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=============================================================================

//=============================================================================
//Dependencies
//=============================================================================

#include "StdAfx.h"
#include "Vector2.h"
#include "MiniMath.h"

//=============================================================================
//Statics
//=============================================================================

CVector2 CVector2::xAxis(1.0f, 0.0f);
CVector2 CVector2::yAxis(0.0f, 1.0f);
CVector2 CVector2::origin(0.0f, 0.0f);
CVector2 CVector2::xy(1.0f, 1.0f);

//=============================================================================
//Class Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------------------

float CVector2::Length() const
{
	return IvSqrt(x*x + y*y);
}

//-----------------------------------------------------------------------------

float CVector2::LengthSquared() const
{
	return (x*x + y*y);
}

//-----------------------------------------------------------------------------

// Comparison operator
bool CVector2::operator==(const CVector2& other) const
{
	if(::IvAreEqual(other.x, x) && ::IvAreEqual(other.y, y))
	{
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------

// Comparison operator
bool CVector2::operator!=(const CVector2& other) const
{
	if(::IvAreEqual(other.x, x) && ::IvAreEqual(other.y, y))
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

// Check for zero vector
bool CVector2::IsZero() const
{
	return ::IsZero(x*x + y*y);
}

//-----------------------------------------------------------------------------

// Set elements close to zero equal to zero
void CVector2::Clean()
{
	if(::IsZero(x))
	{
		x = 0.0f;
	}
	if(::IsZero(y))
	{
		y = 0.0f;
	}
}

//-----------------------------------------------------------------------------

// Set to unit vector
void CVector2::Normalize()
{
	float lengthsq = x*x + y*y;

	if(::IsZero(lengthsq))
	{
		Zero();
	}
	else
	{
		float factor = IvInvSqrt(lengthsq);
		x *= factor;
		y *= factor;
	}
}

//-----------------------------------------------------------------------------

// Add vector to self and return
CVector2 CVector2::operator+(const CVector2& other) const
{
	return CVector2(x + other.x, y + other.y);
}

//-----------------------------------------------------------------------------

// Add vector to self, store in self
CVector2& operator+=(CVector2& self, const CVector2& other)
{
	self.x += other.x;
	self.y += other.y;

	return self;
}

//-----------------------------------------------------------------------------

// Subtract vector from self and return
CVector2 CVector2::operator-(const CVector2& other) const
{
	return CVector2(x - other.x, y - other.y);
}

//-----------------------------------------------------------------------------

// Subtract vector from self, store in self
CVector2& operator-=(CVector2& self, const CVector2& other)
{
	self.x -= other.x;
	self.y -= other.y;

	return self;
}

//-----------------------------------------------------------------------------

// Negate self and return
CVector2 CVector2::operator-() const
{
	return CVector2(-x, -y);
}

//-----------------------------------------------------------------------------

// Scalar multiplication
CVector2 CVector2::operator*(float scalar)
{
	return CVector2(scalar * x, scalar * y);
}


//-----------------------------------------------------------------------------

// Scalar multiplication
CVector2 operator*(float scalar, const CVector2& vector)
{
	return CVector2(scalar * vector.x, scalar * vector.y);
}


//-----------------------------------------------------------------------------

// Scalar multiplication by self
CVector2& CVector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

//-----------------------------------------------------------------------------

// Scalar division
CVector2 CVector2::operator/(float scalar)
{
	return CVector2(x / scalar, y / scalar);
}

//-----------------------------------------------------------------------------

// Scalar division by self
CVector2& CVector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

//-----------------------------------------------------------------------------

// Dot product by self
float CVector2::Dot(const CVector2& vector) const
{
	return (x * vector.x + y * vector.y);
}


//-----------------------------------------------------------------------------

// Dot product friend operator
float Dot(const CVector2& vector1, const CVector2& vector2)
{
	return (vector1.x*vector2.x + vector1.y*vector2.y);
}

//-----------------------------------------------------------------------------

// Perpendicular dot product by self
float CVector2::PerpDot(const CVector2& vector) const
{
	return (x*vector.y - y*vector.x);
}

//-----------------------------------------------------------------------------

// Dot product friend operator
float PerpDot(const CVector2& vector1, const CVector2& vector2)
{
	return (vector1.x*vector2.y - vector1.y*vector2.x);
}