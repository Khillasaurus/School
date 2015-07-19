//=============================================================================
// @ CVector3.h
// 3D vector class
// ----------------------------------------------------------------------------
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=============================================================================

#ifndef __CVector3__h__
#define __CVector3__h__

//=============================================================================
//Class Declarations
//=============================================================================

class CVector3
{
public:
	//Default Methods
	// Constructors
	inline CVector3(){}
	inline CVector3(float _x, float _y, float _z)
	:	x(_x)
	,	y(_y)
	,	z(_z)
	{
	}
	// Destructor
	inline ~CVector3(){}
	// Copy Constructors
	CVector3(const CVector3& other);
	// Copy-Assignment Operators
	CVector3& operator= (const CVector3& other);

	//Overridden Operators
	// Logic
	//  Comparison
	bool operator==(const CVector3& other) const;
	bool operator!=(const CVector3& other) const;
	// Mathematical
	//  Addition and Subtraction
			CVector3	operator+	(const CVector3& other) const;
	friend	CVector3&	operator+=	(CVector3& vector, const CVector3& other);
			CVector3	operator-	(const CVector3& other) const;
	friend	CVector3&	operator-=	(CVector3& vector, const CVector3& other);
			CVector3	operator-	() const;
	//  Scalar Multiplication and Division
			CVector3	operator*	(float scalar);
	friend	CVector3	operator*	(float scalar, const CVector3& vector);
			CVector3&	operator*=	(float scalar);
			CVector3	operator/	(float scalar);
			CVector3&	operator/=	(float scalar);

	//Calculations
	friend	float Distance(const CVector3& p0, const CVector3& p1);
	friend	float DistanceSquared(const CVector3& p0, const CVector3& p1);
			float Length() const;
			float LengthSquared() const;
			float Dot(const CVector3& v) const;
	friend	float Dot(const CVector3& v1, const CVector3& v2);
			CVector3& Cross(const CVector3& v);
			CVector3& Cross(const CVector3& v, const CVector3& w);

	//Comparison
	bool IsZero() const;
	bool IsUnit() const;

	//Accessors
	inline float& operator[](unsigned int i){return (&x)[i];}
	inline float operator[](unsigned int i) const{return (&x)[i];}

	//Manipulators
	inline void Set(float _x, float _y, float _z);
	void Clean();		// sets near-zero elements to 0
	inline void Zero();	// sets all elements to 0
	void Normalize();	// sets to unit vector

	//Member variables
	// General
	float x;
	float y;
	float z;
	// Statics
	//  Useful Defaults
	static CVector3 xAxis;
	static CVector3 yAxis;
	static CVector3 zAxis;
	static CVector3 origin;
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-----------------------------------------------------------------------------

// Set vector elements
inline void CVector3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

//-----------------------------------------------------------------------------

// Zero all elements
inline void CVector3::Zero()
{
	x = y = z = 0.0f;
}

#endif //#ifndef __CVector3__h__