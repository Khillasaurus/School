#ifndef INCLUDED_APPLICATION_H
#define INCLUDED_APPLICATION_H

//====================================================================================================
// Filename:	CApplication.h
// Created by:	Peter Chan
// Description:	Class for creating a windows application. Any new project can inherit from
//			  CApplication and extend functionality by giving new implementations to OnInitialize(),
//			  OnTerminate(), OnMainLoop().
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <windows.h>

//====================================================================================================
// Defines
//====================================================================================================

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//====================================================================================================
// Class Declarations
//====================================================================================================

class CApplication
{
public:
	// Constructor
	CApplication(void);

	// Destructor
	virtual ~CApplication(void);

	// Functions to startup and shutdown the application
	void Initialize(const char* pAppName, HINSTANCE hInstance, int iWinWidth, int iWinHeight);
	void Terminate(void);

	// Function to enter main loop
	void Run(void);

	// Function to be called when we want to quit the application
	void Quit(void);

protected:
	// Customizable functions for specific tasks
	virtual void OnInitialize(void);
	virtual void OnTerminate(void);
	virtual void OnMainLoop(void);

	// Members
	HWND mWindow;

	int mWinWidth;
	int mWinHeight;
};

#endif // #ifndef INCLUDED_APPLICATION_H