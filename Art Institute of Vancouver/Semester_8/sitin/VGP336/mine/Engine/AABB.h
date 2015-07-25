#ifndef INCLUDED_ENGINE_AABB_H
#define INCLUDED_ENGINE_AABB_H

//====================================================================================================
// Filename:	AABB.h
// Created by:	Peter Chan
// Description:	Struct for a axis-aligned bounding box.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct AABB
{
	Vector3 center;
	Vector3 extend;

	AABB() : center(0.0f, 0.0f, 0.0f), extend(1.0f, 1.0f, 1.0f) {}
	AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}
};

} // namespace Math

#endif // #ifndef INCLUDED_ENGINE_AABB_H