//-----------------------------
// File:		stdafx.h
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <Windows.h>
#include "targetver.h"
#include "../vgplib/include/vgp/vgptypes.h"
#include "../vgplib/include/vgp/vgptime.h"
#include "../vgplib/include/vgp/vgptimer.h"
#include "../corelib/include/core/aierror.h"
#include <queue>

using namespace std;



// TODO: reference additional headers your program requires here
