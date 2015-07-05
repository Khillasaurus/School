// file:	vgptypes.h
// created: 2011/10/14
//

#ifndef __VGPTYPES_H
#define __VGPTYPES_H


//char
//bool

typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned short Uint16;
typedef signed short Sint16;
typedef unsigned int Uint32;
typedef signed int Sint32;

#if defined(WIN32)
typedef unsigned __int64 Uint64;
typedef signed __int64 Sint64;
//typedef unsigned __int128 Uint128;
//typedef signed __int128 Sint128;
#elif defined (OSX)
typedef unsigned long long Uint64;
typedef signed long long Sint64;
#endif



#endif
