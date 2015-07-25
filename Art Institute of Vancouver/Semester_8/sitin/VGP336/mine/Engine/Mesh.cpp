//====================================================================================================
// Filename:	Mesh.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Mesh.h"

#include "MeshUtil.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
}

//====================================================================================================
// Class Definitions
//====================================================================================================

const D3D11_INPUT_ELEMENT_DESC* Mesh::GetVertexLayout()
{
	return kVertexLayout;
}

//----------------------------------------------------------------------------------------------------

u32 Mesh::GetVertexLayoutSize()
{
	return ARRAYSIZE(kVertexLayout);
}

//----------------------------------------------------------------------------------------------------

u32 Mesh::GetVertexFormat()
{
	return VF_Position | VF_Color | VF_Normal | VF_Tangent | VF_TexCoord;
}

//----------------------------------------------------------------------------------------------------

Mesh::Mesh()
	: mpVertices(nullptr)
	, mpIndices(nullptr)
	, mNumVertices(0)
	, mNumIndices(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Mesh::~Mesh()
{
	ASSERT(mpVertices == nullptr, "[Mesh] Vertex data not freed.");
	ASSERT(mpIndices == nullptr, "[Mesh] Index data not freed.");
}

//----------------------------------------------------------------------------------------------------
void Mesh::Destroy()
{
	SafeDeleteArray(mpVertices);
	SafeDeleteArray(mpIndices);
	mNumVertices = 0;
	mNumIndices = 0;
}