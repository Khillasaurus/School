#ifndef INCLUDED_ENGINE_MODEL_H
#define INCLUDED_ENGINE_MODEL_H

//====================================================================================================
// Filename:	Model.h
// Created by:	Peter Chan
// Description:	Class for a 3D model.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Resource.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace Math
{
	struct Matrix;
};
struct Bone;
class AnimationClip;
class GraphicsSystem;
class Mesh;
class MeshBuffer;
class MeshRenderer;
class Texture;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Model : public Resource
{
public:
	Model();
	virtual ~Model();

	void Load(GraphicsSystem& gs, const char* pFilename);
	void Unload();

	void Render(MeshRenderer& renderer, const Math::Matrix& transform) const;

	NONCOPYABLE(Model);

	std::vector<Mesh*> mMeshes;

	Bone* mRoot;
	std::vector<Bone*> mBones;
	std::map<std::string, u32> mBoneIndexMap;
	std::vector<AnimationClip*> mAnimations;

	std::vector<MeshBuffer*> mMeshBuffers;
	std::vector<Texture*> mTextures;
};

#endif // #ifndef INCLUDED_ENGINE_MODEL_H