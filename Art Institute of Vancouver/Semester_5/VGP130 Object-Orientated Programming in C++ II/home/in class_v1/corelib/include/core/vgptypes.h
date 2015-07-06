//-----------------------------
// File:		vgptypes.h
// Created:		2012/01/06
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __VGPTYPES_H
	#define __VGPTYPES_H
	//Data types
	typedef unsigned char		Uint8;
	typedef signed char			Sint8;
	typedef unsigned short		Uint16;
	typedef signed short		Sint16;
	typedef unsigned int		Uint32;
	typedef signed int			Sint32;

	#if defined(WIN32)// can also be written   #ifdef WIN32
		typedef unsigned __int64	Uint64;
		typedef signed __int64		Sint64;
		//typedef unsigned __int128	Uint128;
		//typedef signed __int128	Sint128;
	#else	// OSX, unix, or solaris
		typedef unsigned long long	Uint64;
		typedef signed long long	Sint64;
		//typedef unsigned __int128	Uint128;
		//typedef signed __int128	Sint128;
	#endif

	#define U64toU32(x) ((Uint32)((Uint64)x & (Uint64)0x00000000ffffffff))
#endif//__VGPTYPES_H