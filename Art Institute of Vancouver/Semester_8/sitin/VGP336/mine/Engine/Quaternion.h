#ifndef INCLUDED_ENGINE_QUATERNION_H
#define INCLUDED_ENGINE_QUATERNION_H

//====================================================================================================
// Filename:	Quaternion.h
// Created by:	Peter chan
// Description:	Struct for a quaternion.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct Quaternion
{
	f32 x, y, z, w;

	Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Quaternion(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

	static Quaternion RotationAxis(const Vector3& axis, f32 rad);

	Quaternion operator+(const Quaternion& rhs) const;
	Quaternion operator*(f32 s) const;
};

} // namespace Math

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "Quaternion.inl"

#endif // #ifndef INCLUDED_ENGINE_QUATERNION_H