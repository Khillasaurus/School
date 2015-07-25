//====================================================================================================
// Filename:	PhysicsWorld.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "PhysicsWorld.h"

#include "Color.h"
#include "Constraints.h"
#include "Particle.h"
#include "SimpleDraw.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	void DrawOBB(const Math::OBB& obb)
	{
		Math::Matrix matTrans = Math::Matrix::Translation(obb.center);
		Math::Matrix matRot = Math::Matrix::RotationQuaternion(obb.rot);
		Math::Matrix toWorld = matRot * matTrans;

		Math::Vector3 points[] =
		{
			Math::Vector3(-obb.extend.x, -obb.extend.y, -obb.extend.z),
			Math::Vector3(-obb.extend.x,  obb.extend.y, -obb.extend.z),
			Math::Vector3( obb.extend.x,  obb.extend.y, -obb.extend.z),
			Math::Vector3( obb.extend.x, -obb.extend.y, -obb.extend.z),
			Math::Vector3(-obb.extend.x, -obb.extend.y,  obb.extend.z),
			Math::Vector3(-obb.extend.x,  obb.extend.y,  obb.extend.z),
			Math::Vector3( obb.extend.x,  obb.extend.y,  obb.extend.z),
			Math::Vector3( obb.extend.x, -obb.extend.y,  obb.extend.z)
		};

		for (u32 i = 0; i < 8; ++i)
		{
			points[i] = Math::TransformCoord(points[i], toWorld);
		}
		
		SimpleDraw::AddLine(points[0], points[1], Color::Blue());
		SimpleDraw::AddLine(points[1], points[2], Color::Blue());
		SimpleDraw::AddLine(points[2], points[3], Color::Blue());
		SimpleDraw::AddLine(points[3], points[0], Color::Blue());
		
		SimpleDraw::AddLine(points[0], points[4], Color::Blue());
		SimpleDraw::AddLine(points[1], points[5], Color::Blue());
		SimpleDraw::AddLine(points[2], points[6], Color::Blue());
		SimpleDraw::AddLine(points[3], points[7], Color::Blue());
		
		SimpleDraw::AddLine(points[4], points[5], Color::Blue());
		SimpleDraw::AddLine(points[5], points[6], Color::Blue());
		SimpleDraw::AddLine(points[6], points[7], Color::Blue());
		SimpleDraw::AddLine(points[7], points[4], Color::Blue());
	}
}


//====================================================================================================
// Class Definitions
//====================================================================================================

PhysicsWorld::PhysicsWorld()
	: mTimer(0.0f)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

PhysicsWorld::~PhysicsWorld()
{
	ClearAll();
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::Setup(const PhysicsSettings& settings)
{
	mSettings = settings;
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::StepSimulation(f32 deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= mSettings.timeStep)
	{
		mTimer -= mSettings.timeStep;
		AccumulateForces();
		Integrate();
		SatisfyConstraints();
	}
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::AddConstraint(Constraint* c)
{
	mConstraints.push_back(c);
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::AddOBB(const Math::OBB& obb)
{
	mOBBs.push_back(obb);
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::ClearDyanamic()
{
	const u32 kNumParticles = mParticles.size();
	for (u32 i = 0; i < kNumParticles; ++i)
	{
		SafeDelete(mParticles[i]);
	}
	mParticles.clear();

	const u32 kNumConstraints = mConstraints.size();
	for (u32 i = 0; i < kNumConstraints; ++i)
	{
		SafeDelete(mConstraints[i]);
	}
	mConstraints.clear();
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::ClearAll()
{
	ClearDyanamic();
	mOBBs.clear();
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::Render()
{
	const u32 kNumParticles = mParticles.size();
	for (u32 i = 0; i < kNumParticles; ++i)
	{
		mParticles[i]->Render();
	}

	const u32 kNumConstraints = mConstraints.size();
	for (u32 i = 0; i < kNumConstraints; ++i)
	{
		mConstraints[i]->Render();
	}

	const u32 kNumOBBs = mOBBs.size();
	for (u32 i = 0; i < kNumOBBs; ++i)
	{
		DrawOBB(mOBBs[i]);
	}
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::AccumulateForces()
{
	const u32 kNumParticles = mParticles.size();
	for (u32 i = 0; i < kNumParticles; ++i)
	{
		Particle* p = mParticles[i];
		p->accel = mSettings.gravity;
	}
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::Integrate()
{
	const f32 kGamma = 1.0f - mSettings.drag;
	const f32 kTimeStepSqr = Math::Sqr(mSettings.timeStep);
	const u32 kNumParticles = mParticles.size();
	for (u32 i = 0; i < kNumParticles; ++i)
	{
		Particle* p = mParticles[i];
		Math::Vector3 temp(p->pos);
		p->pos = p->pos + ((p->pos - p->posOld) * kGamma) + (p->accel * kTimeStepSqr);
		p->posOld = temp;
	}
}

//----------------------------------------------------------------------------------------------------

void PhysicsWorld::SatisfyConstraints()
{
	const u32 kNumParticles = mParticles.size();
	const u32 kNumConstraints = mConstraints.size();
	const u32 kNumOBBs = mOBBs.size();

	for (u32 n = 0; n < 1; ++n)
	{
		for (u32 i = 0; i < kNumConstraints; ++i)
		{
			mConstraints[i]->Apply();
		}

		for (u32 i = 0; i < kNumParticles; ++i)
		{
			Particle* p = mParticles[i];
			for (u32 j = 0; j < kNumOBBs; ++j)
			{
				const Math::OBB& obb = mOBBs[j];
				if (Intersect(p->pos, obb))
				{
					Math::Vector3 vel(p->pos - p->posOld);
					Math::Vector3 dir = Math::Normalize(vel);

					Math::Ray ray(p->posOld, dir);
					Math::Vector3 point, normal;
					GetContactPoint(ray, obb, point, normal);

					Math::Vector3 velN = normal * Math::Dot(normal, vel);
					Math::Vector3 velT = vel - velN;

					p->pos = point + (normal * 0.005f);
					p->posOld = p->pos - (velT - velN * p->bounce);
				}
			}
		}
	}
}