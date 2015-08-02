#ifndef INCLUDED_ENGINE_MEMHANDLE_H
#define INCLUDED_ENGINE_MEMHANDLE_H

//====================================================================================================
// Filename:	MemHandle.h
// Created by:	Peter Chan
// Description:	Class for a handle to a memory block.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

template <typename DataType> class MemoryPool;

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename DataType>
class MemHandle
{
public:
	MemHandle();
	MemHandle(u16 instance, u16 index);

	bool IsValid() const;
	void Invalidate();

	DataType* Get();

	u16 GetInstance() const					{ return mInstance; }
	u16 GetIndex() const					{ return mIndex; }

	bool operator==(MemHandle rhs) const	{ return mInstance == rhs.mInstance && mIndex == rhs.mIndex; }
	bool operator!=(MemHandle rhs) const	{ return mInstance != rhs.mInstance && mIndex != rhs.mIndex; }
	bool operator<(MemHandle rhs) const		{ return mInstance < rhs.mInstance && mIndex < rhs.mIndex; }

private:
	friend class MemoryPool<DataType>;

	static MemoryPool<DataType>* sMemoryPool;

	u16 mInstance;
	u16 mIndex;
};

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "MemHandle.inl"

#endif // #ifndef INCLUDED_ENGINE_MEMHANDLE_H