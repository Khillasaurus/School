#ifndef INCLUDED_ENGINE_WINDOW_H
#define INCLUDED_ENGINE_WINDOW_H

//====================================================================================================
// Filename:	Window.h
// Created by:	Peter Chan
// Description:	Class for a Win32 application window.
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

class Window
{
public:
	Window();
	virtual ~Window();

	void Initialize(HINSTANCE instance, LPCSTR appName, u32 width, u32 height);
	void Terminate();

	bool HandleMessage();

	HWND GetWindowHandle() const { return mWindow; }

private:
	HINSTANCE mInstance;
	HWND mWindow;

	std::string mAppName;
};

#endif // #ifndef INCLUDED_ENGINE_WINDOW_H