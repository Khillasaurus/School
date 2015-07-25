//====================================================================================================
// Filename:	ConstantBuffer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "ConstantBuffer.h"

#include "GraphicsSystem.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

ConstantBuffer::ConstantBuffer()
	: mpBuffer(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

ConstantBuffer::~ConstantBuffer()
{
	ASSERT(mpBuffer == nullptr, "[ConstantBuffer] Buffer not released!");
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Initialize(GraphicsSystem& gs, u32 bufferSize, const void* initData)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof desc);
	desc.ByteWidth = bufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA subresourceData;
	D3D11_SUBRESOURCE_DATA* subresourceDataPtr = nullptr;
	if (initData != nullptr)
	{
		ZeroMemory(&subresourceData, sizeof(subresourceData));
		subresourceData.pSysMem = initData;
		subresourceDataPtr = &subresourceData;
	}

	gs.GetDevice()->CreateBuffer(&desc, subresourceDataPtr, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Terminate()
{
	SafeRelease(mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Set(GraphicsSystem& gs, const void* data)
{
	gs.GetContext()->UpdateSubresource(mpBuffer, 0, nullptr, data, 0, 0);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindVS(GraphicsSystem& gs, u32 slot)
{
	gs.GetContext()->VSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindGS(GraphicsSystem& gs, u32 slot)
{
	gs.GetContext()->GSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindPS(GraphicsSystem& gs, u32 slot)
{
	gs.GetContext()->PSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindCS(GraphicsSystem& gs, u32 slot)
{
	gs.GetContext()->CSSetConstantBuffers(slot, 1, &mpBuffer);
}