#ifndef INCLUDED_ENGINE_VECTOR3_H
#define INCLUDED_ENGINE_VECTOR3_H

//====================================================================================================
// Filename:	Vector3.h
// Created by:	Peter Chan
// Description:	Struct for a 3D vector.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct Vector3
{
	f32 x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
	
	static Vector3 Zero();
	static Vector3 XAxis();
	static Vector3 YAxis();
	static Vector3 ZAxis();
	
	Vector3 operator-() const;
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(f32 s) const;
	Vector3 operator/(f32 s) const;

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(f32 s);
	Vector3& operator/=(f32 s);
};

} // namespace Math

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "Vector3.inl"

#endif // #ifndef INCLUDED_MATH_VECTOR3_H