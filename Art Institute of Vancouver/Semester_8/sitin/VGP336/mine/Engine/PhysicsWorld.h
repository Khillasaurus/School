#ifndef INCLUDED_ENGINE_PHYSICSWORLD_H
#define INCLUDED_ENGINE_PHYSICSWORLD_H

//====================================================================================================
// Filename:	PhysicsWorld.h
// Created by:	Peter Chan
// Description:	Class for a physics simulation world.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Constraint;
class Particle;

//====================================================================================================
// Class Declarations
//====================================================================================================

struct PhysicsSettings
{
	PhysicsSettings()
		: gravity(0.0f, -9.8f, 0.0f)
		, timeStep(1.0f / 60.0f)
		, drag(0.0f)
	{}

	Math::Vector3 gravity;
	f32 timeStep;
	f32 drag;
};

//----------------------------------------------------------------------------------------------------

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void Setup(const PhysicsSettings& settings);

	void StepSimulation(f32 deltaTime);

	void AddParticle(Particle* p);
	void AddConstraint(Constraint* c);
	void AddOBB(const Math::OBB& obb);
	
	void ClearDyanamic();
	void ClearAll();
	
	void Render();

	f32 GetTimeStep() const { return mSettings.timeStep; }

private:
	void AccumulateForces();
	void Integrate();
	void SatisfyConstraints();

	std::vector<Particle*> mParticles;
	std::vector<Constraint*> mConstraints;
	std::vector<Math::OBB> mOBBs;

	PhysicsSettings mSettings;

	f32 mTimer;
};

#endif // #ifndef INCLUDED_ENGINE_PHYSICSWORLD_H