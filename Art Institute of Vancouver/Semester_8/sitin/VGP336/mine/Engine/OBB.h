#ifndef INCLUDED_ENGINE_OBB_H
#define INCLUDED_ENGINE_OBB_H

//====================================================================================================
// Filename:	OBB.h
// Created by:	Peter Chan
// Description:	Struct for an oriented bounding box.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct OBB
{
	Vector3 center;
	Vector3 extend;
	Quaternion rot;

	OBB()
		: center(0.0f, 0.0f, 0.0f)
		, extend(1.0f, 1.0f, 1.0f)
		, rot(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(f32 x, f32 y, f32 z, f32 sx, f32 sy, f32 sz)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, rot(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(f32 x, f32 y, f32 z, f32 sx, f32 sy, f32 sz, f32 ax, f32 ay, f32 az, f32 angle)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, rot(Quaternion::RotationAxis(Math::Vector3(ax, ay, az), angle))
	{}
};

} // namespace Math

#endif // #ifndef INCLUDED_ENGINE_OBB_H