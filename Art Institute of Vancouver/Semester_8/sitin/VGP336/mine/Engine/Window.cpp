//====================================================================================================
// Filename:	Window.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Window.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Window::Window()
	: mInstance(nullptr)
	, mWindow(nullptr)
{
}

//----------------------------------------------------------------------------------------------------

Window::~Window()
{
}

//----------------------------------------------------------------------------------------------------

void Window::Initialize(HINSTANCE instance, LPCSTR appName, u32 width, u32 height)
{
	mAppName = appName;

	// Every Windows Window requires at least oen window object. Three things are involved:
	// 1)	Register a window class.
	// 2)	Create a window object.
	// 3)	Retrieve and dispatch messages for this window.

	// Register class
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = appName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassExA(&wcex);
	
	// Create window
	mInstance = instance;
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	
	const s32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const s32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
	const s32 winWidth = rc.right - rc.left;
	const s32 winHeight = rc.bottom - rc.top;
	const s32 left = (screenWidth - winWidth) / 2;
	const s32 top = (screenHeight - winHeight) / 2;

	mWindow = CreateWindowA
	(
		appName,
		appName,
		WS_OVERLAPPEDWINDOW,
		left,
		top,
		winWidth,
		winHeight,
		nullptr,
		nullptr,
		instance,
		nullptr
	);

	ShowWindow(mWindow, true);
	SetCursorPos(screenWidth / 2, screenHeight / 2);
}

//----------------------------------------------------------------------------------------------------

void Window::Terminate()
{
	DestroyWindow(mWindow);

	UnregisterClassA(mAppName.c_str(), mInstance);
}

//----------------------------------------------------------------------------------------------------

bool Window::HandleMessage()
{
	MSG msg = {0};
	
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (WM_QUIT == msg.message);
}