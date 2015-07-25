//====================================================================================================
// Filename:	Sampler.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Sampler.h"

#include "GraphicsSystem.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	const D3D11_FILTER kFilters[] =
	{
		D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_FILTER_ANISOTROPIC
	};
	const UINT kNumFilters = ARRAYSIZE(kFilters);

	const D3D11_TEXTURE_ADDRESS_MODE kAddressModes[] =
	{
		D3D11_TEXTURE_ADDRESS_BORDER,
		D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_MIRROR,
        D3D11_TEXTURE_ADDRESS_WRAP
	};
	const UINT kNumAddressModes = ARRAYSIZE(kAddressModes);
}

//====================================================================================================
// Class Definitions
//====================================================================================================

Sampler::Sampler()
	: mpSampler(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------
Sampler::~Sampler()
{
	ASSERT(mpSampler == nullptr, "[Sampler] Sampler not released!");
}

//----------------------------------------------------------------------------------------------------

void Sampler::Initialize(GraphicsSystem& gs, Filter filter, AddressMode addressMode)
{
	ASSERT(filter >= 0 && filter < kNumFilters, "[Sampler] Invalid filter mode.");
	ASSERT(addressMode >= 0 && addressMode < kNumAddressModes, "[Sampler] Invalid address mode.");

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = kFilters[filter];
	sampDesc.AddressU = kAddressModes[addressMode];
	sampDesc.AddressV = kAddressModes[addressMode];
	sampDesc.AddressW = kAddressModes[addressMode];
	sampDesc.BorderColor[0] = 1.0f;
	sampDesc.BorderColor[1] = 1.0f;
	sampDesc.BorderColor[2] = 1.0f;
	sampDesc.BorderColor[3] = 1.0f;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = gs.GetDevice()->CreateSamplerState(&sampDesc, &mpSampler);
	ASSERT(SUCCEEDED(hr), "[TestApp] Failed to create sampler state.");
}

//----------------------------------------------------------------------------------------------------

void Sampler::Terminate()
{
	SafeRelease(mpSampler);
}

//----------------------------------------------------------------------------------------------------

void Sampler::BindVS(GraphicsSystem& gs, u32 index)
{
	gs.GetContext()->VSSetSamplers(index, 1, &mpSampler);
}

//----------------------------------------------------------------------------------------------------

void Sampler::BindGS(GraphicsSystem& gs, u32 index)
{
	gs.GetContext()->GSSetSamplers(index, 1, &mpSampler);
}

//----------------------------------------------------------------------------------------------------

void Sampler::BindPS(GraphicsSystem& gs, u32 index)
{
	gs.GetContext()->PSSetSamplers(index, 1, &mpSampler);
}