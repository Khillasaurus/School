#ifndef INCLUDED_ENGINE_CONSTRAINTS_H
#define INCLUDED_ENGINE_CONSTRAINTS_H

//====================================================================================================
// Filename:	Constraints.h
// Created by:	Peter Chan
// Description:	Header containing various particle constraints.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Particle;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Constraint
{
public:
	virtual ~Constraint() {}
	virtual void Apply() = 0;
	virtual void Render() {}
};

//----------------------------------------------------------------------------------------------------

class Fix : public Constraint
{
public:
	Fix(Particle* p);
	Fix(Particle* p, float x, float y, float z);

	// Implements Constraint
	virtual void Apply();

protected:
	Particle* mParticle;
	Math::Vector3 mLocation;
};

//----------------------------------------------------------------------------------------------------

class Spring : public Constraint
{
public:
	Spring(Particle* a, Particle* b, f32 restLength = -1.0f);

	// Implements Constraint
	virtual void Apply();
	virtual void Render();

protected:
	Particle* mParticleA;
	Particle* mParticleB;
	
	f32 mRestLength;
};

//----------------------------------------------------------------------------------------------------

class SpringMin : public Constraint
{
public:
	SpringMin(Particle* a, Particle* b, float minLength = -1.0f);

	// Implements Constraint
	virtual void Apply();
	virtual void Render();

protected:
	Particle* mParticleA;
	Particle* mParticleB;
	
	float mMinLength;
};

//----------------------------------------------------------------------------------------------------

class Plane : public Constraint
{
public:
	Plane(Particle* a, Particle* b, Particle* c, Particle* d);

	// Implements Constraint
	virtual void Apply();
	virtual void Render();

protected:
	Particle* mParticleA;
	Particle* mParticleB;
	Particle* mParticleC;
	Particle* mParticleD;
};

//----------------------------------------------------------------------------------------------------

class Hinge : public Constraint
{
public:
	Hinge(Particle* a, Particle* b, Particle* c, float minAngle, float maxAngle);

	// Implements Constraint
	virtual void Apply();
	virtual void Render();

protected:
	Particle* mParticleA;
	Particle* mParticleB;
	Particle* mParticleC;

	Spring mBA;
	Spring mBC;

	float mMinLength;
	float mMaxLength;
};

#endif // #ifndef INCLUDED_ENGINE_CONSTRAINTS_H