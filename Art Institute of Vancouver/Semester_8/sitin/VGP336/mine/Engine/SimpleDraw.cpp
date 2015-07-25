//====================================================================================================
// Filename:	SimpleDraw.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SimpleDraw.h"

#include "Camera.h"
#include "Color.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"
#include "MeshUtil.h"
#include "PixelShader.h"
#include "VertexShader.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	struct SimpleVertex
	{
		Math::Vector3 position;
		Color color;

		SimpleVertex()
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f)
		{}

		SimpleVertex(f32 x, f32 y, f32 z, const Color& color)
			: position(x, y, z)
			, color(color)
		{}
	};

	struct CBSimpleDraw
	{
		Math::Matrix transform;
	};
}

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace SimpleDraw
{

class SimpleDrawImpl
{
public:
	// Constructor
	SimpleDrawImpl(GraphicsSystem& gs);

	//.Destructor
	~SimpleDrawImpl();

	// Functions to startup/shutdown simple draw
	void Initialize(u32 maxVertices);
	void Terminate();

	// Functions to add 3D lines
	void AddLine(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, const Color& color);
	void AddAABB(f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY, f32 maxZ, const Color& color);
	void AddSphere(f32 x, f32 y, f32 z, f32 radius, const Color& color, u32 slices, u32 rings);

	// Functions to add screen lines
	void AddScreenLine(f32 x0, f32 y0, f32 x1, f32 y1, const Color& color);
	void AddScreenRect(f32 l, f32 t, f32 r, f32 b, const Color& color);
	void AddScreenCircle(f32 x, f32 y, f32 r, const Color& color);

	// Function to render all the lines added
	void Render(const Camera& camera);

private:
	GraphicsSystem& mGS;
	
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	TypedConstantBuffer<CBSimpleDraw> mConstantBuffer;

	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer* mpVertexBuffer2D;

	SimpleVertex* mpVertices3D;
	SimpleVertex* mpVertices2D;

	u32 mMaxVertices;
	u32 mNumVertices3D;
	u32 mNumVertices2D;

	bool mInitialized;
};

//====================================================================================================
// Class Definitions
//====================================================================================================

SimpleDrawImpl::SimpleDrawImpl(GraphicsSystem& gs)
	: mGS(gs)
	, mpVertexBuffer(nullptr)
	, mpVertexBuffer2D(nullptr)
	, mpVertices3D(nullptr)
	, mpVertices2D(nullptr)
	, mMaxVertices(0)
	, mNumVertices2D(0)
	, mNumVertices3D(0)
	, mInitialized(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SimpleDrawImpl::~SimpleDrawImpl()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::Initialize(u32 maxVertices)
{
	ASSERT(!mInitialized, "[SimpleDraw] Already initialized.");

	const u32 kVertexFormat = VF_Position | VF_Color;
	mVertexShader.Initialize(mGS, L"../Engine/Shaders/SimpleDraw.fx", "VS", "vs_4_0", kVertexFormat);
	mPixelShader.Initialize(mGS, L"../Engine/Shaders/SimpleDraw.fx", "PS", "ps_4_0");
	mConstantBuffer.Initialize(mGS);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = maxVertices * sizeof(SimpleVertex);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	// Create vertex buffers for 3D/2D lines
	mGS.GetDevice()->CreateBuffer(&bd, nullptr, &mpVertexBuffer);
	mGS.GetDevice()->CreateBuffer(&bd, nullptr, &mpVertexBuffer2D);

	// Create line buffers
	mpVertices3D = new SimpleVertex[maxVertices];
	mpVertices2D = new SimpleVertex[maxVertices];

	mMaxVertices = maxVertices;
	mNumVertices3D = 0;
	mNumVertices2D = 0;

	// Set flag
	mInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::Terminate()
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Release everything
	if (mpVertices2D != nullptr)
	{
		delete[] mpVertices2D;
		mpVertices2D = nullptr;
	}
	if (mpVertices3D != nullptr)
	{
		delete[] mpVertices3D;
		mpVertices3D = nullptr;
	}

	SafeRelease(mpVertexBuffer2D);
	SafeRelease(mpVertexBuffer);

	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

	// Clear flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddLine(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, const Color& color)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Check if we have enough space
	if (mNumVertices3D + 2 <= mMaxVertices)
	{
		// Add line
		mpVertices3D[mNumVertices3D++] = SimpleVertex(x0, y0, z0, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(x1, y1, z1, color);
	}

	ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddAABB(f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY, f32 maxZ, const Color& color)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Check if we have enough space
	if (mNumVertices3D + 24 <= mMaxVertices)
	{
		// Add lines
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);

		mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);
		mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);
	}
	
	ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddSphere(f32 x, f32 y, f32 z, f32 radius, const Color& color, u32 slices, u32 rings)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");
	
	const u32 kSlices = Math::Max(3u, slices);
	const u32 kRings = Math::Max(2u, rings);
	const u32 kLines = (4 * kSlices * kRings) - (2 * kSlices);

	// Check if we have enough space
	if (mNumVertices3D + kLines <= mMaxVertices)
	{
		// Add lines
		const f32 kTheta = Math::kPi / (f32)kRings;
		const f32 kPhi = Math::kTwoPi / (f32)kSlices;
		for (u32 j = 0; j < kSlices; ++j)
		{
			for (u32 i = 0; i < kRings; ++i)
			{
				const f32 a = i * kTheta;
				const f32 b = a + kTheta;
				const f32 ay = radius * cos(a);
				const f32 by = radius * cos(b);

				const f32 theta = j * kPhi;
				const f32 phi = theta + kPhi;

				const f32 ar = sqrt(radius * radius - ay * ay);
				const f32 br = sqrt(radius * radius - by * by);

				const f32 x0 = x + (ar * sin(theta));
				const f32 y0 = y + (ay);
				const f32 z0 = z + (ar * cos(theta));

				const f32 x1 = x + (br * sin(theta));
				const f32 y1 = y + (by);
				const f32 z1 = z + (br * cos(theta));

				const f32 x2 = x + (br * sin(phi));
				const f32 y2 = y + (by);
				const f32 z2 = z + (br * cos(phi));

				mpVertices3D[mNumVertices3D++] = SimpleVertex(x0, y0, z0, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(x1, y1, z1, color);

				if (i < kRings - 1)
				{
					mpVertices3D[mNumVertices3D++] = SimpleVertex(x1, y1, z1, color);
					mpVertices3D[mNumVertices3D++] = SimpleVertex(x2, y2, z2, color);
				}
			}
		}
	}

	ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddScreenLine(f32 x0, f32 y0, f32 x1, f32 y1, const Color& color)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Check if we have enough space
	if (mNumVertices2D + 2 <= mMaxVertices)
	{
		// Add line
		mpVertices2D[mNumVertices2D++] = SimpleVertex(x0, y0, 0.0f, color);
		mpVertices2D[mNumVertices2D++] = SimpleVertex(x1, y1, 0.0f, color);
	}
	
	ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddScreenRect(f32 l, f32 t, f32 r, f32 b, const Color& color)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Check if we have enough space
	if (mNumVertices2D + 8 <= mMaxVertices)
	{
		// Add lines
		mpVertices2D[mNumVertices2D++] = SimpleVertex(l, t, 0.0f, color);
		mpVertices2D[mNumVertices2D++] = SimpleVertex(r, t, 0.0f, color);

		mpVertices2D[mNumVertices2D++] = SimpleVertex(r, t, 0.0f, color);
		mpVertices2D[mNumVertices2D++] = SimpleVertex(r, b, 0.0f, color);

		mpVertices2D[mNumVertices2D++] = SimpleVertex(r, b, 0.0f, color);
		mpVertices2D[mNumVertices2D++] = SimpleVertex(l, b, 0.0f, color);

		mpVertices2D[mNumVertices2D++] = SimpleVertex(l, b, 0.0f, color);
		mpVertices2D[mNumVertices2D++] = SimpleVertex(l, t, 0.0f, color);
	}

	ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::AddScreenCircle(f32 x, f32 y, f32 r, const Color& color)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	// Check if we have enough space
	if (mNumVertices2D + 32 <= mMaxVertices)
	{
		// Add line
		const f32 kAngle = Math::kPi / 8.0f;
		for (u32 i = 0; i < 16; ++i)
		{
			const f32 alpha = i * kAngle;
			const f32 beta = alpha + kAngle;
			const f32 x0 = x + (r * sin(alpha));
			const f32 y0 = y + (r * cos(alpha));
			const f32 x1 = x + (r * sin(beta));
			const f32 y1 = y + (r * cos(beta));
			mpVertices2D[mNumVertices2D++] = SimpleVertex(x0, y0, 0.0f, color);
			mpVertices2D[mNumVertices2D++] = SimpleVertex(x1, y1, 0.0f, color);
		}
	}

	ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
}

//----------------------------------------------------------------------------------------------------

void SimpleDrawImpl::Render(const Camera& camera)
{
	ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

	Math::Matrix matView = camera.GetViewMatrix();
	Math::Matrix matProj = camera.GetProjectionMatrix();

	mVertexShader.Bind(mGS);
	mPixelShader.Bind(mGS);

	CBSimpleDraw cb;
	cb.transform = Math::Transpose(matView * matProj);
	mConstantBuffer.Set(mGS, cb);
	mConstantBuffer.BindVS(mGS, 0);
	
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	// Draw 3D lines
	D3D11_MAPPED_SUBRESOURCE resource;
	mGS.GetContext()->Map(mpVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, mpVertices3D, mNumVertices3D * stride);
	mGS.GetContext()->Unmap(mpVertexBuffer, 0);
	
	mGS.GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	mGS.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	mGS.GetContext()->Draw(mNumVertices3D, 0);
	
	const u32 w = mGS.GetWidth();
	const u32 h = mGS.GetHeight();
	Math::Matrix matInvScreen
	(
		2.0f/w,  0.0f,   0.0f, 0.0f,
		0.0f,   -2.0f/h, 0.0f, 0.0f,
		0.0f,    0.0f,   1.0f, 0.0f,
		-1.0f,   1.0f,   0.0f, 1.0f
	);
	cb.transform = Math::Transpose(matInvScreen);
	mConstantBuffer.Set(mGS, cb);
	mConstantBuffer.BindVS(mGS, 0);
	
	// Draw 2D lines
	mGS.GetContext()->Map(mpVertexBuffer2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, mpVertices2D, mNumVertices2D * stride);
	mGS.GetContext()->Unmap(mpVertexBuffer2D, 0);
	
	mGS.GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer2D, &stride, &offset);
	mGS.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	mGS.GetContext()->Draw(mNumVertices2D, 0);

	// Reset index
	mNumVertices3D = 0;
	mNumVertices2D = 0;
}

