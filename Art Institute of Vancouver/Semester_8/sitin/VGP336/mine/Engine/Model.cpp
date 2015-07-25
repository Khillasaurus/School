//====================================================================================================
// Filename:	Model.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Model.h"

#include "AnimationClip.h"
#include "Bone.h"
#include "BoneAnimation.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "MeshBuilder.h"
#include "MeshRenderer.h"
#include "Texture.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Model::Model()
	: mRoot(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Model::~Model()
{
	ASSERT(mMeshes.empty(), "[Model] Mesh data not freed.");
	ASSERT(mMeshBuffers.empty(), "[Model] Mesh buffers not freed.");
}

//----------------------------------------------------------------------------------------------------

void Model::Load(GraphicsSystem& gs, const char* pFilename)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pFilename, "r");

	u32 numMeshes = 0;
	u32 numTextures = 0;
	u32 numBones = 0;
	u32 numAnimations = 0;
	fscanf_s(pFile, "%*s %u\n", &numMeshes);
	fscanf_s(pFile, "%*s %u\n", &numTextures);
	fscanf_s(pFile, "%*s %u\n", &numBones);
	fscanf_s(pFile, "%*s %u\n", &numAnimations);
	fscanf_s(pFile, "\n");
	
	for (u32 m = 0; m < numMeshes; ++m)
	{
		Mesh* mesh = new Mesh;

		u32 numVertices = 0;
		u32 numIndices = 0;
		fscanf_s(pFile, "%*s %u\n", &numVertices);
		fscanf_s(pFile, "%*s %u\n", &numIndices);

		Mesh::Vertex* vertices = new Mesh::Vertex[numVertices];
		for (u32 v = 0; v < numVertices; ++v)
		{
			f32 x, y, z, nx, ny, nz, s, t;
			fscanf_s(pFile, "%f %f %f %f %f %f %f %f\n", &x, &y, &z, &nx, &ny, &nz, &s, &t);
			vertices[v].position = Math::Vector3(x, y, z);
			vertices[v].normal = Math::Vector3(nx, ny, nz);
			vertices[v].texcoord = Math::Vector2(s, t);
		}

		u16* indices = new u16[numIndices];
		for (u32 i = 0; i < numIndices; i += 3)
		{
			u32 a, b, c;
			fscanf_s(pFile, "%u %u %u\n", &a, &b, &c);
			indices[i] = a;
			indices[i + 1] = b;
			indices[i + 2] = c;
		}
		fscanf_s(pFile, "\n");

		MeshBuilder::GenerateMesh(*mesh, vertices, numVertices, indices, numIndices);
		mMeshes.push_back(mesh);

		SafeDeleteArray(vertices);
		SafeDeleteArray(indices);
				
		u32 numVertexWeights = 0;
		fscanf_s(pFile, "%*s %u\n", &numVertexWeights);
		if(numVertexWeights > 0)
		{
			VertexWeights& vertexWeights = mesh->GetVertexWeights();
			vertexWeights.resize(numVertexWeights);

			for (u32 i = 0; i < numVertexWeights; ++i)
			{
				u32 numBoneWeights = 0;
				fscanf_s(pFile, "%u ", &numBoneWeights);
				for (u32 j = 0; j < numBoneWeights; ++j)
				{
					BoneWeight boneWeight;
					fscanf_s(pFile, "%u %f ", &boneWeight.boneIndex, &boneWeight.weight);
					vertexWeights[i].push_back(boneWeight);
				}
				fscanf_s(pFile, "\n");
			}
		}

		MeshBuffer* meshBuffer = new MeshBuffer();
		meshBuffer->Initialize(gs, Mesh::GetVertexFormat(), *mesh, numVertexWeights > 0);
		mMeshBuffers.push_back(meshBuffer);
	}

	std::string path = pFilename;
	u32 slashIndex = path.find_last_of('/');
	path = path.erase(slashIndex + 1);

	for (u32 t = 0; t < numTextures; ++t)
	{
		Texture* texture = new Texture();
		char buffer[256];
		fscanf_s(pFile, "%s\n", buffer, 256);
		std::string fullpath = path;
		fullpath += buffer;

		wchar_t wbuffer[256];
		size_t numConverted = 0;
		mbstowcs_s(&numConverted, wbuffer, fullpath.c_str(), 256);
		texture->Initialize(gs, wbuffer);
		mTextures.push_back(texture);
	}
	fscanf_s(pFile, "\n");

	if (numBones > 0)
	{
		for (u32 b = 0; b < numBones; ++b)
		{
			Bone* bone = new Bone();

			char buffer[256];
			fscanf_s(pFile, "%*s %s\n", buffer, 256);
			bone->name = buffer;

			fscanf_s(pFile, "%*s %d\n", &bone->parentIndex);

			u32 numChildren = 0;
			fscanf_s(pFile, "%*s %u\n", &numChildren);
			if (numChildren > 0)
			{
				bone->childrenIndex.resize(numChildren);
				for (u32 c = 0; c < numChildren; ++c)
				{
					fscanf_s(pFile, "%u ", &bone->childrenIndex[c]);
				}
				fscanf_s(pFile, "\n");
			}
			Math::Matrix& m = bone->transform;
			fscanf_s(pFile, "%*s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
				&m._11, &m._12, &m._13, &m._14,
				&m._21, &m._22, &m._23, &m._24,
				&m._31, &m._32, &m._33, &m._34,
				&m._41, &m._42, &m._43, &m._44);
			Math::Matrix& o = bone->offsetTransform;
			fscanf_s(pFile, "%*s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
				&o._11, &o._12, &o._13, &o._14,
				&o._21, &o._22, &o._23, &o._24,
				&o._31, &o._32, &o._33, &o._34,
				&o._41, &o._42, &o._43, &o._44);
			fscanf_s(pFile, "Index: %u\n", &bone->index);

			bone->transform = Math::Transpose(bone->transform);
			bone->offsetTransform = Math::Transpose(bone->offsetTransform);
			mBones.push_back(bone);

			fscanf_s(pFile, "\n");
		}

		for (u32 b = 0; b < numBones; ++b)
		{
			Bone* bone = mBones[b];
			if (bone->parentIndex != -1)
			{
				bone->parent = mBones[bone->parentIndex];
			}
			else
			{
				mRoot = bone;
			}

			if (!bone->childrenIndex.empty())
			{
				bone->children.resize(bone->childrenIndex.size());
				for (u32 i = 0; i < bone->childrenIndex.size(); ++i)
				{
					bone->children[i] = mBones[bone->childrenIndex[i]];
				}
			}
		}
	}

	if (numAnimations > 0)
	{
		for (u32 a = 0; a < numAnimations; ++a)
		{
			AnimationClip* animClip = new AnimationClip();

			char buffer[256];
			fscanf_s(pFile, "%*s %s\n", buffer, 256);
			animClip->mName = buffer;

			fscanf_s(pFile, "%*s %f\n", &animClip->mDuration);
			fscanf_s(pFile, "%*s %f\n", &animClip->mTicksPerSecond);

			animClip->mBoneAnimations.resize(numBones, nullptr);

			u32 numBoneAnims = 0;
			fscanf_s(pFile, "%*s %u\n", &numBoneAnims);
			if (numBoneAnims > 0)
			{
				for (u32 b = 0; b < numBoneAnims; ++b)
				{
					BoneAnimation* boneAnim = new BoneAnimation();
					fscanf_s(pFile, "%*s %u\n", &boneAnim->mBoneIndex);

					u32 numKeyframes = 0;
					fscanf_s(pFile, "%*s %u\n", &numKeyframes);
					if (numKeyframes > 0)
					{
						for (u32 k = 0; k < numKeyframes; ++k)
						{
							Keyframe* keyframe = new Keyframe();
							fscanf_s(pFile, "%*s %f %f %f %f %f %f %f %f %f %f %f\n",
								&keyframe->mTranslation.x,
								&keyframe->mTranslation.y,
								&keyframe->mTranslation.z,
								&keyframe->mRotation.x,
								&keyframe->mRotation.y,
								&keyframe->mRotation.z,
								&keyframe->mRotation.w,
								&keyframe->mScale.x,
								&keyframe->mScale.y,
								&keyframe->mScale.z,
								&keyframe->mTime);

							boneAnim->mKeyframes.push_back(keyframe);
						}
					}

					animClip->mBoneAnimations[boneAnim->mBoneIndex] = boneAnim;
				}
			}

			mAnimations.push_back(animClip);

			fscanf_s(pFile, "\n");
		}
	}

	fclose(pFile);
}

