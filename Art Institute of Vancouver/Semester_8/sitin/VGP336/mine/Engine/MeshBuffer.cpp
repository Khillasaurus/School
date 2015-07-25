//====================================================================================================
// Filename:	MeshBuffer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MeshBuffer.h"

#include "GraphicsSystem.h"
#include "MeshUtil.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

MeshBuffer::MeshBuffer()
	: mpVertexBuffer(nullptr)
	, mpIndexBuffer(nullptr)
	, mVertexFormat(0)
	, mVertexSize(0)
	, mVertexCount(0)
	, mIndexCount(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------
MeshBuffer::~MeshBuffer()
{
	ASSERT(mpVertexBuffer == nullptr, "[MeshBuffer] Vertex buffer not released!");
	ASSERT(mpIndexBuffer == nullptr, "[MeshBuffer] Index buffer not released!");
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::Initialize(GraphicsSystem& gs, u32 vertexFormat, const void* vertexData, u32 numVertices, bool dynamic)
{
	mVertexFormat = vertexFormat;
	mVertexCount = numVertices;
	
	mVertexSize = MeshUtil::ComputeVertexSize(vertexFormat);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bd.ByteWidth = mVertexSize * mVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexData;

	gs.GetDevice()->CreateBuffer(&bd, &initData, &mpVertexBuffer);
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::Initialize(GraphicsSystem& gs, u32 vertexFormat, const void* vertexData, u32 numVertices, const u16* indexData, u32 numIndices, bool dynamic)
{
	Initialize(gs, vertexFormat, vertexData, numVertices, dynamic);
	
	mIndexCount = numIndices;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = 2 * mIndexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexData;

	gs.GetDevice()->CreateBuffer(&bd, &initData, &mpIndexBuffer);
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::Initialize(GraphicsSystem& gs, u32 vertexFormat, const Mesh& mesh, bool dynamic)
{
	Initialize(gs, vertexFormat, mesh.GetVertices(), mesh.GetVertexCount(), mesh.GetIndices(), mesh.GetIndexCount(), dynamic);
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::Terminate()
{
	SafeRelease(mpVertexBuffer);
	SafeRelease(mpIndexBuffer);
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::UpdateBuffer(GraphicsSystem& gs, const Mesh::Vertex* vertices, u32 vertexCount)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	gs.GetContext()->Map(mpVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, vertices, sizeof(Mesh::Vertex) * vertexCount);
	gs.GetContext()->Unmap(mpVertexBuffer, 0);
}

//----------------------------------------------------------------------------------------------------

void MeshBuffer::Render(GraphicsSystem& gs)
{
	// Set vertex buffer
	UINT stride = mVertexSize;
	UINT offset = 0;
	gs.GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	// Set primitive topology
	gs.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Check if we are using index buffer
	if (mpIndexBuffer != nullptr)
	{
		// Set index buffer
		gs.GetContext()->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// Draw indexed mesh
		gs.GetContext()->DrawIndexed(mIndexCount, 0, 0 );
	}
	else
	{
		// Draw mesh
		gs.GetContext()->Draw(mVertexCount, 0);
	}
}