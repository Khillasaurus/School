#ifndef INCLUDED_ENGINE_BONE_H
#define INCLUDED_ENGINE_BONE_H

//====================================================================================================
// Filename:	Bone.h
// Created by:	Peter Chan
// Description:	Struct for a skeleton bone.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Structs
//====================================================================================================

struct Bone
{
	Bone()
		: parent(nullptr)
		, parentIndex(-1)
		, index(0)
	{}

	std::string name;

	Bone* parent;
	std::vector<Bone*> children;

	s32 parentIndex;
	std::vector<u32> childrenIndex;

	Math::Matrix transform;
	Math::Matrix offsetTransform;

	u32 index;
};

#endif // #ifndef INCLUDED_ENGINE_BONE_H