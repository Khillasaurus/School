//
// File: connectiontcp.h 
// Date: 2012/05/07
// Copyright 2012 Me
//

#ifndef __CONNECTIONTCP_H
#define __CONNECTIONTCP_H

// fwd decls
class cConnectionPool;
class cPacket;

// --------------------------

class cConnectionTCP
{
public:
	enum eType
	{
		kClient,
		kServer
	};
public:
	cConnectionTCP();
	~cConnectionTCP();

	// server methods
	bool Bind();
	bool Accept();

	// general
	Sint32 Read(cPacket *pPkt);
	Sint32 Write();

	// outbound 
	void AddPendingPkt(cPacket *pPkt);

	// all done
	void Close();


public:
	Uint32 mType;
	Uint32 mSocket;
	cConnectionPool *mpPool;
	Uint32 mIpAddr; // bigendian
	Uint16 mPort;

	bool mHasOutput;
	cPacket *mpCurrentWritePkt;
	queue<cPacket *> mWriteQueue;
};

#endif
