//
// File: packet.cpp
// Date: 2012/05/14
// Copyright 2012 Me
//

#include "stdafx.h"
#include "net/packet.h"

cPacket::cPacket()
:	mpData(NULL)
,	mDataSize(0)
,	mTrueSize(0)
,	mExpectedSize(0)
,	mWrittenSize(0)
{
	resize(1024);
}

bool cPacket::resize(Uint32 sz)
{
    if( (mTrueSize - mDataSize) <= sz)
    {
		const Uint32 kDataPaddingSize = 128;

        Uint32 newsize = ((mDataSize + sz) + (kDataPaddingSize - 1)) & ~(kDataPaddingSize - 1);

		char *oldbuf = mpData;
        char *newbuf = new char[ newsize ];
        if( newbuf )
        {
            mpData = newbuf;
            memset(mpData, 0, newsize);

            if( oldbuf )
            {
                memcpy(mpData, oldbuf, mDataSize);
                delete[] oldbuf;
            }

            mTrueSize = newsize;
            return true;
        }
    }
	return false;
}
