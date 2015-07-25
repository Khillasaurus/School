#ifndef INCLUDED_ENGINE_DELEGATE_H
#define INCLUDED_ENGINE_DELEGATE_H

//====================================================================================================
// Filename:	Delegate.h
// Created by:	Peter Chan
// Description:	Simple delegate implementation based on the following link:
//				http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates
// TODO:		For a truly generic version, refer to (requires C++11 Variadic Template support):
//				http://blog.coldflake.com/posts/C++-delegates-on-steroids/
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename ReturnType>
class Delegate0
{
public:
	Delegate0()
		: mInstance(nullptr)
		, mInvoke(nullptr)
	{}

	ReturnType operator()() const
	{
		return (*mInvoke)(mInstance);
	}

	bool Empty() const
	{
		return mInstance == nullptr || mInvoke == nullptr;
	}

	void Clear()
	{
		mInstance = nullptr;
		mInvoke = nullptr;
	}
	
	template <class T, ReturnType (T::*MethodType)()>
	static Delegate0 Make(T* instance)
	{
		Delegate0 d;
		d.mInstance = instance;
		d.mInvoke = &Invoke<T, MethodType>;
		return d;
	}

private:
	typedef ReturnType (*InvokeType)(void*);

	void* mInstance;
	InvokeType mInvoke;

	template <class T, ReturnType (T::*MethodType)()>
	static ReturnType Invoke(void* instance)
	{
		T* ptr = static_cast<T*>(instance);
		return (ptr->*MethodType)();
	}
};

//----------------------------------------------------------------------------------------------------

template <class ReturnType, class ParamType>
class Delegate1
{
public:
	Delegate1()
		: mInstance(nullptr)
		, mInvoke(nullptr)
	{}

	ReturnType operator()(ParamType p1) const
	{
		return (*mInvoke)(mInstance, p1);
	}

	bool Empty() const
	{
		return mInstance == nullptr || mInvoke == nullptr;
	}

	void Clear()
	{
		mInstance = nullptr;
		mInvoke = nullptr;
	}
	
	template <class T, ReturnType (T::*MethodType)(ParamType)>
	static Delegate1 Make(T* instance)
	{
		Delegate1 d;
		d.mInstance = instance;
		d.mInvoke = &Invoke<T, MethodType>;
		return d;
	}

private:
	typedef ReturnType (*InvokeType)(void*, ParamType);

	void* mInstance;
	InvokeType mInvoke;

	template <class T, ReturnType (T::*MethodType)(ParamType)>
	static ReturnType Invoke(void* instance, ParamType p1)
	{
		T* ptr = static_cast<T*>(instance);
		return (ptr->*MethodType)(p1);
	}
};

#endif // #ifndef INCLUDED_ENGINE_DELEGATE_H