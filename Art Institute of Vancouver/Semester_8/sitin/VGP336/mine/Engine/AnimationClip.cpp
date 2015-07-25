//====================================================================================================
// Filename:	AnimationClip.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "AnimationClip.h"

#include "Bone.h"
#include "BoneAnimation.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

AnimationClip::AnimationClip()
	: mDuration(0.0f)
	, mTicksPerSecond(0.0f)
	, mKeyframeCount(0)
{
}

//----------------------------------------------------------------------------------------------------

AnimationClip::~AnimationClip()
{
	for (u32 i = 0; i < (u32)mBoneAnimations.size(); ++i)
	{
		SafeDelete(mBoneAnimations[i]);
	}
	mBoneAnimations.clear();
}

//----------------------------------------------------------------------------------------------------

void AnimationClip::GetTransform(f32 time, Bone* bone, Math::Matrix& transform) const
{
	BoneAnimation* boneAnim = mBoneAnimations[bone->index];
	if (boneAnim != nullptr)
	{
		boneAnim->GetTransform(time, transform);
	}
	else
	{
		transform = Math::Matrix::Identity();
	}
}