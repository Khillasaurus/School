//=================================================================================================
// Filename:	WinMain.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/09
// Last Edited:	2012/10/16
// Description:	Hello Shooter demo
//====================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include <SGE.h>
using namespace SGE;

#include "Bullet.h"
#include "Enemy.h"
#include "Fighter.h"

//=================================================================================================
// Globals
//=================================================================================================

//Background
SGE_Sprite gBackground;

//Fighter
Fighter gFighter;
SGE_Sound gBulletSoundFire;

// Bullets
const int kMaxBullets = 100;
Bullet gBullets[kMaxBullets];
int gBulletIndex = 0;
float gFireDelay = 0.0f;

// Enemies
const int kMaxEnemies = 100;
Enemy gEnemies[kMaxEnemies];
int gEnemiesIndex = 0;

// Explosions
const int kMaxExplosions = 20;
SGE_Emitter gExplosions[kMaxExplosions];
int gExplosionIndex = 0;
SGE_Sound gExplosionSound;

bool gQuit = false;

//=================================================================================================
// Helper Functions
//=================================================================================================

void UpdateGameObjects(float deltaTime)
{
	//Fighter
	gFighter.Update(deltaTime);

	// Bullets
	for(int i = 0; i < kMaxBullets; ++i)
	{
		gBullets[i].Update(deltaTime);
	}

	// Enemies
	for(int i = 0; i < kMaxEnemies; ++i)
	{
		gEnemies[i].Update(deltaTime);
	}

	// Enemies
	for(int i = 0; i < kMaxExplosions; ++i)
	{
		gExplosions[i].Update(deltaTime);
	}
}

//-------------------------------------------------------------------------------------------------

void FireBullets(float deltaTime)
{
	// Update fire timer
	if(gFireDelay > 0.0f)
	{
		gFireDelay -= deltaTime;
	}

	if(Input_IsKeyDown(Keys::SPACE) && gFireDelay <= 0.0f)
	{
		const int index0 = gBulletIndex;
		const int index1 = (gBulletIndex + 1) % kMaxBullets;
		const int index2 = (gBulletIndex + 2) % kMaxBullets;
		if( !gBullets[index0].IsActive() &&
			!gBullets[index1].IsActive() &&
			!gBullets[index2].IsActive() )
		{
			SVector2 cacheFighterPos = gFighter.GetPosition();
			SVector2 pos0(cacheFighterPos);
			SVector2 pos1(cacheFighterPos);
			SVector2 pos2(cacheFighterPos);
			SVector2 vel0(20.0f, -750.0f);
			SVector2 vel1(0.0f, -750.0f);
			SVector2 vel2(-20.0f, -750.0f);
			//pos1.x += 20.0f;
			//pos2.x += -20.0f;
			gBullets[index0].Fire(pos0, vel0);
			gBullets[index1].Fire(pos1, vel1);
			gBullets[index2].Fire(pos2, vel2);
			gBulletIndex = (index2 + 1) % kMaxBullets;
			gFireDelay = 0.1f;
			gBulletSoundFire.Play(false);
		}
	}
}

//-------------------------------------------------------------------------------------------------

void SpawnEnemies(float deltaTime)
{
	if(RandomFloat(0.0f, 1.0f) < 0.05f)
	{
		if(!gEnemies[gEnemiesIndex].IsActive())
		{
			const int kWinWidth = IniFile_GetInt("WinWidth", 768);
			SVector2 pos(RandomFloat(100.0f, kWinWidth - 100.0f), -100.0f);
			gEnemies[gEnemiesIndex].Spawn(pos);
			gEnemiesIndex = (gEnemiesIndex + 1) % kMaxEnemies;
		}
	}
}

//-------------------------------------------------------------------------------------------------

void CheckCollision()
{
	// Go through each enemy
	for(int e = 0; e < kMaxEnemies; ++e)
	{
		// Check if this enemy is active
		if(gEnemies[e].IsActive())
		{
			// Go through each bullet
			for(int b = 0; b < kMaxBullets; ++b)
			{
				// Check if this bullet is active
				if(!gBullets[b].IsActive())
				{
					continue;
				}
				SCircle enemyCircle = gEnemies[e].GetBoundingCircle();
				SCircle bulletCircle = gBullets[b].GetBoundingCircle();
				if(Intersect(enemyCircle, bulletCircle))
				{
					// Remove both
					gEnemies[e].Kill();
					gBullets[b].Kill();

					// Start a new explosion
					gExplosions[gExplosionIndex].SetPosition(enemyCircle.center);
					gExplosions[gExplosionIndex].Start(100.0f, true);
					gExplosionIndex = (gExplosionIndex + 1) % kMaxExplosions;
					gExplosionSound.Play(false);

					break;
				}
				//float d = DistanceSquared(enemyCircle.center, bulletCircle.center);
				//float r = enemyCircle.radius + bulletCircle.radius;
			}
		}
	}
}

//=================================================================================================
// SGE Functions
//=================================================================================================

void SGE_Initialize()
{
	// Cache Window Settings
	const int kWinWidth = IniFile_GetInt("WinWidth", 1024);
	const int kWinHeight = IniFile_GetInt("WinHeight", 768);

	//Background
	gBackground.Load("space.jpg");

	// Fighter
	gFighter.Load();
	gFighter.SetPosition(SVector2(kWinWidth * 0.5f, kWinHeight * 0.5f));
	gFighter.SetSpeed(500.0f);

	// Bullets
	gBulletSoundFire.Load("photongun1.wav");
	for(int i = 0; i < kMaxBullets; ++i)
	{
		gBullets[i].Load();
	}

	// Enemies
	for(int i = 0; i < kMaxEnemies; ++i)
	{
		gEnemies[i].Load();
	}

	// Explosions
	gBulletSoundFire.Load("explosion.wav");
	for(int i = 0; i < kMaxExplosions; ++i)
	{
		gExplosions[i].Load("explosion.txt");
	}
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	//Background
	gBackground.Unload();

	//Fighter
	gFighter.Unload();

	// Bullets
	gBulletSoundFire.Unload();
	for(int i = 0; i < kMaxBullets; ++i)
	{
		gBullets[i].Unload();
	}

	// Enemies
	for(int i = 0; i < kMaxEnemies; ++i)
	{
		gEnemies[i].Unload();
	}

	// Explosions
	gExplosionSound.Unload();
	for(int i = 0; i < kMaxExplosions; ++i)
	{
		gExplosions[i].Unload();
	}
}

//-------------------------------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	UpdateGameObjects(deltaTime);
	FireBullets(deltaTime);
	SpawnEnemies(deltaTime);
	CheckCollision();

	//Quit the application
	if(Input_IsKeyPressed(Keys::ESCAPE))
	{
		gQuit = true;
	}

	return gQuit;
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	//Background
	gBackground.Render();

	// Enemies
	for(int i = 0; i < kMaxEnemies; ++i)
	{
		gEnemies[i].Render();
	}

	// Bullets
	for(int i = 0; i < kMaxBullets; ++i)
	{
		gBullets[i].Render();
	}

	//Fighter
	gFighter.Render();

	// Explosions
	for(int i = 0; i < kMaxExplosions; ++i)
	{
		gExplosions[i].Render(true);
	}
}

//-------------------------------------------------------------------------------------------------