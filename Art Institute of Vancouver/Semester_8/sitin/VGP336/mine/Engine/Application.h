#ifndef INCLUDED_ENGINE_APPLICATION_H
#define INCLUDED_ENGINE_APPLICATION_H

//====================================================================================================
// Filename:	Application.h
// Created by:	Peter Chan
// Description:	Class for an application.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

struct InputEvent;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Application
{
public:
	Application();
	virtual ~Application();

	void Initialize(HINSTANCE instance, LPCSTR appName, u32 width, u32 height);
	void Terminate();
	
	void HookWindow(HWND hWnd);
	void UnhookWindow();

	void Update();
	
	bool IsRunning() const			{ return mRunning; }
	
protected:
	HINSTANCE GetInstance() const	{ return mInstance; }
	HWND GetWindow() const			{ return mWindow; }
	const char* GetAppName() const	{ return mAppName.c_str(); }
	
	bool mRunning;

private:
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void OnInitialize(u32 width, u32 height) {}
	virtual void OnTerminate() {}
	virtual bool OnInput(const InputEvent& evt) { return false; }
	virtual void OnUpdate() {}

	HINSTANCE mInstance;
	HWND mWindow;

	std::string mAppName;
};

#endif // #ifndef INCLUDED_ENGINE_APPLICATION_H