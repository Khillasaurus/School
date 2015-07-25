// CCMGfx.h : main header file for the CCMGfx application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCMGfxApp:
// See CMGfx.cpp for the implementation of this class
//

class CCMGfxApp : public CWinApp
{
public:
	CCMGfxApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGraphicsDisplaywindow();

	void InitSingletons();
	void CleanUpSingletons();
	void DeleteSingletons();
};

extern CCMGfxApp theApp;