//=================================================================================================
// File:		Character.cpp
// Created By:	Daniel Schenker
// Created:		2012/10/29
// Last Edited:	2012/11/05
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

// Daniel Schenker
#include "Character.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

Character::Character(int id, const World& world)
: Agent(id)
, mWorld(world)
, mpPerceptionModule(NULL)
, mpSteeringModule(NULL)
, mpSeekBehavior(NULL)
, mpArriveBehavior(NULL)
, mpWanderBehavior(NULL)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

Character::~Character()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

void Character::Load()
{
	mSprite.Load("pikachu.png");

	mpPerceptionModule = new PerceptionModule(this);

	mpSeekBehavior = new SeekBehavior(this, 1.0f);
	mpSeekBehavior->SetActive(true);

	mpArriveBehavior = new ArriveBehavior(this, 1.0f);
	mpArriveBehavior->SetBrakeDistance(100.0f);
	//mpArriveBehavior->SetActive(true);

	mpWanderBehavior = new WanderBehavior(this, 1.0f);
	mpWanderBehavior->SetWanderRadius(50.0f);
	mpWanderBehavior->SetWanderDistance(100.0f);
	mpWanderBehavior->SetWanderJitter(5.0f);
	mpWanderBehavior->SetActive(true);

	mpSteeringModule = new SteeringModule();
	mpSteeringModule->AddBehavior(mpSeekBehavior);
	mpSteeringModule->AddBehavior(mpArriveBehavior);
	mpSteeringModule->AddBehavior(mpWanderBehavior);
}

//-------------------------------------------------------------------------------------------------

void Character::Unload()
{
	mSprite.Unload();

	if(mpPerceptionModule != NULL)
	{
		delete mpPerceptionModule;
		mpPerceptionModule = NULL;
	}

	if(mpSteeringModule != NULL)
	{
		delete mpSteeringModule;
		mpSteeringModule = NULL;
	}
}

//-------------------------------------------------------------------------------------------------

void Character::Update(float deltaTime)
{
	// Update perception
	//mpPerceptionModule->Update(deltaTime,);

	//Update locomotion
	SVector2 acceleration = mpSteeringModule->Update(deltaTime);
	mVelocity += acceleration * deltaTime;
	mVelocity.Truncate(mMaxSpeed);
	mPosition += mVelocity * deltaTime;

	// Update heading if we have valid velocity
	if(mVelocity.LengthSquared() > 0.0001f)
	{
		SetHeading(mVelocity);
	}

	// Wrapping
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	if(mPosition.x < 0.0)				mPosition.x = kScreenWidth - 1.0f;
	if(mPosition.x >= kScreenWidth)		mPosition.x = 0.0f;
	if(mPosition.y < 0.0)				mPosition.y = kScreenHeight - 1.0f;
	if(mPosition.y >= kScreenHeight)	mPosition.y = 0.0f;
}

//-------------------------------------------------------------------------------------------------

void Character::Render()
{
	const int kHalfWidth = mSprite.GetWidth() >> 1;
	const int kHalfHeight = mSprite.GetHeight() >> 1;
	SVector2 renderPos(mPosition.x - kHalfWidth, mPosition.y - kHalfHeight);
	float angle = atan2(-mHeading.x, mHeading.y) + kPI;
	mSprite.SetPosition(renderPos);
	mSprite.SetRotation(angle);
	mSprite.Render();

	// Debug
	if(mpSeekBehavior->IsActive())
		mpSeekBehavior->Render();
	if(mpArriveBehavior->IsActive())
		mpSeekBehavior->Render();
	if(mpWanderBehavior->IsActive())
		mpWanderBehavior->Render();
}

//-------------------------------------------------------------------------------------------------

void Character::ActivateSeek(bool activate)
{
	mpSeekBehavior->SetActive(activate);
}

//-------------------------------------------------------------------------------------------------

void Character::ActivateArrive(bool activate)
{
	mpArriveBehavior->SetActive(activate);
}

//-------------------------------------------------------------------------------------------------

void Character::ActivateWander(bool activate)
{
	mpWanderBehavior->SetActive(activate);
}