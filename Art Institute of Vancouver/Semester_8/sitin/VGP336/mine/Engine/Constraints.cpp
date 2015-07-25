//====================================================================================================
// Filename:	Constraints.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Constraints.h"

#include "Color.h"
#include "Particle.h"
#include "SimpleDraw.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Fix::Fix(Particle* p)
	: mParticle(p)
	, mLocation(p->pos)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Fix::Fix(Particle* p, f32 x, f32 y, f32 z)
	: mParticle(p)
	, mLocation(x, y, z)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void Fix::Apply()
{
	mParticle->pos = mLocation;
}

//----------------------------------------------------------------------------------------------------

Spring::Spring(Particle* a, Particle* b, f32 restLength)
	: mParticleA(a)
	, mParticleB(b)
	, mRestLength(restLength)
{
	if (mRestLength <= 0.0f)
	{
		mRestLength = Math::Distance(a->pos, b->pos);
	}
}

//----------------------------------------------------------------------------------------------------

void Spring::Apply()
{
	Math::Vector3 delta = mParticleB->pos - mParticleA->pos;
	f32 dist = Math::Magnitude(delta);
	f32 diff = (dist - mRestLength) / (dist * (mParticleA->invMass + mParticleB->invMass));
	mParticleA->pos += delta * diff * mParticleA->invMass;
	mParticleB->pos -= delta * diff * mParticleB->invMass;
}

//----------------------------------------------------------------------------------------------------

void Spring::Render()
{
	SimpleDraw::AddLine(mParticleA->pos, mParticleB->pos, Color::Green());
}

//----------------------------------------------------------------------------------------------------

SpringMin::SpringMin(Particle* a, Particle* b, f32 minLength)
	: mParticleA(a)
	, mParticleB(b)
	, mMinLength(minLength)
{
	if (mMinLength <= 0.0f)
	{
		mMinLength = Math::Distance(a->pos, b->pos);
	}
}

//----------------------------------------------------------------------------------------------------

void SpringMin::Apply()
{
	Math::Vector3 delta = mParticleB->pos - mParticleA->pos;
	f32 dist = Math::Magnitude(delta);
	if (dist < mMinLength)
	{
		f32 diff = (dist - mMinLength) / (dist * (mParticleA->invMass + mParticleB->invMass));
		mParticleA->pos += delta * diff * mParticleA->invMass;
		mParticleB->pos -= delta * diff * mParticleB->invMass;
	}
}

//----------------------------------------------------------------------------------------------------

void SpringMin::Render()
{
	SimpleDraw::AddLine(mParticleA->pos, mParticleB->pos, Color::Red());
}

//----------------------------------------------------------------------------------------------------

Plane::Plane(Particle* a, Particle* b, Particle* c, Particle* d)
	: mParticleA(a)
	, mParticleB(b)
	, mParticleC(c)
	, mParticleD(d)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void Plane::Apply()
{
	// Compute the planes normal
	Math::Vector3 ab = mParticleB->pos - mParticleA->pos;
	Math::Vector3 ac = mParticleC->pos - mParticleA->pos;
	Math::Vector3 cross = Math::Cross(ab, ac);
	Math::Vector3 norm = Math::Normalize(cross);

	// Compute the plane distance by projecting a point to the norm 
	f32 d = Math::Dot(mParticleA->pos, norm);

	// Compute particleD's distance to the plane
	f32 t = Math::Dot(mParticleD->pos, norm);

	// Check if particleD is below the plane
	if (d > t)
	{
		f32 diff = (d - t) * 0.5f;
		mParticleA->pos -= norm * diff;
		mParticleB->pos -= norm * diff;
		mParticleC->pos -= norm * diff;
		mParticleD->pos += norm * diff;
	}
}

//----------------------------------------------------------------------------------------------------

void Plane::Render()
{
	SimpleDraw::AddLine(mParticleA->pos, mParticleB->pos, Color::Magenta());
	SimpleDraw::AddLine(mParticleB->pos, mParticleC->pos, Color::Magenta());
	SimpleDraw::AddLine(mParticleC->pos, mParticleA->pos, Color::Magenta());
}

//----------------------------------------------------------------------------------------------------

Hinge::Hinge(Particle* a, Particle* b, Particle* c, f32 minAngle, f32 maxAngle)
	: mParticleA(a)
	, mParticleB(b)
	, mParticleC(c)
	, mBA(b, a)
	, mBC(b, c)
	, mMinLength(-1.0f)
	, mMaxLength(-1.0f)
{
	f32 ba = Math::Distance(mParticleA->pos, mParticleB->pos);
	f32 bc = Math::Distance(mParticleC->pos, mParticleB->pos);

	if (minAngle >= 0.0f)
		mMinLength = sqrt((ba * ba) + (bc * bc) - (2.0f * ba * bc * cos(minAngle)));
	if (maxAngle >= 0.0f)
		mMaxLength = sqrt((ba * ba) + (bc * bc) - (2.0f * ba * bc * cos(maxAngle)));
}

//----------------------------------------------------------------------------------------------------

void Hinge::Apply()
{
	mBA.Apply();
	mBC.Apply();

	Math::Vector3 delta = mParticleC->pos - mParticleA->pos;
	f32 dist = Math::Magnitude(delta);
	if (dist < mMinLength && mMinLength >= 0.0f)
	{
		f32 diff = (dist - mMinLength) / (dist * (mParticleA->invMass + mParticleC->invMass));
		mParticleA->pos += delta * diff * mParticleA->invMass;
		mParticleC->pos -= delta * diff * mParticleC->invMass;
	}
	else if (dist > mMaxLength && mMaxLength >= 0.0f)
	{
		f32 diff = (dist - mMaxLength) / (dist * (mParticleA->invMass + mParticleC->invMass));
		mParticleA->pos += delta * diff * mParticleA->invMass;
		mParticleC->pos -= delta * diff * mParticleC->invMass;
	}
}

//----------------------------------------------------------------------------------------------------

void Hinge::Render()
{
	SimpleDraw::AddLine(mParticleA->pos, mParticleB->pos, Color::Cyan());
	SimpleDraw::AddLine(mParticleB->pos, mParticleC->pos, Color::Cyan());
}