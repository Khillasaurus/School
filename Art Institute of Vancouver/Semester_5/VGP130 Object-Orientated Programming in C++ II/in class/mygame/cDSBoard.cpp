//====================================================================================================
//File:		cDSBoard.cpp
//Created:		2012/08/10
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

#include "stdafx.h"

#include <string.h>
#include <time.h>

//Daniel Schenker
#include "cDSBoard.h"
#include "cDSPiece.h"
#include "cDSApp.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSBoard::cDSBoard(const int posX, const int posY, const int width, const int height, const int tilesX, const int tilesY, int moveCounter)
:	mkPosX(posX)
,	mkPosY(posY)
,	mkWidth(width)
,	mkHeight(height)
,	mkTilesX(tilesX)
,	mkTilesY(tilesY)
,	mkTilesTotal((tilesX * tilesY) - 1)
,	mPiecesInitialPosSet(false)
,	mPiecesPosScrambled(false)
,	mSolved(false)
,	mMoveCounter(moveCounter)
{
	//initialize random seed
	srand( static_cast<unsigned int>(time(NULL)) );

	//Pieces
	for(int j = 0; j < mkTilesY; ++j)
	{
		for(int i = 0; i < mkTilesX; ++i)
		{
			//if not at the bottom right corner where the empty space will be
			if(i != (mkTilesX - 1) || j != (mkTilesY - 1))
			{
				mpTiles.push_back(new cDSPiece(i, j));
				mpTiles[(j * mkTilesX) + i]->SetDepth(cDSApp::msDepthButton);
			}
			else if(i == (mkTilesX - 1) || j == (mkTilesY - 1))
			{
				//Empty piece placeholders
				mpEmptyTile = new cDSPiece(i, j);
				mpEmptyTile->SetDepth(cDSApp::msDepthButton);
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSBoard::~cDSBoard()
{
	//Pieces
	mpTiles.clear();
	//Empty piece placeholders
	delete mpEmptyTile;
	mpEmptyTile = NULL;//mpEmptyTile = nullptr; is only avaible in VS2010 and newer
}

//----------------------------------------------------------------------------------------------------
//General Functions
//----------------------------------------------------------------------------------------------------

void cDSBoard::LoadTileTextures(const char* pFileBaseName)
{
	char fileToLoad[256];
	const char* pFileToLoad = &fileToLoad[0];
	
	//open the debuglog in append mode
	FILE* fpDebugLog = fopen("./debuglog.txt", "a");
	//allocate buffer for writing data to the debuglog
	char debugBuff[256];
	//allocate buffer for converting numbers to char
	char numBuff[16];
	//write function name to debuglog
	strcpy(debugBuff, "void cDSBoard::LoadTileTextures(const char* pFileBaseName)\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
	//write title for upcoming debug info in the debuglog
	strcpy(debugBuff, "==============\nLOAD TILE TEXTURES\n--------------\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);

	for(int i = 0; i < mkTilesTotal; ++i)
	{
		//set file name of texture to be loaded
		strcpy(fileToLoad, pFileBaseName);
		itoa(mkTilesX, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcpy(numBuff, "");
		strcat(fileToLoad, "x");
		itoa(mkTilesY, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcpy(numBuff, "");
		strcat(fileToLoad, "_");
		itoa(i, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcat(fileToLoad, ".bmp");

		//load texture
		mpTiles[i]->LoadTextures(pFileToLoad, pFileToLoad, pFileToLoad, pFileToLoad);

		//temp, should change to having its' own function
		mpTiles[i]->UpdateTexture();

		//write file name of loaded texture to log
		strcat(fileToLoad, "\n");
		fwrite(&fileToLoad, strlen(fileToLoad), 1, fpDebugLog);
	}

	//write new line into debug log
	strcpy(debugBuff, "\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
	//close debug log file pointer
	fclose(fpDebugLog);
}

//----------------------------------------------------------------------------------------------------

void cDSBoard::OverwriteTileTextures(const char* pFileBaseName)
{
	char fileToLoad[256];
	const char* pFileToLoad = &fileToLoad[0];
	
	//open the debuglog in append mode
	FILE* fpDebugLog = fopen("./debuglog.txt", "a");
	//allocate buffer for writing data to the debuglog
	char debugBuff[256];
	//allocate buffer for converting numbers to char
	char numBuff[16];
	//write function name to debuglog
	strcpy(debugBuff, "void cDSBoard::OverwriteTileTextures(const char* pFileBaseName)\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
	//write title for upcoming debug info in the debuglog
	strcpy(debugBuff, "==============\nOVERWRITE TILE TEXTURES\n--------------\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);

	for(int i = 0; i < mkTilesTotal; ++i)
	{
		//set file name of texture to be loaded
		strcpy(fileToLoad, pFileBaseName);
		itoa(mkTilesX, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcpy(numBuff, "");
		strcat(fileToLoad, "x");
		itoa(mkTilesY, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcpy(numBuff, "");
		strcat(fileToLoad, "_");
		itoa(i, numBuff, 10);
		strcat(fileToLoad, numBuff);
		strcat(fileToLoad, ".bmp");

		//overwrite texture
		mpTiles[i]->OverwriteTextures(pFileToLoad, pFileToLoad, pFileToLoad, pFileToLoad);

		//write file name of loaded texture to log
		strcat(fileToLoad, "\n");
		fwrite(&fileToLoad, strlen(fileToLoad), 1, fpDebugLog);
	}

	//write new line into debug log
	strcpy(debugBuff, "\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
	//close debug log file pointer
	fclose(fpDebugLog);
}

//----------------------------------------------------------------------------------------------------

void cDSBoard::UpdateTextures()
{
	//open the debuglog in append mode
	FILE* fpDebugLog = fopen("./debuglog.txt", "a");
	//allocate buffer for writing data to the debuglog
	char debugBuff[256];
	//allocate buffer for converting numbers to char
	char numBuff[16];
	//write function name to debuglog
	strcpy(debugBuff, "void cDSBoard::UpdateTextures()\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);

	for(int i = 0; i < mkTilesTotal; ++i)
	{
		mpTiles[i]->mSprite.ClearTextures();

		if(mpTiles[i]->GetButtonState() == ButtonState::kUp)
		{
			mpTiles[i]->mSprite.AddTexture(&mpTiles[i]->mUpTexture);

			//write to the debuglog
			strcpy(debugBuff, "mpTiles[");
			itoa(i, numBuff, 10);
			strcat(debugBuff, numBuff);
			strcat(debugBuff, "].mSprite.AddTexture(&mpTiles[");
			strcat(debugBuff, numBuff);
			strcat(debugBuff, "].mUpTexture);\n");
			fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
		}
		else if(mpTiles[i]->GetButtonState() == ButtonState::kHover)
		{
			mpTiles[i]->mSprite.AddTexture(&mpTiles[i]->mHoverTexture);
		}
		else if(mpTiles[i]->GetButtonState() == ButtonState::kDown)
		{
			mpTiles[i]->mSprite.AddTexture(&mpTiles[i]->mDownTexture);
		}
		else if(mpTiles[i]->GetButtonState() == ButtonState::kClick)
		{
			mpTiles[i]->mSprite.AddTexture(&mpTiles[i]->mClickTexture);
		}
	}

	//write new line into debug log
	strcpy(debugBuff, "\n");
	fwrite(&debugBuff, strlen(debugBuff), 1, fpDebugLog);
	//close debug log file pointer
	fclose(fpDebugLog);
}

//----------------------------------------------------------------------------------------------------

bool cDSBoard::MovePiece(const int pieceNum, bool increaseCounter)
{
	//When piece "pieceNum" is clicked (done outside of this function)
	//Determine if there is an adjacent space free
	bool adjacent = false;
	//if the empty space is on the left or right of mpTiles[pieceNum]
	if((mpTiles[pieceNum]->GetPiecePosX() - mpEmptyTile->GetPiecePosX()) == 1 || (mpTiles[pieceNum]->GetPiecePosX() - mpEmptyTile->GetPiecePosX()) == -1)
	{
		//if the empty space is equal to mpTiles[pieceNum] vertically
		if(mpTiles[pieceNum]->GetPiecePosY() == mpEmptyTile->GetPiecePosY())
		{
			adjacent = true;
		}
	}
	//else if the empty space is above or below of mpTiles[pieceNum]
	else if((mpTiles[pieceNum]->GetPiecePosY() - mpEmptyTile->GetPiecePosY()) == 1 || (mpTiles[pieceNum]->GetPiecePosY() - mpEmptyTile->GetPiecePosY()) == -1)
	{
		//if the empty space is equal to mpTiles[pieceNum] horizontally
		if(mpTiles[pieceNum]->GetPiecePosX() == mpEmptyTile->GetPiecePosX())
		{
			adjacent = true;
		}
	}

	//if the empty space is adjacent, move the piece into the free space
	if(adjacent)
	{
		//temp hold piece to remember values while swapping mpTiles[pieceNum] and mpEmptyTile
		//cDSPiece hold(mpTiles[pieceNum]);
		cDSPiece hold(mpTiles[pieceNum]->GetPieceCorrectX(), mpTiles[pieceNum]->GetPieceCorrectY(), mpTiles[pieceNum]->GetPiecePosX(), mpTiles[pieceNum]->GetPiecePosY());
		//Swap mpTiles[pieceNum] and mpEmptyTile (this includes setting their pos)
		//mpTiles[pieceNum] = mpEmptyTile;
		mpTiles[pieceNum]->SetPiecePos(mpEmptyTile->GetPiecePosX(), mpEmptyTile->GetPiecePosY());
		//mpEmptyTile = &hold;
		mpEmptyTile->SetPiecePos(hold.GetPiecePosX(), hold.GetPiecePosY());
		
		//set origin of piece
		mpTiles[pieceNum]->SetOrigin( (mkPosX + (mpTiles[pieceNum]->GetPiecePosX() * mpTiles[pieceNum]->GetWidth())), (mkPosY + (mpTiles[pieceNum]->GetPiecePosY() * mpTiles[pieceNum]->GetHeight())) );
		//set origin of empty tile
		mpEmptyTile->SetOrigin( (mkPosX + (mpEmptyTile->GetPiecePosX() * mpEmptyTile->GetWidth())), (mkPosY + (mpEmptyTile->GetPiecePosY() * mpEmptyTile->GetHeight())) );

		//Increase the move counter
		if(increaseCounter)
		{
			++mMoveCounter;
		}

		return true;
	}
	//else the empty space is not adjacent
	else
	{
		return false;
	}
}

//----------------------------------------------------------------------------------------------------

void cDSBoard::ScramblePieces(const int moves)
{
	bool foundPiece = false;
	int lastPieceNum = -1;
	int curPieceNum = -1;
	for(int i = 0; i < moves; ++i)
	{
		//try moving a pieces until we find a possible move
		do
		{
			//pick a random number that we didn't pick last time
			do
			{
				curPieceNum = rand() % mkTilesTotal;
			}while(curPieceNum == lastPieceNum);
			//swap piece "curPieceNum" with the empty space, but do NOT add to the move counter
			foundPiece = MovePiece(curPieceNum, false);
		}while(!foundPiece);
		//update last moved piece
		lastPieceNum = curPieceNum;

		foundPiece = false;
	}
	mPiecesPosScrambled = true;
}

//----------------------------------------------------------------------------------------------------

bool cDSBoard::IsSolved()
{
	//loop through every tile and check if it is in the correct place
	for(int i = 0; i < mkTilesTotal; ++i)
	{
		//if a piece is not in the correct position
		if((mpTiles[i]->GetPieceCorrectX() != mpTiles[i]->GetPiecePosX()) || (mpTiles[i]->GetPieceCorrectY() != mpTiles[i]->GetPiecePosY()))
		{
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

bool cDSBoard::GetPiecesPosScrambled() const
{
	return mPiecesPosScrambled;
}