#ifndef INCLUDED_ENGINE_TERRAIN_H
#define INCLUDED_ENGINE_TERRAIN_H

//====================================================================================================
// Filename:	Terrain.h
// Created by:	Peter Chan
// Description:	Class for rendering a terrain.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ConstantBuffer.h"
#include "Heightmap.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
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
class Texture;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Terrain
{
public:

	Terrain();
	~Terrain();

	void Initialize(GraphicsSystem& gs, const char* pFilename, u32 width, u32 length, f32 maxHeight);
	void Terminate();

	void SetCamera(Camera& camera);
	void SetLayer(Texture* pTexture, u32 layer, f32 minHeight, f32 maxHeight, f32 frequency);

	f32 GetHeight(const Math::Vector3& position);

	void Render();

private:
	NONCOPYABLE(Terrain);

	static const u32 kMaxTerrainLayers = 4;

	struct CBuffer
	{
		XMMATRIX matWVP;
		XMVECTOR layer[kMaxTerrainLayers];
	};

	GraphicsSystem* mpGraphicsSystem;
	Camera* mpCamera;

	TypedConstantBuffer<CBuffer> mCBuffer;

	VertexShader mVertexShader;
	PixelShader mPixelShader;

	Heightmap mHeightmap;
	Mesh mTerrainMesh;
	MeshBuffer mTerrain;

	Texture* mpTerrainLayers[kMaxTerrainLayers];
	Math::Vector3 mLayerInfo[kMaxTerrainLayers];

	Sampler mSampler;

	bool mInitialized;
};

#endif // #ifndef INCLUDED_ENGINE_TERRAIN_H