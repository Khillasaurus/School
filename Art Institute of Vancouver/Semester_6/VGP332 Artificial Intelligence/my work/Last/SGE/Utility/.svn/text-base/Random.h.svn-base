#ifndef INCLUDED_RANDOM_H
#define INCLUDED_RANDOM_H

//====================================================================================================
// Filename:	Random.h
// Created by:	Peter Chan
// Description:	Header containing some useful random functions. A call to Random::SetRandSeed() can be
//			  called during program initialization to set the random seed. If no seed is passed,
//			  time will be used as the random seed.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <stdlib.h>
#include <time.h>
#include <d3dx9.h>

//====================================================================================================
// Namespace
//====================================================================================================

namespace Random
{

//====================================================================================================
// Function Declarations
//====================================================================================================

// Function to set random seed
inline void SetRandSeed(int iSeed = -1);

// Function to return a random int
inline int GetInt(int iLower, int iUpper);

// Function to return a random float
inline float GetFloat(float fLower, float fUpper);

// Functions to return a random vector
inline D3DXVECTOR2 GetVector2(const D3DXVECTOR2& v0, const D3DXVECTOR2& v1);
inline D3DXVECTOR3 GetVector3(const D3DXVECTOR3& v0, const D3DXVECTOR3& v1);

// Function to return a random color
inline D3DXCOLOR GetColor(const D3DXCOLOR& c0, const D3DXCOLOR& c1);

//====================================================================================================
// Function Definitions
//====================================================================================================

inline void SetRandSeed(int iSeed)
{
	// Check if a seed is provided
	if (-1 == iSeed)
	{
		// Set random seed with time
		srand((unsigned int)time(0));
	}
	else
	{
		// Use the random seed provided
		srand(iSeed);
	}
}

//----------------------------------------------------------------------------------------------------

inline int GetInt(int iLower, int iUpper)
{
	// Create a random float from 0.0f to 1.0f
	float fRandFloat = rand() / static_cast<float>(RAND_MAX);

	// Return a number between iLower and iUpper
	return iLower + static_cast<int>((iUpper - iLower) * fRandFloat);
}

//----------------------------------------------------------------------------------------------------

inline float GetFloat(float fLower, float fUpper)
{
	// Create a random float from 0.0f to 1.0f
	float fRandFloat = rand() / static_cast<float>(RAND_MAX);

	// Return a number between fLower and fUpper
	return fLower + ((fUpper - fLower) * fRandFloat);
}

//----------------------------------------------------------------------------------------------------

inline D3DXVECTOR2 GetVector2(const D3DXVECTOR2& v0, const D3DXVECTOR2& v1)
{
	D3DXVECTOR2 returnMe;

	// Create a random vector
	returnMe.x = GetFloat(v0.x, v1.x);
	returnMe.y = GetFloat(v0.y, v1.y);

	// Return new vector
	return returnMe;
}

//----------------------------------------------------------------------------------------------------

inline D3DXVECTOR3 GetVector3(const D3DXVECTOR3& v0, const D3DXVECTOR3& v1)
{
	D3DXVECTOR3 returnMe;

	// Create a random vector
	returnMe.x = GetFloat(v0.x, v1.x);
	returnMe.y = GetFloat(v0.y, v1.y);
	returnMe.z = GetFloat(v0.z, v1.z);

	// Return new vector
	return returnMe;
}

//----------------------------------------------------------------------------------------------------

inline D3DXCOLOR GetColor(const D3DXCOLOR& c0, const D3DXCOLOR& c1)
{
	D3DXCOLOR returnMe;

	// Create a random color
	returnMe.r = GetFloat(c0.r, c1.r);
	returnMe.g = GetFloat(c0.g, c1.g);
	returnMe.b = GetFloat(c0.b, c1.b);
	returnMe.a = GetFloat(c0.a, c1.a);

	// Return new color
	return returnMe;
}

} // namespace Random

#endif // #ifndef INCLUDED_RANDOM_H