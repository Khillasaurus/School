//-----------------------------
// File:		packet.h
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __PACKET_H
#define __PACKET_H


class cPacket
{
public:
	cPacket();
	~cPacket();

	void SetDataSize(Uint32 size){mDataSize = size;}
	Uint32 GetDataSize(){return mDataSize - mWrittenSize;}
	//dangerous "changing of contents" method
	char* GetDataPtr(){return mDpata + mWrittenSize;}
	Uint32 GetTrueSize(){return mTrueSize}
	void UpdateWritten(Uint32 written){mWrittenSize += written};

protected:
	// the data
	char* mpData;
	// total length of: currently received data / data to send
	Uint32 mDataSize;
	// mpData alloc size
	Uint32 mTrueSize;
	// expected datasize on read
	Uint32 mExpectedSize;
	// bytes written so far
	Uint32 mWrittenSize;
};

#endif //__PACKET_H