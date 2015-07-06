//
// File: packet.h 
// Date: 2012/05/07
// Copyright 2012 Me
//

#ifndef __PACKET_H
#define __PACKET_H

class cPacket
{
public:
	cPacket();
	bool resize(Uint32 sz);
	void SetDataSize(Uint32 size){ mDataSize = size; }
	Uint32 GetDataSize(){ return mDataSize - mWrittenSize; }
	// dangerous "changing of contents" method
	char *GetDataPtr(){ return mpData + mWrittenSize; }
	Uint32 GetTrueSize(){ return mTrueSize; }
	void UpdateWritten(Uint32 written){ mWrittenSize += written; }

//protected:
public:
	// the data
	char *mpData;
	// total length of: currently received data / data to send
	Uint32 mDataSize;
	// mpData alloc size
	Uint32 mTrueSize;
	// expected datasize on read
	Uint32 mExpectedSize;
	// bytes written so far
	Uint32 mWrittenSize;
};

#endif


