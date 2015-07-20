//=============================================================================
// @ CVector2.h
// 2D vector class
//-----------------------------------------------------------------------------
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
	//Default Methods
	// Constructors
	inline CVector2(){}
	inline CVector2(float _x, float _y)
	:	x(_x)
	,	y(_y)
	{
	}
	// Destructor
	inline ~CVector2(){}

	//Overridden Operators
	// Logic
	//  Comparison
	bool operator== (const CVector2& other) const;
	bool operator!= (const CVector2& other) const;
	// Mathematical
	//  Addition and Subtraction
			CVector2	operator+	(const CVector2& other) const;
			CVector2&	operator+=	(const CVector2& other);
			CVector2	operator-	(const CVector2& other) const;
			CVector2&	operator-=	(const CVector2& other);
			CVector2	operator-	() const;
	//  Scalar Multiplication and Division
			CVector2	operator*	(float scalar);
	friend	CVector2	operator*	(float scalar, const CVector2& vector);
			CVector2&	operator*=	(float scalar);
			CVector2	operator/	(float scalar);
			CVector2&	operator/=	(float scalar);

	//Calculations
			float		Length() const;
			float		LengthSquared() const;
			float		Dot(const CVector2& other) const;
	friend	float		Dot(const CVector2& v, const CVector2& w);
			CVector2	Perpendicular() const { return CVector2(-y, x); }
			float		PerpDot(const CVector2& other) const;
	friend	float		PerpDot(const CVector2& vector1, const CVector2& vector2);

	//Comparison
	bool IsZero() const;

	//Accessors
	inline float& operator[](unsigned int i){return (&x)[i];}
	inline float operator[](unsigned int i) const{return (&x)[i];}

	//Manipulators
	inline void Set(float _x, float _y);
	void Clean();							// sets near-zero elements to 0
	inline void Zero();						// sets all elements to 0
	void Normalize();						// sets to unit vector

	//Member Variables
	// General
	float x;
	float y;
	// Statics
	//  Useful defaults
	static CVector2 xAxis;
	static CVector2 yAxis;
	static CVector2 origin;
	static CVector2 xy;
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