#ifndef INCLUDED_ENGINE_GRAPHICSSYSTEM_H
#define INCLUDED_ENGINE_GRAPHICSSYSTEM_H

//====================================================================================================
// Filename:	GraphicsSystem.h
// Created by:	Peter Chan
// Description:	Class for the graphics system.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

struct Color;

//====================================================================================================
// Class Declarations
//====================================================================================================

class GraphicsSystem
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	void Initialize(HWND window, bool fullscreen);
	void Terminate();

	void BeginRender(const Color& clearColor);
	void EndRender();

	void ToggleFullscreen();
	void ResetRenderTarget();
	void ResetViewport();

	void EnableDepthTesting(bool enable);
	
	u32 GetWidth() const;
	u32 GetHeight() const;

	ID3D11Device* GetDevice()			{ return mpD3DDevice; }
	ID3D11DeviceContext* GetContext()	{ return mpImmediateContext; }
	
private:
	NONCOPYABLE(GraphicsSystem);

	ID3D11Device* mpD3DDevice;
	ID3D11DeviceContext* mpImmediateContext;

	IDXGISwapChain* mpSwapChain;
	ID3D11RenderTargetView* mpRenderTargetView;

	ID3D11Texture2D* mpDepthStencilBuffer;
	ID3D11DepthStencilView* mpDepthStencilView;
	ID3D11DepthStencilState* mpDisableDepthStencil;

	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;

	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

	D3D11_VIEWPORT mViewport;
	
	bool mFullscreen;
	bool mInitialized;
};

#endif // #ifndef INCLUDED_ENGINE_GRAPHICSSYSTEM_H