//----------------------------------------------------------------------------------------------------

void Model::Unload()
{
	for (u32 i = 0; i < (u32)mMeshes.size(); ++i)
	{
		mMeshes[i]->Destroy();
		SafeDelete(mMeshes[i]);
	}
	mMeshes.clear();

	for (u32 i = 0; i < (u32)mBones.size(); ++i)
	{
		SafeDelete(mBones[i]);
	}
	mBones.clear();

	for (u32 i = 0; i < (u32)mAnimations.size(); ++i)
	{
		SafeDelete(mAnimations[i]);
	}
	mAnimations.clear();

	for (u32 i = 0; i < (u32)mMeshBuffers.size(); ++i)
	{
		mMeshBuffers[i]->Terminate();
		SafeDelete(mMeshBuffers[i]);
	}
	mMeshBuffers.clear();

	for (u32 i = 0; i < (u32)mTextures.size(); ++i)
	{
		mTextures[i]->Terminate();
		SafeDelete(mTextures[i]);
	}
	mTextures.clear();
}

//----------------------------------------------------------------------------------------------------

void Model::Render(MeshRenderer& renderer, const Math::Matrix& transform) const
{
	for (u32 i = 0; i < (u32)mMeshBuffers.size(); ++i)
	{
		renderer.SetTexture(*mTextures[i]);
		renderer.Render(*mMeshBuffers[i], transform);
	}
}