//-----------------------------
// File:		connectiontcp.h
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

#ifndef __CONNECTIONTCP_H
#define __CONNECTIONTCP_H

//fwd decls
class cConnectionPool;
class cPacket;

class cConnectionTCP
{
public:
	enum eTypes
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

	// outboud
	void AddPendingPkt();
	void Close(Uint32)

public:
	Uint32 mType;
	Uint32 mSocket;
	cConnectionPool* mpPool;
	Uint32 mIpAddr;// bigendian

	cPacket* mpCurrentWritePkt;
	queue<cPacket*> mWriteQueue;
};

#endif //__CONNECTIONTCP_H