#ifndef INCLUDED_ENGINE_ANIMATIONCONTROLLER_H
#define INCLUDED_ENGINE_ANIMATIONCONTROLLER_H

//====================================================================================================
// Filename:	AnimationController.h
// Created by:	Peter Chan
// Description:	Class for controlling animation playback.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

struct Bone;
class AnimationClip;
class Model;

//====================================================================================================
// Class Declarations
//====================================================================================================

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	void Initialize(Model& model);

	void StartClip(AnimationClip& clip, bool loop);
	void Update(f32 deltaTime);

	const std::vector<Math::Matrix>& ToRootTransforms() const	{ return mToRootTransforms; }
	const std::vector<Math::Matrix>& BoneTransforms() const		{ return mFinalTransforms; }

private:
	void GetBindPose(Bone* bone);
	void GetPose(f32 time, Bone* bone);

	AnimationClip* mpCurrentAnimationClip;

	std::vector<Math::Matrix> mToRootTransforms;
	std::vector<Math::Matrix> mFinalTransforms;
	Math::Matrix mInverseRootTransform;

	Model* mpModel;

	f32 mCurrentTime;
	u32 mCurrentFrame;

	bool mIsPlaying;
	bool mIsLooping;
};

#endif // #ifndef INCLUDED_ENGINE_ANIMATIONCONTROLLER_H