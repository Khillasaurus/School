// file:	concrete.h
// created:	2012/01/27
// Copyright 2012 by Me

#ifndef __cConcrete_H
#define __cConcrete_H

#include "sub1.h"
#include "sub2.h"

class cConcrete : public cSub1, public cSub2
{
public: // cConcrete
	virtual void Test()
	{
		std::cout<< "test = "<< Get() << std::endl;
	}
	virtual bool QI(Uint32 iid, void **ppvObj)
	{
		switch( iid )
		{
		case cBase::kIID:
			(*ppvObj) = static_cast< cBase *>( static_cast< cSub1 *>( this ) );
			return true;
		case cSub1::kIID:
			(*ppvObj) = static_cast< cSub1 *>( this );
			return true;
		case cSub2::kIID:
			(*ppvObj) = static_cast< cSub2 *>( this );
			return true;
		}
		return false;
	}
};



#endif // __cConcrete_H
