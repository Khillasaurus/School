// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//c:\afile.txt			== FILE			persistent resource
//c:\afile.jpg			== FILE			persistent resource
//hello world				== record
//image data				== record
//drive					== data source
//database				== data source
//network/ftp/http		== data source
//recently accessed		== caches
//in use instance			== caches
//resource/asset manager	== 
//
//texttileobjectInstance	<= hello world record 
//texture					<= image data
//bitmap					<= image data
//
//
//		cIObject
//			|
//		cISerializable		Read(stream) write(stream)
//			|
//		____|________
//		|			|
//	cIIStream	cIOStream
//		|			|
//	    |___________|
//			|
//		  cRecord

//class cBase
//{
//public:
//	bool mIsTrue;
//};
//
//class cSub1 : public cBase
//public:
//{
//};
//class cSub2 : public cBase
//{
//public:
//};
//
//class cConcrete : public cSub1, public cSub2
//{
//public:
//};


//	cIObject		cIObject
//		|			|
//	cISerializable	cISerializable
//bool isBigEndian;		bool isBigEndian;
//		|			|
//		|			|
//		|			|
//	cIIStream	cIOStream
//		|			|
//	cIStream	cOStream
//		|			|
//	    |___________|
//			|
//		  cRecord



//		  cRecord *pRec;
//  cIStream *pIStream = static_cast< cIStream * > pRec;
//  cIIStream *pIIStream = static_cast< cIIStream * > pRec;
//  cISerializable *pISerial = static_cast< cISerializable * >( static_cast< cIStream * >( pRec ) );
//
//
//LoadStuff( cIObject *pObj )
//{
//	FILE *pFile = fopen("afile.txt", "r" );
//
//	cIIStream *pIStream;
//	if( pObj->QueryInterface( cIIStream::kInterfaceID, pIStream) )
//	{
//		// do i specific stuff
//	}
//}
//
//DoSimObject( cIObject *pObj )
//{
//	//if the object is a command object... do command stuff
//	// if the object is a physical obj...do unit stuff
//}
//


#include "concrete.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cConcrete *pObj = new cConcrete();

	cSub1 *pObj;
	if( CreateObj( cConcrete::kClassId, cSub1::kIID, (void**)&pObj ) )
	{
		// yay
	}

	std::cout<< "v1=" << ((cSub1*)pObj)->Get() << std::endl;
	((cSub1*)pObj)->mIsTrue = true;
	std::cout<< "v1=" << ((cSub1*)pObj)->Get() << std::endl;
	std::cout<< "v2=" << ((cSub2*)pObj)->mIsTrue << std::endl;

	// http://thedocs.com/13435asdf
	//tAutoPtr<cSub1> pSub1;
	cSub1 *pSub1;
	//if( pObj->QI( cSub1::kIID, pSub1.AsPPV() ) )
	if( pObj->QI( cSub1::kIID, (void**)&pSub1 ) )
	{
		pSub1->Test();

		cSub2 *pSub2;
		if( pSub1->QI( cSub2::kIID, (void**)&pSub2 ) )
		{
			pSub2->Test();
		}
	}


	//std::cout<< "-------"<< std::endl;

	//std::cout<< "sub1"<< std::endl;
	//cSub1 *pSub1 = static_cast<cSub1 *>(pObj);
	//std::cout<< "v=" << pSub1->mIsTrue << std::endl;
	//pSub1->Test();

	//std::cout<< "sub2"<< std::endl;
	//cSub2 *pSub2 = static_cast<cSub2 *>(pObj);
	//std::cout<< "v=" << pSub2->mIsTrue << std::endl;
	//pSub2->Test();

	//std::cout<< "sub2 -> base2"<< std::endl;
	//cBase *pBase2 = static_cast<cBase *>(pSub2);
	//std::cout<< "v=" << pBase2->mIsTrue << std::endl;
	//pBase2->Test();

	//std::cout<< "base2 -> sub1"<< std::endl;
	//cSub1 *pBase2_Sub1 = static_cast<cSub1 *>(pBase2);
	//std::cout<< "v=" << pBase2_Sub1->mIsTrue << std::endl;
	//pBase2_Sub1->Test();

	delete pObj;
	return 0;
}
