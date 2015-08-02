//====================================================================================================
// Filename:	MemHandle.inl
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Statics
//====================================================================================================

template <typename DataType>
MemoryPool<DataType>* MemHandle<DataType>::sMemoryPool = nullptr;


//====================================================================================================
// Class Definitions
//====================================================================================================

template <typename DataType>
MemHandle<DataType>::MemHandle()
	: mInstance(U16_MAX)
	, mIndex(U16_MAX)
{
}

//----------------------------------------------------------------------------------------------------

template <typename DataType>
MemHandle<DataType>::MemHandle(u16 instance, u16 index)
	: mInstance(instance)
	, mIndex(index)
{
}

//----------------------------------------------------------------------------------------------------

template <typename DataType>
bool MemHandle<DataType>::IsValid() const
{
	return sMemoryPool && sMemoryPool->IsValid(*this);
}

//----------------------------------------------------------------------------------------------------

template <typename DataType>
void MemHandle<DataType>::Invalidate()
{
	mInstance = U16_MAX;
	mIndex = U16_MAX;
}

//----------------------------------------------------------------------------------------------------

template <typename DataType>
DataType* MemHandle<DataType>::Get()
{
	DataType* data = nullptr;
	if(sMemoryPool)
	{
		data = sMemoryPool->Get(*this);
	}
	return data;
}