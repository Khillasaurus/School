//====================================================================================================
// Filename:	VertexShader.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "VertexShader.h"

#include "GraphicsSystem.h"
#include "MeshUtil.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

VertexShader::VertexShader()
	: mpVertexShader(nullptr)
	, mpVertexLayout(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

VertexShader::~VertexShader()
{
	ASSERT(mpVertexShader == nullptr, "[VertexShader] Shader not released!");
	ASSERT(mpVertexLayout == nullptr, "[VertexShader] Shader not released!");
}

//----------------------------------------------------------------------------------------------------

void VertexShader::Initialize(GraphicsSystem& gs, const wchar_t* pFileName, const char* pEntryPoint, const char* pShaderModel, u32 vertexFormat)
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
	HRESULT hr = D3DCompileFromFile(pFileName, nullptr, nullptr, pEntryPoint, pShaderModel, shaderFlags, 0, &pShaderBlob, &pErrorBlob);
	if (FAILED(hr) && pErrorBlob != nullptr)
	{
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
	}
	SafeRelease(pErrorBlob);

	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	MeshUtil::CreateVertexLayout(vertexFormat, vertexLayout);

	// Create vertex buffer
	hr = gs.GetDevice()->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), nullptr, &mpVertexShader);

	// Create the input layout
	hr = gs.GetDevice()->CreateInputLayout(&vertexLayout[0], vertexLayout.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &mpVertexLayout);

	SafeRelease(pShaderBlob);
}

//----------------------------------------------------------------------------------------------------

void VertexShader::Terminate()
{
	SafeRelease(mpVertexShader);
	SafeRelease(mpVertexLayout);
}

//----------------------------------------------------------------------------------------------------

void VertexShader::Bind(GraphicsSystem& gs)
{
	gs.GetContext()->VSSetShader(mpVertexShader, nullptr, 0);
	gs.GetContext()->IASetInputLayout(mpVertexLayout);
}