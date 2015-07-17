// file:	tautoptr.h
// created:	2012/01/20
// Copyright 2012 by Me

#ifndef __tAutoPtr_H
#define __tAutoPtr_H

// example:
//	cObject *pObj = new cObject;
//  delete pObj;

//  tAutoPtr<cObject> pObj = new cObject;
//  pObj = NULL;

// {
//		cObject obj;
// }
// at this point, obj has been destroyed

template <class T>
class tAutoPtr
{
public: // tAutoPtr

	// tAutoPtr <cTest> pTest(new cTest);
   tAutoPtr(T* pObj = NULL)
   :	mpObj(pObj)
   {
      if(mpObj)
      {
         mpObj->AddRef();
      }
   }

   // tAutoPtr<cTest> pTest1;
   // tAutoPtr<cTest> pTest2(pTest1);
   tAutoPtr(const tAutoPtr<T>& _T)
       :	mpObj(_T.mpObj)
   {
      if(mpObj)
      {
         mpObj->AddRef();
      }
   }

   // destructor is NOT virtual
   ~tAutoPtr()
   {
      if(mpObj)
      {
         mpObj->Release();
      }
   }

	// assignment operator
   const tAutoPtr& operator=( T *pObj )
   {
      if(pObj != mpObj)
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

   // tAutoPtr<cTest> pTest1;
   // tAutoPtr<cTest> pTest2 = pTest1;
   const tAutoPtr& operator =(const tAutoPtr& rhs)
   {
      if(&rhs != this)
      {
         operator =(rhs.mpObj);
      }
      return (*this);
   }

   // tAutoPtr<cTest> pTest = new cTest;
   // cTest &t = *pTest;
   T& operator  *() const { return (*mpObj); }

   // tAutoPtr<cTest> pTest = new cTest;
   // pTest->func();
   T *operator ->() const { return (mpObj);  }

   // casting operator
   // tAutoPtr<cTest> pAutoTest = new cTest;
   // cTest *pTest = pAutoTest;
   // cTest *pTest = pAutoTest.mpObj;
   //tAutoPtr<cTest> pTest = new cTest;
   // function (pTest);
   // function (cTest *pTest);
   operator T*() const { return mpObj; }

   // 
   void** AsPPV()	{return (void**)&mpObj;	}
   // used for filling in mpObj by a factory function


   // int x;
   // variable with address
   // &x
   // int *p;  a variable which holds an address ...
   // int **p;  a variable which holds an address to a pointer ... 
   T** AsPPObj()
   {
      if(mpObj)
      {
         mpObj->Release();
      }
      mpObj = NULL;
      return (T**)AsPPV();
   }


public:
	T *mpObj;
};



#endif // __tAutoPtr_H
