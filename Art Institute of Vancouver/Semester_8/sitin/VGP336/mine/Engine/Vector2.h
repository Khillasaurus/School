#ifndef INCLUDED_ENGINE_VECTOR2_H
#define INCLUDED_ENGINE_VECTOR2_H

//====================================================================================================
// Filename:	Vector2.h
// Created by:	Peter Chan
// Description:	Struct for a 2D vector.
//====================================================================================================

//====================================================================================================
// Structs
//====================================================================================================

namespace Math
{

struct Vector2
{
	f32 x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(f32 x, f32 y) : x(x), y(y) {}
};

} // namespace Math

#endif // #ifndef INCLUDED_MATH_VECTOR2_H