//====================================================================================================
// Statics
//====================================================================================================

static SimpleDrawImpl* sSimpleDrawImpl = nullptr;

//====================================================================================================
// Function Definitions
//====================================================================================================

void Initialize(GraphicsSystem& GraphicsSystem, u32 maxVertices)
{
	if (nullptr == sSimpleDrawImpl)
	{
		sSimpleDrawImpl = new SimpleDrawImpl(GraphicsSystem);
		sSimpleDrawImpl->Initialize(maxVertices);
	}
}

//----------------------------------------------------------------------------------------------------

void Terminate()
{
	if (nullptr != sSimpleDrawImpl)
	{
		sSimpleDrawImpl->Terminate();
		delete sSimpleDrawImpl;
		sSimpleDrawImpl = nullptr;
	}
}

//----------------------------------------------------------------------------------------------------

void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddLine(v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, color);
}

//----------------------------------------------------------------------------------------------------

void AddLine(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddLine(x0, y0, z0, x1, y1, z1, color);
}

//----------------------------------------------------------------------------------------------------

void AddAABB(const Math::Vector3& center, f32 extend, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddAABB(center.x - extend, center.y - extend, center.z - extend, center.x + extend, center.y + extend, center.z + extend, color);
}

//----------------------------------------------------------------------------------------------------

