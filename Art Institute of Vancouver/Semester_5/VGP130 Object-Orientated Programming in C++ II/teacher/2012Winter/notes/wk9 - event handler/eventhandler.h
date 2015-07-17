// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#ifndef __EVENTHANDLER_H
#define __EVENTHANDLER_H

//class CallbackBase 
//{
//public:
//    virtual Uint32 operator()(void* pEvent) const { return 0; };
//    virtual ~CallbackBase()
//    {
//    }
//};
//template<typename T, typename E>
//class Callback
//{
//public:
//    typedef Uint32 (T::*FUNC_PTRARG)(E* pEvent);
//
//    Callback( T *t, FUNC_PTRARG f ) : _this(t), _func1(f)  {}
//    Callback( const Callback &rhs) 
//		:	_this(rhs._this)
//		,	_func1(rhs._func1)  
//	{}
//    Callback &operator =(const Callback &rhs)
//	{
//		_this = rhs._this;
//		_func1 = rhs._func1;
//		return (*this);
//	}
//
//
//    Uint32 operator()(void* pEvent) const
//    {
//        return (_this->*_func1)((E*)(pEvent));
//    }
//
//private:
//    // pointer to the class instance the function will be scoped to
//    T *_this;
//    // function bound to a specified Uint32 event constant
//    FUNC_PTRARG  _func1;
//};

// ---------------------------------

class cIEventTarget
{
public:
	virtual ~cIEventTarget(){}
	virtual void OnEvent(Uint32 eventId) = 0;
};

// ---------------------------------

//NOTE if using EventHandler as a template, above interface is moot
//template< class T >
class cEventHandler
{
public:
	cEventHandler();
	bool HandleEvents();
	//version 1
	//bool RegisterTarget(cIEventTarget *pTarget);
	//version 2
	bool RegisterTarget(Uint32 eventId, cIEventTarget *pTarget);
	bool PostEvent(Uint32 eventId);

protected:
	// version 1
	//typedef vector< cIEventTarget *> tTargetList;
	//		version 1 (as template)
	//		typedef vector< T *> tTargetList;
	//tTargetList mEventTargets;

	// version 2
	typedef multimap< Uint32, cIEventTarget *> tEventTargetMap;

	// version 3
	//typedef multimap< Uint32, CallbackBase*> tEventTargetMap;
	typedef tEventTargetMap::iterator tEventTargetMapIter;
	typedef pair< tEventTargetMapIter, tEventTargetMapIter> tEventTargetMapRangeIter;
	tEventTargetMap mEventTargets;

	typedef queue< Uint32 > tEventQueue;
	tEventQueue mEvents;
};

// template Outofclassdecl impl
//#include "eventhandler.inl"
//
//template<class T>
//bool cEventHandler<T>::PostEvent(Uint32 eventId)
//{
//	mEvents.push( eventId );
//	return true;
//}

#endif //__EVENTHANDLER_H