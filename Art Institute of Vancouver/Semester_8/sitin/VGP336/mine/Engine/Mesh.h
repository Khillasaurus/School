#ifndef INCLUDED_ENGINE_MESH_H
#define INCLUDED_ENGINE_MESH_H

//====================================================================================================
// Filename:	Mesh.h
// Created by:	Peter Chan
// Description:	Class for a 3D mesh.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Color.h"
#include "EngineMath.h"

//====================================================================================================
// Structs
//====================================================================================================

struct BoneWeight
{
	u32 boneIndex;
	f32 weight;
};
typedef std::vector<BoneWeight> BoneWeights;
typedef std::vector<BoneWeights> VertexWeights;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Mesh
{
public:
	struct Vertex
	{
		Vertex()
			: position(0.0f, 0.0f, 0.0f)
			, normal(0.0f, 0.0f, 0.0f)
			, tangent(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f)
			, texcoord(0.0f, 0.0f)
		{}

		Vertex(Math::Vector3 p, Math::Vector3 n, Math::Vector3 t, Color c, Math::Vector2 uv)
			: position(p)
			, normal(n)
			, tangent(t)
			, color(c)
			, texcoord(uv)
		{}

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Color color;
		Math::Vector2 texcoord;
	};
	
	static const D3D11_INPUT_ELEMENT_DESC* GetVertexLayout();
	static u32 GetVertexLayoutSize();
	static u32 GetVertexFormat();

	Mesh();
	~Mesh();

	void Destroy();
	
	const Vertex* GetVertices() const				{ return mpVertices; }
	const u16* GetIndices() const					{ return mpIndices; }
	u32 GetVertexCount() const						{ return mNumVertices; }
	u32 GetIndexCount() const						{ return mNumIndices; }

	VertexWeights& GetVertexWeights()				{ return mVertexWeights; }
	const VertexWeights& GetVertexWeights() const	{ return mVertexWeights; }

private:
	NONCOPYABLE(Mesh);

	friend class MeshBuilder;

	Vertex* mpVertices;
	u16* mpIndices;

	u32 mNumVertices;
	u32 mNumIndices;

	VertexWeights mVertexWeights;
};

#endif // #ifndef INCLUDED_ENGINE_MESH_H
