/*
 * MD5.H - header file for MD5C.C
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

#ifndef _MD5_H
#define _MD5_H

/* MD5 context. */
struct MD5_CTX
{
  Uint32 digest[4];				/* state (ABCD) */
  Uint32 count[2];				/* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];				/* input buffer */
};


/* --------------------------------------------- *\
	class	: cMD5Hash
	Desc	: 
\* --------------------------------------------- */
class cMD5Hash
{
public:
	void MD5Init();
	void MD5Update( Uint8 *input, Uint32 inputLength);
	void MD5Final(Uint8 *pDigest);//(Uint8 digest[16]);
    //void MD5Final( cLGString &digest);

    cMD5Hash& operator<<(const char *message_array);

#ifdef DEBUG
    static void UnitTest();
#endif

protected:
	MD5_CTX mContext;
};

#endif