void AddAABB(const Math::Vector3& min, const Math::Vector3& max, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

//----------------------------------------------------------------------------------------------------

void AddAABB(f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY, f32 maxZ, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddAABB(minX, minY, minZ, maxX, maxY, maxZ, color);
}

//----------------------------------------------------------------------------------------------------

void AddSphere(const Math::Vector3& center, f32 radius, const Color& color, u32 slices, u32 rings)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddSphere(center.x, center.y, center.z, radius, color, slices, rings);
}

//----------------------------------------------------------------------------------------------------

void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenLine(v0.x, v0.y, v1.x, v1.y, color);
}

//----------------------------------------------------------------------------------------------------

void AddScreenLine(f32 x0, f32 y0, f32 x1, f32 y1, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenLine(x0, y0, x1, y1, color);
}

//----------------------------------------------------------------------------------------------------

void AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenRect(min.x, min.y, max.x, max.y, color);
}

//----------------------------------------------------------------------------------------------------

void AddScreenRect(f32 x, f32 y, f32 w, f32 h, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenRect(x, y, w, h, color);
}

//----------------------------------------------------------------------------------------------------

void AddScreenCircle(const Math::Vector2& center, f32 r, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenCircle(center.x, center.y, r, color);
}

//----------------------------------------------------------------------------------------------------

void AddScreenCircle(f32 x, f32 y, f32 r, const Color& color)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->AddScreenCircle(x, y, r, color);
}

//----------------------------------------------------------------------------------------------------

void Render(const Camera& camera)
{
	ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
	sSimpleDrawImpl->Render(camera);
}

} // namespace SimpleDraw