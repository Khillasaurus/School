#ifndef INCLUDED_ENGINE_PARTICLE_H
#define INCLUDED_ENGINE_PARTICLE_H

//====================================================================================================
// Filename:	Particle.h
// Created by:	Peter Chan
// Description:	Class for a 3D verlet particle.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Particle
{
public:
	Particle();
	Particle(f32 x, f32 y, f32 z, f32 radius, f32 invMass);

	void Render();

	void SetPosition(f32 x, f32 y, f32 z);
	void SetVelocity(f32 x, f32 y, f32 z);

	Math::Vector3 pos;
	Math::Vector3 posOld;
	Math::Vector3 accel;

	f32 radius;
	f32 invMass;
	f32 bounce;
};

#endif // #ifndef INCLUDED_ENGINE_PARTICLE_H