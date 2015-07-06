//------------------------------
// File:		stadfx.h
// Created:		2012/05/14
// Copyright:	Daniel Schenker
//------------------------------

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//Platform detection
#define PLATFORM_WINDOWS	1
#define PLATFORM_MAC		2
#define PLATFORM_UNIX		3
#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif

//Include Appropriate headers based on platform type
#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

//Link to the winsock library to get socket functionality
#if PLATFORM == PLATFORM_WINDOWS
	#pragma comment( lib, "wsock32.lib" )
#endif



// TODO: reference additional headers your program requires here
