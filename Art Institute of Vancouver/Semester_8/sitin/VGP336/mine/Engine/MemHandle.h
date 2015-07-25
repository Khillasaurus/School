#ifndef INCLUDED_ENGINE_MEMHANDLE_H
#define INCLUDED_ENGINE_MEMHANDLE_H

//====================================================================================================
// Filename:	MemHandle.h
// Created by:	Peter Chan
// Description:	Class for a handle to a memory block.
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

template <
class MemHandle
{
public:

	META_DECLARE(MemHandle);

	static MetaClass* GetMetaClass();
	MetaClass* GetMetaClass();

	MemHandle();
	MemHandle(u16 instance, u16 index);

	u16 GetInstance() const					{ return mInstance; }
	u16 GetIndex() const					{ return mIndex; }

	bool IsValid() const					{ return mInstance != U16_MAX && mIndex != U16_MAX; }
	void Invalidate()						{ mInstance = U16_MAX; mIndex = U16_MAX; }

	bool operator==(MemHandle rhs) const	{ return mInstance == rhs.mInstance && mIndex == rhs.mIndex; }
	bool operator!=(MemHandle rhs) const	{ return mInstance != rhs.mInstance && mIndex != rhs.mIndex; }
	bool operator<(MemHandle rhs) const		{ return mInstance < rhs.mInstance && mIndex < rhs.mIndex; }

private:
	u16 mInstance;
	u16 mIndex;
};

#endif // #ifndef INCLUDED_ENGINE_MEMHANDLE_H

class MetaClass
{
public:

private:
	static MetaType* mFields;
};


MemHandle::GetMetaClass()->


template <typename T>
MetaClass* GetTypeInfo()
{
	T::GetMetaClass();
}