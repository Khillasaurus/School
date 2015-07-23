//=============================================================================
// @ MiniMath.h
// Base math macros and functions
//-----------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=============================================================================

#ifndef __MiniMath__h__
#define __MiniMath__h__

//=============================================================================
//Dependencies
//=============================================================================

#include <math.h>
#include "Plane2.h"
//QUESTION: What is Plane4.h? This include was already commented out with the first version of CMGfx that I received.
//#include "Plane4.h"

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

#define kEpsilon    1.0e-6f

#define kPI         3.1415926535897932384626433832795f
#define kHalfPI     1.5707963267948966192313216916398f
#define kTwoPI      2.0f*kPI

#define DEG2RAD(x) ((x)*kPI/180.0f)

#ifdef PLATFORM_OSX
#define sqrtf sqrt
#define sinf sin
#define cosf cos
#define fabsf fabs
#define tanf tan
#define atan2f atan2
#define acosf acos
#endif

inline float IvSqrt(float val)		{ return sqrtf(val); }
inline float IvInvSqrt(float val)	{ return 1.0f/sqrtf(val); }
inline float IvAbs(float f)			{ return fabsf(f); }

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Functions ------------------------------------------------------------------
//-------------------------------------------------------------------------------
//QUESTION: What is IvFastSinCos? This function was already commented out with the first version of CMGfx that I received.
// extern void IvFastSinCos( float a, float& sina, float& cosa );

//-----------------------------------------------------------------------------
//-- Inlines ------------------------------------------------------------------
//-----------------------------------------------------------------------------

//Is this floating point value close to zero?
inline bool IsZero(float a)
{
	return (fabsf(a) < kEpsilon);
}

//-----------------------------------------------------------------------------

//Are these floating point values close to equal?
inline bool IvAreEqual( float a, float b ) 
{
	return (::IsZero(a-b));
}

//-----------------------------------------------------------------------------

//Returns the floating-point sine of the argument
inline float IvSin(float a)
{
	return sinf(a);
}

//-----------------------------------------------------------------------------

//Returns the floating-point cosine of the argument
inline float IvCos(float a)
{
	return cosf(a);
}

//-----------------------------------------------------------------------------

//Returns the floating-point tangent of the argument
inline float IvTan(float a)
{
	return tanf(a);

}

//-----------------------------------------------------------------------------

//Returns the floating-point sine and cosine of the argument
inline void IvSinCos(float a, float& sina, float& cosa)
{
	sina = sinf(a);
	cosa = cosf(a);
}

//-----------------------------------------------------------------------------

//Returns the ua, ub intersection parameters given two lines
inline bool IntersectionTwoLines(
									const float x1, const float y1, const float x2, const float y2,
									const float x3, const float y3, const float x4, const float y4,
									float &ua, float &ub
								)
{
	float denom = (y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1);
	if (::IsZero(denom))
	{
		return false;
	}

	ua = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / denom;
	ub = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / denom;

	return true;
}

//-----------------------------------------------------------------------------

//Returns the u intersection parameter given a line and a plane
inline bool IntersectionLinePlane(const CVector2 &p1, const CVector2 &p2, const CPlane2 &plane, float &u)
{
	float denom = Dot(plane.normal, (p2 - p1));
	if(::IsZero( denom))
	{
		return false;
	}

	u = Dot(plane.normal, (plane.point - p1)) / denom;

	return true;
}

//-----------------------------------------------------------------------------
//-- Externs ------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif //#ifndef __MiniMath__h__