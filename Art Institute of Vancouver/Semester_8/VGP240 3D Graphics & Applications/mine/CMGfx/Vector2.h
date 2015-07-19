//=============================================================================
// @ CVector2.h
// 2D vector class
// ----------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=============================================================================


#ifndef __CVector2__h__
#define __CVector2__h__

//=============================================================================
//Class Declarations
//=============================================================================

class CVector2
{
public:
	//Constructors
	inline CVector2(){}
	inline CVector2(float _x, float _y)
	:	x(_x)
	,	y(_y)
	{
	}
	//Destructor
	inline ~CVector2(){}

	// accessors
	inline float& operator[](unsigned int i){return (&x)[i];}
	inline float operator[](unsigned int i) const{return (&x)[i];}

	float Length() const;
	float LengthSquared() const;

	// comparison
	bool operator==(const CVector2& other) const;
	bool operator!=(const CVector2& other) const;
	bool IsZero() const;

	// manipulators
	inline void Set(float _x, float _y);
	void Clean();							// sets near-zero elements to 0
	inline void Zero();						// sets all elements to 0
	void Normalize();						// sets to unit vector

	// operators
	CVector2 operator-() const;

	// addition/subtraction
	CVector2 operator+(const CVector2& other) const;
	CVector2& operator+=(const CVector2& other);
	CVector2 operator-(const CVector2& other) const;
	CVector2& operator-=(const CVector2& other);

	// scalar multiplication
	CVector2 operator*(float scalar);
	friend CVector2 operator*(float scalar, const CVector2& vector);
	CVector2& operator*=(float scalar);
	CVector2 operator/(float scalar);
	CVector2& operator/=(float scalar);

	// dot product
	float Dot(const CVector2& vector) const;
	friend float Dot(const CVector2& vector1, const CVector2& vector2);

	// perpendicular and cross product equivalent
	CVector2 Perpendicular() const { return CVector2(-y, x); }
	float PerpDot(const CVector2& vector) const;
	friend float PerpDot(const CVector2& vector1, const CVector2& vector2);

	// useful defaults
	static CVector2 xAxis;
	static CVector2 yAxis;
	static CVector2 origin;
	static CVector2 xy;

	// member variables
	float x;
	float y;
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector2::Set()
//-------------------------------------------------------------------------------
// Set vector elements
//-------------------------------------------------------------------------------
inline void 
CVector2::Set( float _x, float _y )
{
    x = _x; y = _y;
}   // End of CVector2::Set()

//-------------------------------------------------------------------------------
// @ CVector2::Zero()
//-------------------------------------------------------------------------------
// Zero all elements
//-------------------------------------------------------------------------------
inline void 
CVector2::Zero()
{
    x = y = 0.0f;
}   // End of CVector2::Zero()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif //#ifndef __CVector2__h__