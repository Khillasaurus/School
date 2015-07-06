//====================================================================================================
// Filename:	CSound.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CSound.h"

#include "Audio/CFMOD.h"
#include "Core/CLog.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CSound::CSound(void) :
	mpSound(NULL),
	mpChannel(NULL),
	mVolume(1.0f),
	mLoaded(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CSound::~CSound(void)
{
	// Release everything
	Unload();
}

//----------------------------------------------------------------------------------------------------

void CSound::Load(const char* pFilename)
{
	// Clear everything before we load the sound
	Unload();

	// Set mode
	FMOD_MODE mode = FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE;

	// Load the sound using FMOD system
	if (FMOD_OK != FMOD_System_CreateSound(CFMOD::Get()->FMODSystem(), pFilename, mode, 0, &mpSound))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Sound] Failed to load sound %s", pFilename);
		return;
	}

	// Set flag
	mLoaded = true;
}

//----------------------------------------------------------------------------------------------------

void CSound::Unload(void)
{
	// Stop playing first
	Stop();

	// Release everything
	if (0 != mpSound)
	{
		FMOD_Sound_Release(mpSound);
		mpSound = 0;
	}

	// Reset flag
	mLoaded = false;
}

//----------------------------------------------------------------------------------------------------

void CSound::Play(bool bLoop)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Stop any previous sound first
	Stop();

	// Check if we are already playing
	FMOD_System_PlaySound(CFMOD::Get()->FMODSystem(), FMOD_CHANNEL_FREE, mpSound, true, &mpChannel);
	FMOD_Channel_SetLoopCount(mpChannel, bLoop ? -1 : 0);
	FMOD_Channel_SetVolume(mpChannel, mVolume);
	FMOD_Channel_SetPaused(mpChannel, false);
}

//----------------------------------------------------------------------------------------------------

void CSound::Stop(void)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Check if we have a valid channel
	if (0 != mpChannel)
	{
		// Stop the channel that is playing the sound
		FMOD_Channel_Stop(mpChannel);
		mpChannel = 0;
	}
}

//----------------------------------------------------------------------------------------------------

void CSound::Pause(void)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Check if we have a valid channel
	if (0 != mpChannel)
	{
		// Pause the channel that is playing the sound
		FMOD_Channel_SetPaused(mpChannel, 1);		
	}
}

//----------------------------------------------------------------------------------------------------

void CSound::Resume(void)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Check if we have a valid channel
	if (0 != mpChannel)
	{
		// Resume the channel that is playing the sound
		FMOD_Channel_SetPaused(mpChannel, 0);		
	}
}

//----------------------------------------------------------------------------------------------------

bool CSound::IsPlaying(void) const
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return false;
	}

	// Check if we have a valid channel
	FMOD_BOOL bPlaying = 0;
	if (0 != mpChannel)
	{
		FMOD_Channel_IsPlaying(mpChannel, &bPlaying);
	}

	return (bPlaying != 0);
}

//----------------------------------------------------------------------------------------------------

bool CSound::IsPaused(void) const
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return false;
	}

	// Check if we have a valid channel
	FMOD_BOOL bPaused = 0;
	if (0 != mpChannel)
	{
		FMOD_Channel_GetPaused(mpChannel, &bPaused);
	}

	return (bPaused != 0);
}

//----------------------------------------------------------------------------------------------------

float CSound::GetVolume(void) const
{
	return mVolume;
}

//----------------------------------------------------------------------------------------------------

void CSound::SetVolume(float fVolume)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Cache the volume
	mVolume = fVolume;

	if (mVolume> 1.0f) mVolume = 1.0f;
	else if (mVolume <0.0f) mVolume = 0.0f;

	// Check if we have a valid channel
	if (0 != mpChannel)
	{
		FMOD_Channel_SetVolume(mpChannel, mVolume);
	}
}

//----------------------------------------------------------------------------------------------------

void CSound::AddToVolume(float fVolume)
{
	// Check if we have a sound loaded
	if (!mLoaded)
	{
		return;
	}

	// Cache the volume
	mVolume += fVolume;

	if (mVolume> 1.0f) mVolume = 1.0f;
	else if (mVolume <0.0f) mVolume = 0.0f;

	// Check if we have a valid channel
	if (0 != mpChannel)
	{
		FMOD_Channel_SetVolume(mpChannel, mVolume);
	}
}