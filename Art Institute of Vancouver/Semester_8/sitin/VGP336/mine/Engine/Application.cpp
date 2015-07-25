//====================================================================================================
// Filename:	Application.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Application.h"

#include "InputEvent.h"
#include "InputTypes.h"

//====================================================================================================
// Window Message Procedure
//====================================================================================================

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	case WM_CHAR:
		{
			Application* myApp = (Application*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
			if (myApp != nullptr)
			{
				InputEvent inputEvent;
				inputEvent.type = InputEvent::Character;
				inputEvent.value = wParam;

				if (!myApp->OnInput(inputEvent))
				{
					return DefWindowProcA(hWnd, message, wParam, lParam);
				}
			}
		}
		break;
	case WM_KEYDOWN:
		{
			Application* myApp = (Application*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
			if (myApp != nullptr)
			{
				InputEvent inputEvent;
				inputEvent.type = InputEvent::KeyDown;
				inputEvent.value = wParam;

				if (!myApp->OnInput(inputEvent))
				{
					return DefWindowProcA(hWnd, message, wParam, lParam);
				}
			}
		}
		break;
	case WM_KEYUP:
		{
			Application* myApp = (Application*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
			if (myApp != nullptr)
			{
				InputEvent inputEvent;
				inputEvent.type = InputEvent::KeyUp;
				inputEvent.value = wParam;

				if (!myApp->OnInput(inputEvent))
				{
					return DefWindowProcA(hWnd, message, wParam, lParam);
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			Application* myApp = (Application*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
			if (myApp != nullptr)
			{
				InputEvent inputEvent;
				inputEvent.type = InputEvent::MouseMove;
				inputEvent.x = GET_X_LPARAM(lParam);
				inputEvent.y = GET_Y_LPARAM(lParam);

				if (!myApp->OnInput(inputEvent))
				{
					return DefWindowProcA(hWnd, message, wParam, lParam);
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			Application* myApp = (Application*)GetWindowLongPtrA(hWnd, GWL_USERDATA);
			if (myApp != nullptr)
			{
				InputEvent inputEvent;
				inputEvent.type = InputEvent::MouseDown;
				inputEvent.value = Mouse::LBUTTON;
				inputEvent.x = GET_X_LPARAM(lParam);
				inputEvent.y = GET_Y_LPARAM(lParam);

				if (!myApp->OnInput(inputEvent))
				{
					return DefWindowProcA(hWnd, message, wParam, lParam);
				}
			}
		}
		break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
		
	return 0;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

Application::Application()
	: mInstance(nullptr)
	, mWindow(nullptr)
	, mRunning(true)
{
}

//----------------------------------------------------------------------------------------------------

Application::~Application()
{
}

//----------------------------------------------------------------------------------------------------

void Application::Initialize(HINSTANCE instance, LPCSTR appName, u32 width, u32 height)
{
	mInstance = instance;
	mAppName = appName;

	OnInitialize(width, height);
}

//----------------------------------------------------------------------------------------------------

void Application::Terminate()
{
	OnTerminate();
}

//----------------------------------------------------------------------------------------------------

void Application::HookWindow(HWND hWnd)
{
	SetWindowLongPtrA(hWnd, GWL_USERDATA, (LONG)this);
	SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);

	mWindow = hWnd;
}

//----------------------------------------------------------------------------------------------------

void Application::UnhookWindow()
{
	SetWindowLongPtrA(mWindow, GWL_USERDATA, 0);
	SetWindowLong(mWindow, GWL_WNDPROC, (LONG)DefWindowProc);

	mWindow = nullptr;
}

//----------------------------------------------------------------------------------------------------

void Application::Update()
{
	OnUpdate();
}