#ifndef INCLUDED_ENGINE_MATRIX_H
#define INCLUDED_ENGINE_MATRIX_H

//====================================================================================================
// Filename:	Matrix.h
// Created by:	Peter Chan
// Description:	Struct for a 4x4 matrix.
//====================================================================================================

namespace Math
{

//====================================================================================================
// Structs
//====================================================================================================

struct Matrix
{
	f32 _11, _12, _13, _14;
	f32 _21, _22, _23, _24;
	f32 _31, _32, _33, _34;
	f32 _41, _42, _43, _44;

	Matrix()
		: _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
		, _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
		, _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
		, _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
	{}

	Matrix(f32 _11, f32 _12, f32 _13, f32 _14,
		   f32 _21, f32 _22, f32 _23, f32 _24,
		   f32 _31, f32 _32, f32 _33, f32 _34,
		   f32 _41, f32 _42, f32 _43, f32 _44)
		: _11(_11), _12(_12), _13(_13), _14(_14)
		, _21(_21), _22(_22), _23(_23), _24(_24)
		, _31(_31), _32(_32), _33(_33), _34(_34)
		, _41(_41), _42(_42), _43(_43), _44(_44)
	{}
	
	static Matrix Zero();
	static Matrix Identity();
	static Matrix Translation(f32 x, f32 y, f32 z);
	static Matrix Translation(const Vector3& v);
	static Matrix RotationX(f32 rad);
	static Matrix RotationY(f32 rad);
	static Matrix RotationZ(f32 rad);
	static Matrix RotationAxis(const Vector3& axis, f32 rad);
	static Matrix RotationQuaternion(const Quaternion& q);
	static Matrix Scaling(f32 s);
	static Matrix Scaling(f32 sx, f32 sy, f32 sz);
	static Matrix Scaling(const Vector3& s);
	
	Matrix operator-() const;

	Matrix operator+(const Matrix& rhs) const;
	Matrix operator-(const Matrix& rhs) const;
	Matrix operator*(const Matrix& rhs) const;
	Matrix operator*(f32 s) const;
	Matrix operator/(f32 s) const;

	Matrix operator+=(const Matrix& rhs);
};

} // namespace Math

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "Matrix.inl"

#endif // #ifndef INCLUDED_ENGINE_MATRIX_H