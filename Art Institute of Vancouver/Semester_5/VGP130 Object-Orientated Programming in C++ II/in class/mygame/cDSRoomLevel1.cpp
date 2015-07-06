//====================================================================================================
//File:			cDSRoomLevel1.cpp
//Created:		2012/09/06
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//SGE
#include "Input/Input.h"
#include "Graphics/CFont.h"

//Daniel Schenker
#include "cDSRoomLevel1.h"
#include "cDSApp.h"
#include "cDSBoard.h"
#include "cDSPiece.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSRoomLevel1::cDSRoomLevel1(const char* bgTexture, const int puzzleInUse, const int rows, const int columns) : cDSRoom(bgTexture)
,	mPuzzleDefaultInitialized(false)
,	mPuzzleUserInitialized(false)
,	mPuzzleInUse(puzzleInUse)
,	mRows(rows)
,	mColumns(columns)
,	mpBitmapFull(NULL)
,	mpBoard(NULL)
,	mpButtonBack(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mpButtonScramble(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
{
	//Create Objects
	 //Tools
	mpBitmapFull = new cBitmap24bit;
	 //Buttons
	mpButtonBack = new cDSMenuButton((cDSApp::msScreenWidth * 0.9) - (168 / 2), (cDSApp::msScreenHeight * 0.9) - (64 / 2), 168, 64, "./Resources/Textures/Buttons/back_up.png", "./Resources/Textures/Buttons/back_hover.png", "./Resources/Textures/Buttons/back_down.png", "./Resources/Textures/Buttons/back_click.png", false, cDSApp::msDepthButton);
	NewBoard();

	if(!mpBoard->mPiecesInitialPosSet)
	{
		int bottomLeftX = -1;
		int bottomLeftY = -1;
		mpBoard->mkWidth = mpBitmapFull->GetWidth();
		mpBoard->mkHeight = mpBitmapFull->GetHeight();
		const int tileWidth = (mpBoard->mkWidth / mpBoard->mkTilesX);
		const int tileHeight = (mpBoard->mkHeight / mpBoard->mkTilesY);

		for(int j = 0; j < mpBoard->mkTilesY; ++j)
		{
			for(int i = 0; i < mpBoard->mkTilesX; ++i)
			{
				bottomLeftX = i * tileWidth;
				bottomLeftY = j * tileHeight;

				//if not at the bottom right corner where the empty space will be
				if(i != (mpBoard->mkTilesX - 1) || j != (mpBoard->mkTilesY - 1))
				{
					mpBoard->mpTiles[(j * mpBoard->mkTilesX) + i]->SetOrigin(mpBoard->mkPosX + bottomLeftX, mpBoard->mkPosY + bottomLeftY);
				}
				else if(i == (mpBoard->mkTilesX - 1) || j == (mpBoard->mkTilesY - 1))
				{
					//place mpEmptyTile
					mpBoard->mpEmptyTile->SetOrigin(mpBoard->mkPosX + bottomLeftX, mpBoard->mkPosY + bottomLeftY);
					mpBoard->mpEmptyTile->SetSize(mpBoard->mpTiles[0]->GetSize());
				}
			}
		}
		mpBoard->mPiecesInitialPosSet = true;
	}

	//Create Objects - con't
	//if the puzzle pieces have not yet been scrambled
	if(!mpBoard->mPiecesPosScrambled)
	{
		//if the scramble button does NOT exist
		if(!mpButtonScramble)
		{
			mpButtonScramble = new cDSMenuButton(mpBoard->mkPosX + (mpBoard->mkWidth / 2) - (168 / 2), mpBoard->mkPosY + mpBoard->mkHeight + (64 / 2), 168, 64, "./Resources/Textures/Buttons/scramble_up.png", "./Resources/Textures/Buttons/scramble_hover.png", "./Resources/Textures/Buttons/scramble_down.png", "./Resources/Textures/Buttons/scramble_click.png", false, cDSApp::msDepthButton);
		}
	}

	//Graphics
	 //Congratulations
	mCongratulationsTexture.Load("./Resources/Textures/Graphics/roomScoreScreenCongratulations_v3.png");
	mCongratulationsSprite.AddTexture(&mCongratulationsTexture);
	mCongratulationsSprite.SetDepth(cDSApp::msDepthButton);

	//Fonts
	mFontStats.Create(FontType::IMPACT, 64);
	mFontStats.SetColor(142, 255, 117);

	//Initialize Positions
	 //Congratulations
	mCongratulationsSprite.SetPosition((cDSApp::msScreenWidth - 700) / 2, mpBoard->mkPosY - 150);
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSRoomLevel1::~cDSRoomLevel1()
{
	//Objects
	 //Tools
	if(mpBitmapFull)
	{
		delete mpBitmapFull;
		mpBitmapFull = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	 //Board
	if(mpBoard)
	{
		delete mpBoard;
		mpBoard = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	 //Buttons
	  //Back
	if(mpButtonBack)
	{
		delete mpButtonBack;
		mpButtonBack = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Scramble
	if(mpButtonScramble)
	{
		delete mpButtonScramble;
		mpButtonScramble = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}

	//Fonts
	mFontStats.Destroy();
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

void cDSRoomLevel1::RunPhysics()
{
	//Objects
	 //Buttons
	  //Back
	if(mpButtonBack)
	{
		mpButtonBack->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	}
	  //Scramble
	//if the button exists
	if(mpButtonScramble)
	{
		mpButtonScramble->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
		if(mpButtonScramble->GetButtonState() == kClick)
		{
			//scramble the board n times, where n is proportional to the size of the board
			mpBoard->ScramblePieces(mpBoard->mkTilesX * mpBoard->mkTilesY * 10);
		}
	}

	 //Board
	  //Pieces
	//Scramble pieces logic
	//if the puzzle has not been scrambled yet, do NOT allow the player to move pieces
	if(mpBoard->GetPiecesPosScrambled())
	{
		if(!mpBoard->mSolved)
		{
			for(int i = 0; i < mpBoard->mkTilesTotal; ++i)
			{
				mpBoard->mpTiles[i]->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
				if(mpBoard->mpTiles[i]->GetButtonState() == kClick)
				{
					//if the scramble button hasn't already been destroyed
					if(mpButtonScramble)
					{
						//if a successful move is made, destroy the scramble button
						if(mpBoard->MovePiece(i))
						{
							delete mpButtonScramble;
							mpButtonScramble = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
						}
					}
					else
					{
						mpBoard->MovePiece(i);
					}
				}
			}
		}
	}
	//Check if all of the pieces are in order (puzzle solved)
	if(mpBoard->mPiecesPosScrambled)
	{
		if(!mpBoard->mSolved)
		{
			if(mpBoard->IsSolved())
			{
				mpBoard->mSolved = true;
				//Change the background
				mBgTexture.Unload();
				mBgTexture.Load("./Resources/Textures/Backgrounds/bgScoreScreen.jpg");
				mBgSprite.ClearTextures();
				mBgSprite.AddTexture(&mBgTexture);

				//Update fonts
				sprintf_s(mStatsBuff, "It took you %d moves to solve a %d by %d puzzle!", mpBoard->mMoveCounter, mpBoard->mkTilesX, mpBoard->mkTilesY);
			}
		}
	}

	#ifdef DSDEBUGMODE
		//Score
		///pApp->mDefaultFont.SetColor(225, 155, 44);
		///sprintf_s(scoreTextBuff, "Score: %d", pApp->mScore);
	#endif //DSDEBUGMODE
}

//----------------------------------------------------------------------------------------------------

int cDSRoomLevel1::CheckRoomChange()
{
	if(mpButtonBack->GetButtonState() == kClick)
	{
		return Room::kRoomMainMenu;
	}
	else
	{
		return -1;
	}
}

//----------------------------------------------------------------------------------------------------

void cDSRoomLevel1::Render()
{
	//Background
	cDSRoom::Render();

	//Objects
	 //Buttons
	  //Back
	if(mpButtonBack)
	{
		mpButtonBack->Render();
	}
	  //Scramble
	if(mpButtonScramble)
	{
		mpButtonScramble->Render();
	}
	 //Board
	  //Pieces
	for(int i = 0; i < mpBoard->mkTilesTotal; ++i)
	{
		mpBoard->mpTiles[i]->Render();
	}
	//Graphics
	 //congratulations
	if(mpBoard->mSolved)
	{
		mCongratulationsSprite.Render();
		//Fonts
		mFontStats.PrintText(mStatsBuff, cDSApp::msScreenWidth * 0.15, mpBoard->mkPosY + mpBoard->mkHeight + 32);
	}

	#ifdef DSDEBUGMODE
		//Draw the score to the screen
		///pApp->mDefaultFont.PrintText(scoreTextBuff, 0, 96);
	#endif //DSDEBUGMODE
}

//----------------------------------------------------------------------------------------------------

void cDSRoomLevel1::NewBoard()
{
	//Board
	//if a board exists
	if(mpBoard)
	{
		//delete the old board
		delete mpBoard;
		mpBoard = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	 //Create the new board
	//if using the default puzzle
	if(mPuzzleInUse == 0)
	{
		mpBitmapFull->InputInfoHeader("./Resources/Textures/Objects/puzzledefault.bmp");
	}
	//if using the user puzzle
	else if(mPuzzleInUse == 1)
	{
		mpBitmapFull->InputInfoHeader("../../puzzle.bmp");
	}
	mpBoard = new cDSBoard((cDSApp::msScreenWidth / 2) - (0.5 * mpBitmapFull->GetWidth()), (cDSApp::msScreenHeight / 2) - (0.5 * mpBitmapFull->GetHeight()), mpBitmapFull->GetWidth(), mpBitmapFull->GetHeight(), mColumns, mRows);
	
	//if using the default puzzle
	if(mPuzzleInUse == 0)
	{
		//if the default puzzle pieces have been created in memory
		if(!mPuzzleDefaultInitialized)
		{
			//if(CreatePuzzlePieces("puzzledefault", "puzzledefault", 0))
			if(CreatePuzzlePieces("puzzledefault"))
			{
				mPuzzleDefaultInitialized = true;
			}
			else
			{
				///sprintf_s(pApp->mDebugBuff, "ERROR: Could not initialize default selection as puzzle background. - void cDSApp::OnMainLoop(void)\n");
				///OutputDebugStringA(pApp->mDebugBuff);
				mPuzzleDefaultInitialized = false;
			}
		}
	}
	//if using the user puzzle
	else if(mPuzzleInUse == 1)
	{
		//if the user puzzle pieces have been created in memory
		if(!mPuzzleUserInitialized)
		{
			if(CreatePuzzlePieces("puzzle", "puzzleuser", 2))
			{
				mPuzzleUserInitialized = true;
			}
			else
			{
				///sprintf_s(pApp->mDebugBuff, "ERROR: Could not initialize default selection as puzzle background. - void cDSApp::OnMainLoop(void)\n");
				///OutputDebugStringA(pApp->mDebugBuff);
				mPuzzleUserInitialized = false;
			}
		}
	}
	mpBoard->mkWidth = mpBitmapFull->GetWidth();
	mpBoard->mkHeight = mpBitmapFull->GetHeight();

	//Pieces
	for(int i = 0; i < mpBoard->mkTilesTotal; ++i)
	{
		mpBoard->mpTiles[i]->SetWidth(mpBoard->mkWidth / mpBoard->mkTilesX);
		mpBoard->mpTiles[i]->SetHeight(mpBoard->mkHeight / mpBoard->mkTilesY);
	}
	
	//Empty Placeholders
	mpBoard->mpEmptyTile->SetWidth(mpBoard->mkWidth / mpBoard->mkTilesX);//or set equal to the first piece in the puzzle
	mpBoard->mpEmptyTile->SetHeight(mpBoard->mkHeight / mpBoard->mkTilesY);
	mpBoard->mpEmptyTile->SetOrigin( (mpBoard->mkPosX + ((mpBoard->mkTilesX - 1) * mpBoard->mpEmptyTile->GetWidth())), (mpBoard->mkPosY + ((mpBoard->mkTilesY - 1) * mpBoard->mpEmptyTile->GetHeight())) );

	//if using the default puzzle
	if(mPuzzleInUse == 0)
	{
		//if the default puzzle pieces have been created in memory
		if(mPuzzleDefaultInitialized)
		{
			//change puzzle tile set
			mpBoard->OverwriteTileTextures("./puzzledefault");
			mpBoard->UpdateTextures();
			mpBoard->mPiecesInitialPosSet = false;
		}
		else
		{
			///sprintf_s(pApp->mDebugBuff, "ERROR: Default puzzle NOT initialized. - void cDSApp::OnMainLoop(void)\n");
			///OutputDebugStringA(pApp->mDebugBuff);
		}
	}
	//if using the user puzzle
	else if(mPuzzleInUse == 1)
	{
		//if the default puzzle pieces have been created in memory
		if(mPuzzleUserInitialized)
		{
			//change puzzle tile set
			mpBoard->OverwriteTileTextures("./puzzleuser");
			mpBoard->UpdateTextures();
			mpBoard->mPiecesInitialPosSet = false;
		}
		else
		{
			///sprintf_s(pApp->mDebugBuff, "ERROR: Default puzzle NOT initialized. - void cDSApp::OnMainLoop(void)\n");
			///OutputDebugStringA(pApp->mDebugBuff);
		}
	}
}

//----------------------------------------------------------------------------------------------------

//bitmapName does not include the file path or the extension
//directory:
	//0: ./Resources/Textures/Objects/
	//1: ./
	//2: ../../
//bool cDSRoomLevel1::CreatePuzzlePieces(const char* bitmapName, const char* outputBaseName, const int directory)
bool cDSRoomLevel1::CreatePuzzlePieces(const char* bitmapName, const char* outputBaseName, const int directory)
{
	if(!outputBaseName)
	{
		outputBaseName = bitmapName;
	}
	#ifdef DSDEBUGMODE
		//open the debuglog in append mode
		FILE* fpDebugLog = fopen("./debuglog.txt", "a");
		//allocate buffer for writing data to the debuglog
		char debugTextBuff[256];
		//allocate buffer for converting numbers to char
		char debugNumBuff[16];
		//write function name to debuglog
		strcpy(debugTextBuff, "bool cDSApp::CreatePuzzlePieces(const char* bitmapName, const int directory = 0)\n");
		fwrite(&debugTextBuff, strlen(debugTextBuff), 1, fpDebugLog);
	#endif //DSDEBUGMODE

	//create buffer to store the file path and file name in
	char fileName[256];

	//chose file path to strcpy to fileName buffer
	if(directory == 0)
	{
		strcpy(fileName, "./Resources/Textures/Objects/");
	}
	else if(directory == 1)
	{
		strcpy(fileName, "./");
	}
	else if(directory == 2)
	{
		strcpy(fileName, "../../");
	}
	#ifdef DSDEBUGMODE
		strcpy(debugTextBuff, "directory: ");
		strcpy(debugNumBuff, "");
		itoa(directory, debugNumBuff, 10);
		strcat(debugTextBuff, debugNumBuff);
		strcat(debugTextBuff, "\n");
		fwrite(&debugTextBuff, strlen(debugTextBuff), 1, fpDebugLog);
	#endif //DSDEBUGMODE
	//strcat bitmap name to fileName buffer
	strcat(fileName, bitmapName);
	//strcat file extension to fileName buffer
	strcat(fileName, ".bmp");
	#ifdef DSDEBUGMODE
		strcpy(debugTextBuff, "fileName: ");
		strcat(debugTextBuff, fileName);
		strcat(debugTextBuff, "\n");
		fwrite(&debugTextBuff, strlen(debugTextBuff), 1, fpDebugLog);
	#endif //DSDEBUGMODE
	//if the file was opened succesfully
	if(mpBitmapFull->Input(fileName))
	{
		//mpBitmapFull->PrintVirtual();
		//pieceBaseName does not include the file path or the file extension
		char pieceBaseName[256];
		strcpy(pieceBaseName, outputBaseName);
		#ifdef DSDEBUGMODE
			strcpy(debugTextBuff, "pieceBaseName: ");
			strcat(debugTextBuff, pieceBaseName);
			strcat(debugTextBuff, "\n");
			fwrite(&debugTextBuff, strlen(debugTextBuff), 1, fpDebugLog);
		#endif //DSDEBUGMODE
		//pieceFullName is the name of the new bitmap that will be created as a piece of the puzzle
		char pieceFullName[256];
		//numBuff is a buffer used to temporarily store int variables converted to char
		char numBuff[16];

		int bottomLeftX = -1;
		int bottomLeftY = -1;
		mpBoard->mkWidth = mpBitmapFull->GetWidth();
		mpBoard->mkHeight = mpBitmapFull->GetHeight();
		const int tileWidth = (mpBoard->mkWidth / mpBoard->mkTilesX);
		const int tileHeight = (mpBoard->mkHeight / mpBoard->mkTilesY);
		
		for(int j = 0; j < mpBoard->mkTilesY; ++j)
		{
			for(int i = 0; i < mpBoard->mkTilesX; ++i)
			{
				//Store pieces of original bitmap reading left to right, starting from top left and ending with an empty place bottom right
				 //Set file name of piece to be created. Example: "puzzledefault3x3_0.bmp"
				  //Puzzle type
				strcpy(pieceFullName, pieceBaseName);
				  //Horizontal
				strcpy(numBuff, "");
				itoa(mpBoard->mkTilesX, numBuff, 10);
				strcat(pieceFullName, numBuff);
				  //x
				strcat(pieceFullName, "x");
				  //Vertical
				strcpy(numBuff, "");
				itoa(mpBoard->mkTilesY, numBuff, 10);
				strcat(pieceFullName, numBuff);
				  //_
				strcat(pieceFullName, "_");
				  //Piece number
				strcpy(numBuff, "");
				itoa((j * mpBoard->mkTilesX) + i, numBuff, 10);
				strcat(pieceFullName, numBuff);
				  //File Extension
				strcat(pieceFullName, ".bmp");

				//Create piece
				//if not at the bottom right corner where the empty space will be
				if(i != (mpBoard->mkTilesX - 1) || j != (mpBoard->mkTilesY - 1))
				{
					bottomLeftX = i * tileWidth;
					bottomLeftY = (mpBoard->mkTilesY * tileHeight) - ((j + 1) * tileHeight);
					if( !mpBitmapFull->OutputPartial(
						pieceFullName,
						bottomLeftX,
						bottomLeftY,
						bottomLeftX + tileWidth - 1,
						bottomLeftY + tileHeight - 1) )
					{
						///sprintf_s(mDebugBuff, "ERROR: Failure creating puzzle piece %d - bool cDSApp::CreatePuzzlePieces(const char* bitmapName, const int directory = 0)\n", (j * mpBoard->mkTilesX) + i);
						///OutputDebugStringA(mDebugBuff);
					}
					#ifdef DSDEBUGMODE
						strcpy(debugTextBuff, "Name of outputted puzzle piece: ");
						strcat(debugTextBuff, pieceFullName);
						strcat(debugTextBuff, "\n");
						fwrite(&debugTextBuff, strlen(debugTextBuff), 1, fpDebugLog);
					#endif //DSDEBUGMODE
				}
			}
		}

		return true;
	}
	else
	{
		//sprintf_s(mDebugBuff, "ERROR: Could not input bitmap %s in order to create puzzle pieces. - bool cDSApp::CreatePuzzlePieces(const char* bitmapName, const int directory = 0)\n", fileName);
		//OutputDebugStringA(mDebugBuff);

		return false;
	}
}