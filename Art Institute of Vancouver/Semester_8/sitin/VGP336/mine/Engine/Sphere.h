#ifndef INCLUDED_ENGINE_SPHERE_H
#define INCLUDED_ENGINE_SPHERE_H

//====================================================================================================
// Filename:	Sphere.h
// Created by:	Peter Chan
// Description:	Struct for a sphere.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct Sphere
{
	Vector3 center;
	f32 radius;

	Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f) {}
	Sphere(f32 x, f32 y, f32 z, f32 radius) : center(x, y, z), radius(radius) {}
	Sphere(const Vector3& center, f32 radius) : center(center), radius(radius) {}
};

} // namespace Math

#endif // #ifndef INCLUDED_ENGINE_SPHERE_H