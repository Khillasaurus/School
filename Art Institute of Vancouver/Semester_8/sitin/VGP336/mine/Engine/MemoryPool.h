#ifndef INCLUDED_ENGINE_MEMORYPOOL_H
#define INCLUDED_ENGINE_MEMORYPOOL_H

//====================================================================================================
// Filename:	MemoryPool.h
// Created by:	Peter Chan
// Description:	Templatized class for a memory pool.
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename Handle, typename DataType>
class MemoryPool
{
public:
	MemoryPool(u16 capacity);
	~MemoryPool();

	Handle Allocate();
	void Free(Handle handle);
	void Flush();

	bool IsValid(Handle handle) const;

	DataType* Get(Handle handle);
	const DataType* Get(Handle handle) const;

private:
	NONCOPYABLE(MemoryPool);

	std::vector<u16> mFreeSlots;

	DataType* mData;
	u16* mInstanceCount;

	u16 mSize;
	u16 mCapacity;
};

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "MemoryPool.inl"

#endif // #ifndef INCLUDED_ENGINE_MEMORYPOOL_H