// file:	vgptypes.h
// created:	2012/01/20
// Copyright 2012 by Me

#ifndef __VGPTypes_H
#define __VGPTypes_H

// data types
//char;					//  8 bits == 1 bytes ==   256 values
//short;					// 16 bits == 2 bytes == 65536 values
//int;					// 32 bits == 4 bytes == 4,294,967,295
//long;					// 32 bits == 4 bytes
//float;					// 32 bits == 4 bytes 
//double;					// 64 bits == 8 bytes
//__int64;				// 64 bits == 8 bytes == 2.5 sextillion
//__int128;				//128 bits ==16 bytes == many many

typedef unsigned char		Uint8;			// 0 - 255
typedef signed char			Sint8;			// -128 to 0 to 127
typedef unsigned short		Uint16;			// 
typedef signed short		Sint16;			// 
typedef unsigned int		Uint32;			// 
typedef signed int			Sint32;			// 
#if defined(WIN32)
typedef unsigned __int64	Uint64;			// 
typedef signed __int64		Sint64;			// 
//typedef unsigned __int128	Uint128;		// 
//typedef signed __int128		Uint128;		// 
#else // OSX, or unix or solaris
typedef unsigned long long	Uint64;			// 
typedef signed long long	Sint64;			// 
//typedef unsigned __int128	Uint128;		// 
//typedef signed __int128	Uint128;		// 
#endif



#endif // __VGPTypes_H
