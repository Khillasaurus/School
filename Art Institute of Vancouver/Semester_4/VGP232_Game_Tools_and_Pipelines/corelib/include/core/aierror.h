//-----------------------------
// File:		aierror.h
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __AIERROR_H
#define __AIERROR_H

#if defined(DEBUG)

namespace AIDebug
{
	bool AssertFunc(bool expression, const char *pExpr, const char *pDesc, int line, const char * pFile, bool *ignoreAlways);
	void DebugMessageV(const char *pFormat, ...);
	void DebugMessageF(const char *pBuf);
}

#define AIAssert(condition)				_AIAssert(condition, #condition)
#define AIAssertMsg(condition, msg)		_AIAssert(condition, msg)
#define dbPrintf						AIDebug::DebugMessageV

#define _AIAssert(exp, desc) \
{ \
	static bool ignoreAlways = false; \
	if(!ignoreAlways) \
	{ \
		if(AIDebug::AssertFunc( exp, #exp, (char*)desc, __LINE__, __FILE__, &ignoreAlways)) \
		{ \
			BREAKPOINT; \
		} \
	} \
}

#if defined(WIN32)
	#define BREAKPOINT	do{void __cdecl :: __debugbreak(void); __debugbreak(); } while(0)
#elif defined(PLATFORM_OSX)	|| defined(PLATFORM_IPAD) // IA-32
	#define BREAKPOINT {__asm {int 3}}
	//#define BREAKPOINT {asm{trap}}		// for PPC32 or PPC64
#endif

#else // RELEASE
#define AIAssert(condition)
#define AIAssertMsg(condition, msg)
#define dbPrintf __noop
#endif

#endif // __AIERROR_H