//
// File: aierror.h 
// Date: 2012/04/02
// Copyright 2012 Me
//

#ifndef __AIERROR_H
#define __AIERROR_H

#ifdef DEBUG

namespace AIDebug
{
	bool AssertFunc( bool expresion, const char *pExpr, const char *pDesc, int line, const char *pFile, bool *ignoreAlways );
	void DebugMessageV( const char *pFormat, ... );
	void DebugMsgF( const char *pBuf);
}

#define AIAssert(condition)				_AIAssert(condition, #condition )
#define AIAssertMsg(condition, msg)		_AIAssert(condition, msg )
#define dbPrintf						AIDebug::DebugMessageV

#define _AIAssert( exp, desc ) \
{ \
	static bool ignoreAlways = false; \
	if( !ignoreAlways ) \
	{ \
		if( AIDebug::AssertFunc( ((int)(exp)), #exp, (char*)desc, __LINE__, __FILE__, &ignoreAlways ) )\
		{\
			BREAKPOINT; \
		} \
	} \
}

#if defined(WIN32)
    #define BREAKPOINT 	do{ void __cdecl :: __debugbreak(void); __debugbreak(); } while(0)
#endif

#else  // RELEASE
#define AIAssert(condition)				
#define AIAssertMsg(condition, msg)		
#define dbPrintf __noop

#endif


#endif
