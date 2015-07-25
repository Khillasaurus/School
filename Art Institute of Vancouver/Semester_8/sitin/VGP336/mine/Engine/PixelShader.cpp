//====================================================================================================
// Filename:	PixelShader.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "PixelShader.h"

#include "GraphicsSystem.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

PixelShader::PixelShader()
	: mpPixelShader(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

PixelShader::~PixelShader()
{
	ASSERT(mpPixelShader == nullptr, "[PixelShader] Shader not released!");
}

//----------------------------------------------------------------------------------------------------

void PixelShader::Initialize(GraphicsSystem& gs, const wchar_t* pFileName, const char* pEntryPoint, const char* pPixelShaderModel)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif
	
	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(pFileName, nullptr, nullptr, pEntryPoint, pPixelShaderModel, shaderFlags, 0, &pShaderBlob, &pErrorBlob);
	if (FAILED(hr) && pErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
	}
	SafeRelease(pErrorBlob);

	// Create pixel buffer
	hr = gs.GetDevice()->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &mpPixelShader);
	SafeRelease(pShaderBlob);
}

//----------------------------------------------------------------------------------------------------

void PixelShader::Terminate()
{
	SafeRelease(mpPixelShader);
}

//----------------------------------------------------------------------------------------------------

void PixelShader::Bind(GraphicsSystem& gs)
{
	gs.GetContext()->PSSetShader(mpPixelShader, nullptr, 0);
}