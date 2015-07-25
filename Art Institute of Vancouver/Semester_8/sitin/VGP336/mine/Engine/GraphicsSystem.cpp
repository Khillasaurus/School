//====================================================================================================
// Filename:	GraphicsSystem.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "GraphicsSystem.h"

#include "Color.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	const D3D_DRIVER_TYPE kDriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	const UINT kNumDriverTypes = ARRAYSIZE(kDriverTypes);

	const D3D_FEATURE_LEVEL kFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	const UINT kNumFeatureLevels = ARRAYSIZE(kFeatureLevels);
}

//====================================================================================================
// Class Definitions
//====================================================================================================

GraphicsSystem::GraphicsSystem()
	: mpD3DDevice(nullptr)
	, mpImmediateContext(nullptr)
	, mpSwapChain(nullptr)
	, mpRenderTargetView(nullptr)
	, mpDepthStencilBuffer(nullptr)
	, mpDepthStencilView(nullptr)
	, mpDisableDepthStencil(nullptr)
	, mDriverType(D3D_DRIVER_TYPE_NULL)
	, mFeatureLevel(D3D_FEATURE_LEVEL_11_0)
	, mFullscreen(false)
	, mInitialized(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------
GraphicsSystem::~GraphicsSystem()
{
	ASSERT(!mInitialized, "[GraphicsSystem] Terminate() must be called to clean up!");
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::Initialize(HWND window, bool fullscreen)
{
	// Check if we have already initialized the system
	if (mInitialized)
	{
		LOG("[GraphicsSystem] System already initialized.");
		return;
	}
	
	LOG("[GraphicsSystem] Initializing...");

	// Now that we have a window that is displaying, we can continue to set up a Direct3D 11 device.
	// Setup is necessary if we are going to render any 3D scene. The first thing to do is to create
	// three objects: a device, an immediate context, and a swap chain. The immediate context is a
	// new object in Direct3D 11.

	// In Direct3D 11, the immediate context is used by the application to perform rendering onto a
	// buffer, and the device contains methods to create resources.

	// The swap chain is responsible for taking the buffer to which the device renders, and displaying
	// the content on the actual monitor screen. The swap chain contains two or more buffers, mainly
	// the front and the back. These are textures to which the device renders in order to display on
	// the monitor. The front buffer is what is being presented currently to the user. This buffer is
	// read-only and cannot be modified. The back buffer is the render target to which the device will
	// draw. Once it finishes the drawing operation, the swap chain will present the backbuffer by
	// swapping the two buffers. The back buffer becomes the front buffer, and vice versa.

	RECT rc = { 0 };
	GetClientRect(window, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	mFullscreen = fullscreen;

	// To create the swap chain, we fill out a DXGI_SWAPCHAIN_DESC structure that describes the swap
	// chain we are about to create. A few fields are worth mentioning. BackBufferUsage is a flag that
	// tells the application how the back buffer will be used. In this case, we want to render to the
	// back buffer, so we'll set BackBufferUsage to DXGI_USAGE_RENDER_TARGET_OUTPUT. The OutputWindow
	// field represents the window that the swap chain will use to present images on the screen.
	// SampleDesc is used to enable multi-sampling. Since this tutorial does not use multi-sampling,
	// SampleDesc's Count is set to 1 and Quality to 0 to have multi-sampling disabled.

	DXGI_SWAP_CHAIN_DESC descSwapChain;
	ZeroMemory(&descSwapChain, sizeof(descSwapChain));
	descSwapChain.BufferCount = 1;
	descSwapChain.BufferDesc.Width = width;
	descSwapChain.BufferDesc.Height = height;
	descSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descSwapChain.BufferDesc.RefreshRate.Numerator = 60;
	descSwapChain.BufferDesc.RefreshRate.Denominator = 1;
	descSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	descSwapChain.OutputWindow = window;
	descSwapChain.SampleDesc.Count = 1;
	descSwapChain.SampleDesc.Quality = 0;
	descSwapChain.Windowed = !fullscreen;

	HRESULT hr = S_OK;
	for (UINT driverTypeIndex = 0; driverTypeIndex < kNumDriverTypes; ++driverTypeIndex)
	{
		mDriverType = kDriverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain
		(
			nullptr,
			mDriverType,
			nullptr,
			createDeviceFlags,
			kFeatureLevels,
			kNumFeatureLevels,
			D3D11_SDK_VERSION,
			&descSwapChain,
			&mpSwapChain,
			&mpD3DDevice,
			&mFeatureLevel,
			&mpImmediateContext
		);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	ASSERT(SUCCEEDED(hr), "[GraphicsSystem] Failed to create device or swap chain.");

	// Cache swap chain description
	mpSwapChain->GetDesc(&mSwapChainDesc);

	// The next thing we need to do is to create a render target view. A render target view is a type
	// of resource view in Direct3D 11. A resource view allows a resource to be bound to the graphics
	// pipeline at a specific stage. Think of resource views as typecast in C. A chunk of raw memory
	// in C can be cast to any data type. We can cast that chunk of memory to an array of integers,
	// an array of floats, a structure, an array of structures, and so on. The raw memory itself is
	// not very useful to us if we don't know its type. Direct3D 11 resource views act in a similar
	// way. For instance, a 2D texture, analogous to the raw memory chunk, is the raw underlying
	// resource. Once we have that resource we can create different resource views to bind that
	// texture to different stages in the graphics pipeline with different formats: as a render target
	// to which to render, as a depth stencil buffer that will receive depth information, or as a
	// texture resource. Where C typecasts allow a memory chunk to be used in a different manner, so
	// do Direct3D 11 resource views.

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	ASSERT(SUCCEEDED(hr), "[GraphicsSystem] Failed to access swap chain buffer.");

	// We need to create a render target view because we would like to bind the back buffer of our
	// swap chain as a render target. This enables Direct3D 11 to render onto it. We first call
	// GetBuffer() to get the back buffer object. Optionally, we can fill in a D3D11_RENDERTARGETVIEW_DESC
	// structure that describes the render target view to be created. This description is normally the
	// second parameter to CreateRenderTargetView. However, for these tutorials, the default render
	// target view will suffice. The default render target view can be obtained by passing NULL as the
	// second parameter. Once we have created the render target view, we can call OMSetRenderTargets() on
	// the immediate context to bind it to the pipeline. This ensures the output that the pipeline renders
	// gets written to the back buffer. The code to create and set the render target view is as follows:

	hr = mpD3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mpRenderTargetView);
	SafeRelease(pBackBuffer);
	ASSERT(SUCCEEDED(hr), "[GraphicsSystem] Failed to create render target view.");

	// The depth buffer allows Direct3D to keep track of the depth of every pixel drawn to the screen.
	// The default behavior of the depth buffer in Direct3D 11 is to check every pixel being drawn to
	// the screen against the value stored in the depth buffer for that screen-space pixel. If the depth
	// of the pixel being rendered is less than or equal to the value already in the depth buffer, the
	// pixel is drawn and the value in the depth buffer is updated to the depth of the newly drawn
	// pixel. On the other hand, if the pixel being draw has a depth greater than the value already in
	// the depth buffer, the pixel is discarded and the depth value in the depth buffer remains unchanged.

	// The following code in the sample creates a depth buffer (a DepthStencil texture). It also creates
	// a DepthStencilView of the depth buffer so that Direct3D 11 knows to use it as a Depth Stencil texture.

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mpD3DDevice->CreateTexture2D(&descDepth, nullptr, &mpDepthStencilBuffer);
	ASSERT(SUCCEEDED(hr), "[GraphicsSystem] Failed to create depth stencil buffer.");

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = mpD3DDevice->CreateDepthStencilView(mpDepthStencilBuffer, &descDSV, &mpDepthStencilView);
	ASSERT(SUCCEEDED(hr), "[GraphicsSystem] Failed to create depth stencil view.");
	
	// Set the render target view and depth stencil view
	mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);
		
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = false;
	mpD3DDevice->CreateDepthStencilState(&depthStencilDesc, &mpDisableDepthStencil);

	// The last thing we need to set up before Direct3D 11 can render is initialize the viewport. The
	// viewport maps clip space coordinates, where X and Y range from -1 to 1 and Z ranges from 0 to 1,
	// to render target space, sometimes known as pixel space. In Direct3D 9, if the application does
	// not set up a viewport, a default viewport is set up to be the same size as the render target.
	// In Direct3D 11, no viewport is set by default. Therefore, we must do so before we can see anything
	// on the screen. Since we would like to use the entire render target for the output, we set the top
	// left point to (0, 0) and width and height to be identical to the render target's size. To do this,
	// use the following code:

	// Setup the viewport
	mViewport.Width = (FLOAT)width;
	mViewport.Height = (FLOAT)height;
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mpImmediateContext->RSSetViewports(1, &mViewport);

	// Initializes the COM library
	CoInitialize(nullptr);

	// Set flag
	mInitialized = true;

	LOG("[GraphicsSystem] System initialized.");
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::Terminate()
{
	// Check if we have already terminated the system
	if (!mInitialized)
	{
		LOG("[GraphicsSystem] System already terminated.");
		return;
	}

	LOG("[GraphicsSystem] Terminating...");

	SafeRelease(mpDisableDepthStencil);
	SafeRelease(mpDepthStencilView);
	SafeRelease(mpDepthStencilBuffer);
	SafeRelease(mpRenderTargetView);
	SafeRelease(mpSwapChain);
	SafeRelease(mpImmediateContext);
	SafeRelease(mpD3DDevice);

	// Set flag
	mInitialized = false;

	LOG("[GraphicsSystem] System terminated.");
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::BeginRender(const Color& clearColor)
{
	mpImmediateContext->ClearRenderTargetView(mpRenderTargetView, *(float(*)[4])&clearColor);
	mpImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::EndRender()
{
	mpSwapChain->Present(0, 0);
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::ToggleFullscreen()
{
	mFullscreen = !mFullscreen;
	mpSwapChain->SetFullscreenState(mFullscreen, nullptr);
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::ResetRenderTarget()
{
	ASSERT(mpImmediateContext != nullptr, "[GraphicsSystem] Failed to reset render target.");
	mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::ResetViewport()
{
	ASSERT(mpImmediateContext != nullptr, "[GraphicsSystem] Failed to reset viewport.");
	mpImmediateContext->RSSetViewports(1, &mViewport);
}

//----------------------------------------------------------------------------------------------------

void GraphicsSystem::EnableDepthTesting(bool enable)
{
	ASSERT(mpImmediateContext != nullptr, "[GraphicsSystem] Failed to set depth stencil state.");
	mpImmediateContext->OMSetDepthStencilState(enable ? nullptr : mpDisableDepthStencil, 0);
}

//----------------------------------------------------------------------------------------------------

u32 GraphicsSystem::GetWidth() const
{
	ASSERT(mpSwapChain != nullptr, "[GraphicsSystem] Failed to get swap chain buffer width.");
	return mSwapChainDesc.BufferDesc.Width;
}

//----------------------------------------------------------------------------------------------------

u32 GraphicsSystem::GetHeight() const
{
	ASSERT(mpSwapChain != nullptr, "[GraphicsSystem] Failed to get swap chain buffer width.");
	return mSwapChainDesc.BufferDesc.Height;
}