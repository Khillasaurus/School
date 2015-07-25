#ifndef INCLUDED_ENGINE_HASH_H
#define INCLUDED_ENGINE_HASH_H

//====================================================================================================
// Filename:	Hash.h
// Created by:	Peter Chan
// Description:	Helper function for generating a hash key.
//====================================================================================================

//====================================================================================================
// Function Declarations
//====================================================================================================

u64 GetHash(const char* str);
u64 GetHash(const wchar_t* wstr);

#endif // #ifndef INCLUDED_ENGINE_HASH_H