//
// File: ailog.h 
// Date: 2012/04/02
// Copyright 2012 Me
//

#ifndef __AILOG_H
#define __AILOG_H

#include "core/aithread.h"
#include "core/aimutex.h"
#include "core/aisemaphore.h"


namespace AIDebug
{
	class cAILogger : public cAIThread
	{
	public:
		static cAILogger *GetInstance();
		static cAILogger *spAILogger;

	public: // cAILogger
		cAILogger();
		void Log(const char *pFormat, ... );

	protected: // member funcs
		void DoWork();

	public: // cAIThread
		virtual Uint32 Run();


	protected: // member vars
		//
		std::queue< std::string > mLogQueue;

		// thread safety
		cAIMutex mLogMutex;
		cAISemaphore mLogSemaphore;

	};
}

#define AILog				AIDebug::cAILogger::GetInstance()->Log



#endif
