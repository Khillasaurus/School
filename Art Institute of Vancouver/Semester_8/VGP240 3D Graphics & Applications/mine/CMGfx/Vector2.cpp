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
//Overridden Operators
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Logic

//-----------------------------------------------------------------------------
//  Comparison

bool CVector2::operator== (const CVector2& other) const
{
	if	(
			::IvAreEqual(other.x, x) &&
			::IvAreEqual(other.y, y)
		)
		{
			return true;
		}

	return false;
}

//-----------------------------------------------------------------------------

bool CVector2::operator!= (const CVector2& other) const
{
	if	(
			::IvAreEqual(other.x, x) &&
			::IvAreEqual(other.y, y)
		)
		{
			return false;
		}

	return true;
}

//-----------------------------------------------------------------------------
// Mathematical

//  Addition and Subtraction

//Add vector to self and return
CVector2 CVector2::operator+(const CVector2& other) const
{
	return CVector2	(
						x + other.x,
						y + other.y
					);
}

//-----------------------------------------------------------------------------

//Add vector to self, store in self
CVector2& operator+= (CVector2& self, const CVector2& other)
{
	self.x += other.x;
	self.y += other.y;

	return self;
}

//-----------------------------------------------------------------------------

//Subtract vector from self and return
CVector2 CVector2::operator- (const CVector2& other) const
{
	return CVector2	(
						x - other.x,
						y - other.y
					);
}

//-----------------------------------------------------------------------------

//Subtract vector from self, store in self
CVector2& operator-= (CVector2& self, const CVector2& other)
{
	self.x -= other.x;
	self.y -= other.y;

	return self;
}

//-----------------------------------------------------------------------------

// Negate self and return
CVector2 CVector2::operator- () const
{
	return CVector2	(	
						-x,
						-y
					);
}

//-----------------------------------------------------------------------------
//  Scalar Multiplication and Division

//Scalar multiplication
CVector2 CVector2::operator* (float scalar)
{
	return CVector2	(
						scalar * x,
						scalar * y
					);
}


//-----------------------------------------------------------------------------

CVector2 operator* (float scalar, const CVector2& vector)
{
	return CVector2	(
						scalar * vector.x,
						scalar * vector.y
					);
}


//-----------------------------------------------------------------------------

CVector2& CVector2::operator*= (float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

//-----------------------------------------------------------------------------

// Scalar division
CVector2 CVector2::operator/ (float scalar)
{
	return CVector2	(
						x / scalar,
						y / scalar
					);
}

//-----------------------------------------------------------------------------

// Scalar division by self
CVector2& CVector2::operator/= (float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

//-----------------------------------------------------------------------------
//Calculations
//-----------------------------------------------------------------------------

float CVector2::Length() const
{
	return IvSqrt(LengthSquared());
}

//-----------------------------------------------------------------------------

float CVector2::LengthSquared() const
{
	return ((x * x) + (y * y));
}

//-----------------------------------------------------------------------------

//self dot other
float CVector2::Dot(const CVector2& other) const
{
	return ((x * other.x) + (y * other.y));
}


//-----------------------------------------------------------------------------

//v dot w
float Dot(const CVector2& v, const CVector2& w)
{
	return ((v.x * w.x) + (v.y * w.y));
}

//-----------------------------------------------------------------------------

//self perpendicular dot product other
float CVector2::PerpDot(const CVector2& other) const
{
	return ((x * other.y) - (y * other.x));
}

//-----------------------------------------------------------------------------

//Dot product friend operator
float PerpDot(const CVector2& v, const CVector2& w)
{
	return ((v.x * w.y) - (v.y * w.x));
}

//-----------------------------------------------------------------------------
//Comparison
//-----------------------------------------------------------------------------

//Check for zero vector
bool CVector2::IsZero() const
{
	return ::IsZero((x * x) + (y * y));
}

//-----------------------------------------------------------------------------
//Manipulators
//-----------------------------------------------------------------------------

//Set elements close to zero equal to zero
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

//Set to unit vector
void CVector2::Normalize()
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

		float factor = IvInvSqrt(lengthsq);
		x *= factor;
		y *= factor;
		*/
	}
}