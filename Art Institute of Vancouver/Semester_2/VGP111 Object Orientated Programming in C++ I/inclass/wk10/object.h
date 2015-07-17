
#ifndef __cObject_H
#define __cObject_H

class cObject
{
public:
	cObject()
	:	mRefCount(0)
	{
	}
	virtual ~cObject()
	{
	}
	virtual Uint32 AddRef()
	{
		// non-thread safe increment
		return ++mRefCount;

		//thread safe increment
		//return (static_cast<Uint32>( InterlockedIncrement( reinterpret_cast<long volatile*>(&mRefCount) ) ) );
	}
	virtual Uint32 Release()
	{
		if( !(--mRefCount ) )
		{
			delete this;
			return 0;
		}
		return mRefCount


		// thread safe decremement
		//return (static_cast<Uint32>( InterlockedDecrement( reinterpret_cast<long volatile*>(&mRefCount) ) ) );
	}
protected:
	Sint32 mRefCount;
};

#endif // __cObject_H
