//=================================================================================================
// Copyright (C) 2004 by Elsevier, Inc. All rights reserved.
//=================================================================================================
// Edited by Daniel Schenker
//=================================================================================================

#ifndef __CVector3__h__
#define __CVector3__h__

//=================================================================================================
//Class Declarations
//=================================================================================================

class CVector3
{
public:
	//Constructors
	inline CVector3() {}
	inline CVector3(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z)
	{
	}
	//Destructor
	inline ~CVector3() {}
	//Copy constructor
	CVector3(const CVector3& other);
	//Assignment operator
	CVector3& operator=(const CVector3& other);
	
	//Overloaded operators
	 //Comparison
	bool operator==(const CVector3& other) const;
	bool operator!=(const CVector3& other) const;
	 //Addition
	CVector3 operator+(const CVector3& other) const;
	friend CVector3& operator+=(CVector3& vector, const CVector3& other);
	 //Subtraction
	CVector3 operator-(const CVector3& other) const;
	friend CVector3& operator-=(CVector3& vector, const CVector3& other);
	CVector3 operator-() const;
	 //Scalar multiplication
	CVector3 operator*(float scalar);
	friend CVector3 operator*(float scalar, const CVector3& vector);
	CVector3& operator*=(float scalar);
	 //Scalar division
	CVector3 operator/(float scalar);
	CVector3& operator/=(float scalar);
	//Accessors
	inline float& operator[](unsigned int i) { return (&x)[i]; }
	inline float operator[](unsigned int i) const { return (&x)[i]; }

	//General Functions
	 //General
	friend float Distance(const CVector3& p0, const CVector3& p1);
	friend float DistanceSquared(const CVector3& p0, const CVector3& p1);
	float Length() const;
	float LengthSquared() const;
	void Normalize();
	float Dot(const CVector3& vector) const;
	CVector3 Cross(const CVector3& vector) const;
	 //Comparison
	bool IsZero() const;
	bool IsUnit() const;
	 //Manipulators
	inline void Set(float _x, float _y, float _z);
	void Clean();		//sets near-zero elements to 0
	inline void Zero();	//sets all elements to 0

	//Statics
	static CVector3 xAxis;
	static CVector3 yAxis;
	static CVector3 zAxis;
	static CVector3 origin;

	//Member variables
	float x;
	float y;
	float z;
};

//-------------------------------------------------------------------------------------------------
// Inlines
//-------------------------------------------------------------------------------------------------

// Set vector elements
//-------------------------------------------------------------------------------------------------
inline void CVector3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

//-------------------------------------------------------------------------------------------------

// Zero all elements
inline void CVector3::Zero()
{
	x = y = z = 0.0f;
}

#endif //__CVector3__h__
