#ifndef INCLUDED_ENGINE_KEYFRAME_H
#define INCLUDED_ENGINE_KEYFRAME_H

//====================================================================================================
// Filename:	Keyframe.h
// Created by:	Peter Chan
// Description:	Class for an animation keyframe.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Keyframe
{
public:
	Keyframe();

	Math::Matrix GetTransform() const;

	Math::Vector3 mTranslation;
	Math::Quaternion mRotation;
	Math::Vector3 mScale;
	f32 mTime;
};

#endif // #ifndef INCLUDED_ENGINE_KEYFRAME_H