#ifndef INCLUDED_ENGINE_BONEANIMATION_H
#define INCLUDED_ENGINE_BONEANIMATION_H

//====================================================================================================
// Filename:	BoneAnimation.h
// Created by:	Peter Chan
// Description:	Class for holding animation keyframes for a bone.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Keyframe.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

struct Bone;

//====================================================================================================
// Class Declarations
//====================================================================================================

class BoneAnimation
{
public:
	BoneAnimation();
	~BoneAnimation();

	void GetTransform(f32 time, Math::Matrix& transform) const;
	u32 FindKeyframeIndex(f32 time) const;

	std::vector<Keyframe*> mKeyframes;
	Bone* mBone;
	u32 mBoneIndex;
};

#endif // #ifndef INCLUDED_ENGINE_BONEANIMATION_H