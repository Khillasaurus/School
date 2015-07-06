// File:	vgptypes.h
// Created:	2012/01/06
// Copyright by Daniel Schenker 2012

#ifndef _VGPTYPES_H
#define _VGPTYPES_H

// data types
// char;								//8 bits	== 1 byte	== 256 values
// short;								//16 bits	== 2 bytes	== 65535 values
// int;									//32 bits	== 4 bytes	== 4,294,967,295 values
// long;								//32 bits	== 4 bytes
// float;								//32 bits	== 4 bytes
// double;								//64 bits	== 8 bytes
// __int64;								//64 bits	== 8 bytes	== 2.5 sextillion
// __int128;							//128 bits	== 16 bytes	== many many
typedef unsigned char		Uint8;		// 0 to 255
typedef signed char			Sint8;		// -128 to 127
typedef unsigned short		Uint16;		//
typedef signed short		Sint16;		//
typedef unsigned int		Uint32;		//
typedef signed int			Sint32;		//
#if defined(WIN32)						// can also be written   #ifdef WIN32
typedef unsigned __int64	Uint64;		//
typedef signed __int64		Sint64;		//
//typedef unsigned __int128	Uint128;	//
//typedef signed __int128		Sint128;	//
#else	// OSX, unix, or solaris
typedef unsigned long long	Uint64;		//
typedef signed long long	Sint64;		//
//typedef unsigned __int128	Uint128;	//not sure about this
//typedef signed __int128	Sint128;	//not sure about this
#endif

#define U64toU32(x) ((Uint32)((Uint64)x & (Uint64)0x00000000ffffffff))

#endif