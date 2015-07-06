//PUT THIS IN CORE LIB!!!

#ifndef  __AUTOREFCOUNT_H
#define __AUTOREFCOUNT_H

//T will require:
	//Sint32 AddRef();
	//Sint32 Release();

template <class T>
class cAutoRefCount
{
public:
	cAutoRefCount(T* pObj = NULL)
	:	mpObj(pObj)
	{
		if(mpObj)
		{
			mpObj->AddRef();
		}
	}

	cAutoRefCount(const cAutoRefCount<T>& rhs)
	:	mpObj(rhs.mpObj)
	{
		if(mpObj)
		{
			mpObj->Release();
		}
		mpObj = mpObj;
		if(mpObj)
		{
			mpObj->AddRef();
		}
	}

	const cAutoRefCount &operator=(T* pObj)
	{
		if(mpObj != pObj)
		{
			if(mpObj)
			{
				mpObj->Release();
			}
			mpObj = pObj;
			if(mpObj)
			{
				mpObj->AddRef();
			}
		}
		return (*this);
	}

	const cAutoRefCount &operator=(const cAutoRefCount& rhs)
	{
		if(mpObj)
		{
			mpObj->Release();
		}
		mpObj = rhs.mpObj;
		if(mpObj)
		{
			mpObj->AddRef();
		}
		return (*this);
	}

	~cAutoRefCount()
	{
		if(mpObj)
		{
			mpObj->Release();
		}
	}

	//magic...
	T& operator *() const
	{
		return (*mpObj);
	}
	//cEvent* pEvent;
	//pEvent->mId;
	//preserve visual consistency
	T operator ->() const
	{
		return (mpObj);
	}
	//cast operator
	operator T*() const
	{
		return mpObj;
	}

public:
	T* mpObj;
};

#endif