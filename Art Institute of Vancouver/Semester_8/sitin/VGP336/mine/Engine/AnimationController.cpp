//====================================================================================================
// Filename:	AnimationController.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "AnimationController.h"

#include "AnimationClip.h"
#include "Bone.h"
#include "Model.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

AnimationController::AnimationController()
	: mpModel(nullptr)
	, mpCurrentAnimationClip(nullptr)
	, mCurrentTime(0.0f)
	, mCurrentFrame(0)
	, mIsPlaying(false)
	, mIsLooping(false)
{
}

//----------------------------------------------------------------------------------------------------

AnimationController::~AnimationController()
{
}

//----------------------------------------------------------------------------------------------------

void AnimationController::Initialize(Model& model)
{
	mpModel = &model;

	mToRootTransforms.resize(model.mBones.size());
	mFinalTransforms.resize(model.mBones.size());
}

//----------------------------------------------------------------------------------------------------

void AnimationController::StartClip(AnimationClip& clip, bool loop)
{
	mpCurrentAnimationClip = &clip;
	mCurrentTime = 0;
	mCurrentFrame = 0;
	mIsPlaying = true;
	mIsLooping = loop;

	mInverseRootTransform = Math::Inverse(mpModel->mRoot->transform);
	GetBindPose(mpModel->mRoot);
}

//----------------------------------------------------------------------------------------------------

void AnimationController::Update(f32 deltaTime)
{
	if (!mIsPlaying)
	{
		return;
	}

	mCurrentTime += deltaTime * mpCurrentAnimationClip->mTicksPerSecond;
	if (mCurrentTime >= mpCurrentAnimationClip->mDuration)
	{
		if (mIsLooping)
		{
			mCurrentTime = 0.0f;
		}
		else
		{
			mIsPlaying = false;
		}
	}

	if (mIsPlaying)
	{
		GetPose(mCurrentTime, mpModel->mRoot);
	}
}

//----------------------------------------------------------------------------------------------------

void AnimationController::GetBindPose(Bone* bone)
{
	Math::Matrix toParentTransform = bone->transform;
	Math::Matrix toRootTransform = toParentTransform;
	if (bone->parent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->parent->index];
	}

	mToRootTransforms[bone->index] = toRootTransform;
	mFinalTransforms[bone->index] = bone->offsetTransform * toRootTransform * mInverseRootTransform;

	for (Bone* child : bone->children)
	{
		GetBindPose(child);
	}
}

//----------------------------------------------------------------------------------------------------

void AnimationController::GetPose(f32 time, Bone* bone)
{
	Math::Matrix toParentTransform;
	mpCurrentAnimationClip->GetTransform(time, bone, toParentTransform);

	Math::Matrix toRootTransform = toParentTransform;
	if (bone->parent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->parent->index];
	}

	mToRootTransforms[bone->index] = toRootTransform;
	mFinalTransforms[bone->index] = bone->offsetTransform * toRootTransform * mInverseRootTransform;

	for (Bone* child : bone->children)
	{
		GetPose(time, child);
	}
}