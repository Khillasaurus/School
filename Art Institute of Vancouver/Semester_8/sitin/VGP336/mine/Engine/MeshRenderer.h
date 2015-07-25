#ifndef INCLUDED_ENGINE_MESHRENDERER_H
#define INCLUDED_ENGINE_MESHRENDERER_H

//====================================================================================================
// Filename:	MeshRenderer.h
// Created by:	Peter Chan
// Description:	Class for rendering a 3D mesh.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexShader.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace Math
{
	struct Matrix;
}
class Camera;
class GraphicsSystem;
class MeshBuffer;

//====================================================================================================
// Class Declarations
//====================================================================================================

class MeshRenderer
{
public:

	MeshRenderer();
	~MeshRenderer();

	void Initialize(GraphicsSystem& gs);
	void Terminate();

	void SetCamera(Camera& camera);
	void SetTexture(Texture& texture);

	void Render(MeshBuffer& meshBuffer, const Math::Matrix& transform);

private:
	NONCOPYABLE(MeshRenderer);

	struct CBuffer
	{
		XMMATRIX matWorld;
		XMMATRIX matWVP;
		XMVECTOR viewPosition;
		XMVECTOR lightDirection;
		XMVECTOR ambientLight;
		XMVECTOR diffuseLight;
		XMVECTOR specularLight;
		XMVECTOR ambientMaterial;
		XMVECTOR diffuseMaterial;
		XMVECTOR specularMaterial;
		f32 specularPower;
	};

	GraphicsSystem* mpGraphicsSystem;
	Camera* mpCamera;
	Texture* mpTexture;

	TypedConstantBuffer<CBuffer> mCBuffer;

	VertexShader mVertexShader;
	PixelShader mPixelShader;

	Texture mDefaultTexture;
	Sampler mSampler;

	bool mInitialized;
};

#endif // #ifndef INCLUDED_ENGINE_MESHRENDERER_H