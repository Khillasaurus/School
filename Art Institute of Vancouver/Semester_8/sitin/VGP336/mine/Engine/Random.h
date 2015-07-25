#ifndef INCLUDED_ENGINE_RANDOM_H
#define INCLUDED_ENGINE_RANDOM_H

//====================================================================================================
// Filename:	Random.h
// Created by:	Peter Chan
// Description:	Helper functions for generating random numbers.
//====================================================================================================

//====================================================================================================
// Function Declarations
//====================================================================================================

namespace Random
{
	void SetSeed(u32 seed);

	f32 GetF();
	f32 GetF(f32 min, f32 max);
}

#endif // #ifndef INCLUDED_ENGINE_RANDOM_H