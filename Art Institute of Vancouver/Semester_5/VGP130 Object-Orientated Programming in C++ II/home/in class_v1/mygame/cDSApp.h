//====================================================================================================
// File:		cDSApp.h
// Created:		2012/07/26
// Copyright:	Daniel Schenker
//====================================================================================================

#ifndef __CDSAPP_H
#define __CDSAPP_H

//====================================================================================================
// Includes
//====================================================================================================

#include "Core/CApplication.h"
#include "graphics/CFont.h"
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class cDSApp : public CApplication
{
protected:
	// 1. Game initalization
	virtual void OnInitialize(void);

	// 2. Main game loop
	virtual void OnMainLoop(void);
		// a. Front-end initialization
		void FrontEndInitialize();
		// b. Front-end loop
		void FrontEndLoop();
			// i. Gather input
			void FrontEndLoopInput();
			// ii. Render Screen
			void FrontEndLoopRender();
			// iii. Update front-end state
			void FrontEndLoopUpdateState();
			// iv. Trigger any state changes
			void FrontEndLoopTriggerState();
		// c. Front-end shutdown
		void FrontEndShutdown();
		// d. Level initialization
		void LevelInitialization();
		// e. Level game loop
		void LevelLoop();
			// i. Gather input
			void LevelLoopInput();
			// ii. Run AI
			void LevelLoopAI();
			// iii. Run physics simulations
			void LevelLoopPhysics();
			// iv. Update game entities
			void LevelLoopUpdateEntities();
			// v. Send/Receive network messages
			void LevelLoopNetwork();
			// vi. Update time step
			void LevelLoopUpdateTimestep();
			// vii. Update game state
			void LevelLoopUpdateState();
		// f. Level Shutdown
		void LevelShutdown();

	// 3. Game shutdown
	virtual void OnTerminate(void);

protected:
	CFont mFont;
	CSprite mTestSprite;
	CTexture mTestTexture;
};

#endif //__CDSAPP_H