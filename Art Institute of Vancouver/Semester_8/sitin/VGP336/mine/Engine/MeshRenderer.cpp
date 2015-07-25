//====================================================================================================
// Filename:	MeshRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MeshRenderer.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "Mesh.h"
#include "MeshBuffer.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

MeshRenderer::MeshRenderer()
	: mpGraphicsSystem(nullptr)
	, mpCamera(nullptr)
	, mpTexture(nullptr)
	, mInitialized(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

MeshRenderer::~MeshRenderer()
{
	ASSERT(!mInitialized, "[MeshRenderer] Not terminated!");
}

//----------------------------------------------------------------------------------------------------

void MeshRenderer::Initialize(GraphicsSystem& gs)
{
	ASSERT(!mInitialized, "[MeshRenderer] Already initialized!");

	mpGraphicsSystem = &gs;

	mCBuffer.Initialize(gs);

	mVertexShader.Initialize(gs, L"../Engine/Shaders/Default.fx", "VS", "vs_4_0", Mesh::GetVertexFormat());
	mPixelShader.Initialize(gs, L"../Engine/Shaders/Default.fx", "PS", "ps_4_0");

	mDefaultTexture.Initialize(gs, L"../Engine/Images/checker.dds");
	mSampler.Initialize(gs, Sampler::Anisotropic, Sampler::Wrap);

	mInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void MeshRenderer::Terminate()
{
	ASSERT(mInitialized, "[MeshRenderer] Already terminated!");

	mpGraphicsSystem = nullptr;
	mpCamera = nullptr;
	mpTexture = nullptr;

	mCBuffer.Terminate();

	mVertexShader.Terminate();
	mPixelShader.Terminate();

	mDefaultTexture.Terminate();
	mSampler.Terminate();

	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void MeshRenderer::SetCamera(Camera& camera)
{
	mpCamera = &camera;
}

//----------------------------------------------------------------------------------------------------

void MeshRenderer::SetTexture(Texture& texture)
{
	mpTexture = &texture;
}

//----------------------------------------------------------------------------------------------------

void MeshRenderer::Render(MeshBuffer& meshBuffer, const Math::Matrix& transform)
{
	ASSERT(mpCamera != nullptr , "[MeshRenderer] No camera set!");

	XMFLOAT3 camPos = *(XMFLOAT3*)&mpCamera->GetPosition();
	
	XMMATRIX matWorld = *(XMMATRIX*)&transform;
	XMMATRIX matView = *(XMMATRIX*)&mpCamera->GetViewMatrix();
	XMMATRIX matProj = *(XMMATRIX*)&mpCamera->GetProjectionMatrix();

	CBuffer cb;
	cb.matWorld = XMMatrixTranspose(matWorld);
	cb.matWVP = XMMatrixTranspose(matWorld * matView * matProj);
	cb.viewPosition = XMVectorSet(camPos.x, camPos.y, camPos.z, 1.0f);
	cb.lightDirection = XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f);
	cb.ambientMaterial = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	cb.diffuseMaterial = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	cb.specularMaterial = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	cb.ambientLight = XMVectorSet(0.5f, 0.5f, 0.5f, 1.0f);
	cb.diffuseLight = XMVectorSet(0.7f, 0.7f, 0.7f, 1.0f);
	cb.specularLight = XMVectorSet(0.7f, 0.7f, 0.7f, 1.0f);
	cb.specularPower = 10.0f;
	mCBuffer.Set(*mpGraphicsSystem, cb);
	mCBuffer.BindVS(*mpGraphicsSystem, 0);
	mCBuffer.BindPS(*mpGraphicsSystem, 0);

	if (mpTexture != nullptr)
	{
		mpTexture->BindPS(*mpGraphicsSystem, 0);
	}
	else
	{
		mDefaultTexture.BindPS(*mpGraphicsSystem, 0);
	}

	mSampler.BindPS(*mpGraphicsSystem, 0);

	mVertexShader.Bind(*mpGraphicsSystem);
	mPixelShader.Bind(*mpGraphicsSystem);

	meshBuffer.Render(*mpGraphicsSystem);
}