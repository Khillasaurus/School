//=================================================================================================
// Filename:	Frontend.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Frontend.h"
#include "GameStates.h"
#include "SubStates.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Frontend::Frontend(GameContext& gc)
: BaseState(gc)
, mSubState(SubState::kMainMenu)
, mpMainMenu(NULL)
, mpStart(NULL)
, mpNewGame(NULL)
, mpLoadGame(NULL)
, mpSettings(NULL)
, mpGameplay(NULL)
, mpKeybindings(NULL)
, mpAudio(NULL)
, mpVideo(NULL)
, mpStatistics(NULL)
{
	// All

	// SubStates
	mpMainMenu = new MainMenu(gc);
	mpStart = new Start(gc);
	mpNewGame = new NewGame(gc);
	mpLoadGame = new LoadGame(gc);
	mpSettings = new Settings(gc);
	mpGameplay = new Gameplay(gc);
	mpKeybindings = new Keybindings(gc);
	mpAudio = new Audio(gc);
	mpVideo = new Video(gc);
	mpStatistics = new Statistics(gc);
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Frontend::~Frontend()
{
}

//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Frontend::Load()
{
	// All
	 //Cursor
	mCursor.Load("PeterChan/sword.png");

	// SubStates
	mpMainMenu->Load();
	mpStart->Load();
	mpNewGame->Load();
	mpLoadGame->Load();
	mpSettings->Load();
	mpGameplay->Load();
	mpKeybindings->Load();
	mpAudio->Load();
	mpVideo->Load();
	mpStatistics->Load();

}

//-------------------------------------------------------------------------------------------------

void Frontend::Unload()
{
	// Reset values
	mSubState = SubState::kMainMenu;

	// All
	 //Cursor
	mCursor.Unload();

	// SubStates
	mpMainMenu->Unload();
	mpStart->Unload();
	mpNewGame->Unload();
	mpLoadGame->Unload();
	mpSettings->Unload();
	mpGameplay->Unload();
	mpKeybindings->Unload();
	mpAudio->Unload();
	mpVideo->Unload();
	mpStatistics->Unload();
}

//-------------------------------------------------------------------------------------------------

int Frontend::Update(float deltaTime)
{
	// All
	 //Cursor
	mCursor.Update(deltaTime);

	// Main Menu
	if(mSubState == SubState::kMainMenu)
	{
		mSubState = static_cast<SubState::eSubState>(mpMainMenu->Update(deltaTime));
	}
	 // Start
	else if(mSubState == SubState::kStart)
	{
		mSubState = static_cast<SubState::eSubState>(mpStart->Update(deltaTime));
	}
	  // New Game
	else if(mSubState == SubState::kNewGame)
	{
		mSubState = static_cast<SubState::eSubState>(mpNewGame->Update(deltaTime));
	}
	  // Load Game
	else if(mSubState == SubState::kLoadGame)
	{
		mSubState = static_cast<SubState::eSubState>(mpLoadGame->Update(deltaTime));
	}
	 // Settings
	else if(mSubState == SubState::kSettings)
	{
		mSubState = static_cast<SubState::eSubState>(mpSettings->Update(deltaTime));
	}
	  // Gameplay
	else if(mSubState == SubState::kGameplay)
	{
		mSubState = static_cast<SubState::eSubState>(mpGameplay->Update(deltaTime));
	}
	   // Keybindings
	else if(mSubState == SubState::kKeybindings)
	{
		mSubState = static_cast<SubState::eSubState>(mpKeybindings->Update(deltaTime));
	}
	  // Audio
	else if(mSubState == SubState::kAudio)
	{
		mSubState = static_cast<SubState::eSubState>(mpAudio->Update(deltaTime));
	}
	  // Video
	else if(mSubState == SubState::kVideo)
	{
		mSubState = static_cast<SubState::eSubState>(mpVideo->Update(deltaTime));
	}
	 // Statistics
	else if(mSubState == SubState::kStatistics)
	{
		mSubState = static_cast<SubState::eSubState>(mpStatistics->Update(deltaTime));
	}

	// Check if we need to change state
	GameState::Type nextState = GameState::Invalid;
	//if(/*LoadGame or NewGameSettings returns Game*/)
	if(mSubState == SubState::kGame)
	{
		nextState = GameState::Game;
	}
	 // Quit
	else if(mSubState == SubState::kQuit)
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

//-------------------------------------------------------------------------------------------------

void Frontend::Render()
{
	// Main Menu
	if(mSubState == SubState::kMainMenu)
	{
		mpMainMenu->Render();
	}
	 // Start
	else if(mSubState == SubState::kStart)
	{
		mpStart->Render();
	}
	  // New Game
	else if(mSubState == SubState::kNewGame)
	{
		mpNewGame->Render();
	}
	  // Load Game
	else if(mSubState == SubState::kLoadGame)
	{
		mpLoadGame->Render();
	}
	 // Settings
	else if(mSubState == SubState::kSettings)
	{
		mpSettings->Render();
	}
	  // Gameplay
	else if(mSubState == SubState::kGameplay)
	{
		mpGameplay->Render();
	}
	   // Keybindings
	else if(mSubState == SubState::kKeybindings)
	{
		mpKeybindings->Render();
	}
	  // Audio
	else if(mSubState == SubState::kAudio)
	{
		mpAudio->Render();
	}
	  // Video
	else if(mSubState == SubState::kVideo)
	{
		mpVideo->Render();
	}
	 // Statistics
	else if(mSubState == SubState::kStatistics)
	{
		mpStatistics->Render();
	}

	// All
	 //Cursor
	mCursor.Render();
}