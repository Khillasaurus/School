//====================================================================================================
// Filename:	MemoryPool.inl
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Class Definitions
//====================================================================================================

template <typename Handle, typename DataType>
MemoryPool<Handle, DataType>::MemoryPool(u16 capacity)
	: mData(nullptr)
	, mInstanceCount(nullptr)
	, mSize(0)
	, mCapacity(capacity)
{
	mData = static_cast<DataType*>(malloc(sizeof(DataType) * capacity));
	mInstanceCount = new u16[capacity];
	memset(mInstanceCount, 0, sizeof(mInstanceCount) * capacity);
	mFreeSlots.reserve(capacity);
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
MemoryPool<Handle, DataType>::~MemoryPool()
{
	SafeDeleteArray(mInstanceCount);
	free(mData);
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
Handle MemoryPool<Handle, DataType>::Allocate()
{
	ASSERT(!mFreeSlots.empty() || mSize < mCapacity, "[MemoryPool] Failed to allocate. MemoryPool is full.");
	if (mFreeSlots.empty() && mSize >= mCapacity)
	{
		return Handle();
	}

	u16 index = 0;
	if (!mFreeSlots.empty())
	{
		index = mFreeSlots.back();
		mFreeSlots.pop_back();
	}
	else
	{
		index = (u16)mSize;
		++mSize;
	}

	new (&mData[index]) DataType();
	return Handle(mInstanceCount[index], index);
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
void MemoryPool<Handle, DataType>::Free(Handle handle)
{
	if (IsValid(handle))
	{
		const u16 index = handle.GetIndex();

		// Free slot
		mData[index].~DataType();
		++mInstanceCount[index];	// This invalidates all existing handles
		mFreeSlots.push_back(index);
	}
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
void MemoryPool<Handle, DataType>::Flush()
{
	for (u32 i = 0; i < mSize; ++i)
	{
		mData[i].~DataType();
		++mInstanceCount[i];
	}
	mFreeSlots.clear();
	mSize = 0;
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
bool MemoryPool<Handle, DataType>::IsValid(Handle handle) const
{
	const u16 instance = handle.GetInstance();
	const u16 index = handle.GetIndex();
	return (index < mSize - 1) && (instance == mInstanceCount[index]);
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
DataType* MemoryPool<Handle, DataType>::Get(Handle handle)
{
	DataType* ptr = nullptr;
	if (IsValid(handle))
	{
		ptr = &mData[handle.GetIndex()];
	}
	return ptr;
}

//----------------------------------------------------------------------------------------------------

template <typename Handle, typename DataType>
const DataType* MemoryPool<Handle, DataType>::Get(Handle handle) const
{
	const DataType* ptr = nullptr;
	if (IsValid(handle))
	{
		ptr = &mData[handle.GetIndex()];
	}
	return ptr;
}