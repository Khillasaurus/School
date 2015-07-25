//====================================================================================================
// Filename:	BoneAnimation.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "BoneAnimation.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

BoneAnimation::BoneAnimation()
	: mBone(nullptr)
	, mBoneIndex(0)
{
}

//----------------------------------------------------------------------------------------------------

BoneAnimation::~BoneAnimation()
{
	for (u32 i = 0; i < (u32)mKeyframes.size(); ++i)
	{
		SafeDelete(mKeyframes[i]);
	}
	mKeyframes.clear();
}

//----------------------------------------------------------------------------------------------------

void BoneAnimation::GetTransform(f32 time, Math::Matrix& transform) const
{
	Keyframe* firstKeyframe = mKeyframes.front();
	Keyframe* lastKeyframe = mKeyframes.back();

	if (time <= firstKeyframe->mTime)
	{
		transform = firstKeyframe->GetTransform();
	}
	else if (time >= lastKeyframe->mTime)
	{
		transform = lastKeyframe->GetTransform();
	}
	else
	{
		u32 keyframeIndex = FindKeyframeIndex(time);
		Keyframe* keyframeOne = mKeyframes[keyframeIndex];
		Keyframe* keyframeTwo = mKeyframes[keyframeIndex + 1];

		Math::Vector3 translationOne = keyframeOne->mTranslation;
		Math::Quaternion rotationQuaternionOne = keyframeOne->mRotation;
		Math::Vector3 scaleOne = keyframeOne->mScale;

		Math::Vector3 translationTwo = keyframeTwo->mTranslation;
		Math::Quaternion rotationQuaternionTwo = keyframeTwo->mRotation;
		Math::Vector3 scaleTwo = keyframeTwo->mScale;

		f32 lerpValue = ((time - keyframeOne->mTime) / (keyframeTwo->mTime - keyframeOne->mTime));
		Math::Vector3 translation = Math::Lerp(translationOne, translationTwo, lerpValue);
		Math::Quaternion rotation = Math::Slerp(rotationQuaternionOne, rotationQuaternionTwo, lerpValue);
		Math::Vector3 scale = Math::Lerp(scaleOne, scaleTwo, lerpValue);

		Math::Matrix matTrans = Math::Matrix::Translation(translation);
		Math::Matrix matRot = Math::Matrix::RotationQuaternion(rotation);
		Math::Matrix matScale = Math::Matrix::Scaling(scale);
		transform = matScale * matRot * matTrans;
	}
}

//----------------------------------------------------------------------------------------------------

u32 BoneAnimation::FindKeyframeIndex(f32 time) const
{
	u32 keyframeIndex = 1;

	const u32 numKeyframes = mKeyframes.size();
	for (; keyframeIndex < numKeyframes; ++keyframeIndex)
	{
		if (time < mKeyframes[keyframeIndex]->mTime)
		{
			break;
		}
	}

	return keyframeIndex - 1;
}