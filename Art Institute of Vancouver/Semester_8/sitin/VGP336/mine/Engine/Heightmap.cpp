//====================================================================================================
// Filename:	Heightmap.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Heightmap.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Heightmap::Heightmap()
	: mpHeightValues(nullptr)
	, mColumns(0)
	, mRows(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Heightmap::~Heightmap()
{
	ASSERT(mpHeightValues == nullptr, "[Heightmap] Height values not freed.");
}

//----------------------------------------------------------------------------------------------------

void Heightmap::GenerateFromRAW(const char* pFilename, u32 columns, u32 rows)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pFilename, "rb");
	ASSERT(pFile != nullptr, "[Heightmap] Failed to load heightmap %s.", pFilename);
	
	fseek(pFile, 0, SEEK_END);
	u32 len = (u32)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	ASSERT(len == columns * rows, "[Heightmap] Invalid heightmap dimension. Expected %ux%u = %u bytes.", columns, rows, columns * rows);

	// Allocate memory for height data
	mpHeightValues = new f32[columns * rows];
	mColumns = columns;
	mRows = rows;

	for (u32 y = 0; y < rows; ++y)
	{
		for (u32 x = 0; x < columns; ++x)
		{
			const u32 index = x + (columns * y);
			mpHeightValues[index] = fgetc(pFile) / 255.0f;
		}
	}

	fclose(pFile);
}

//----------------------------------------------------------------------------------------------------

void Heightmap::Purge()
{
	SafeDeleteArray(mpHeightValues);
	mColumns = 0;
	mRows = 0;
}

//----------------------------------------------------------------------------------------------------

f32 Heightmap::GetHeight(u32 x, u32 y) const
{
	ASSERT(mpHeightValues != nullptr, "[Heightmap] Failed to get height value. Height map is empty.");
	ASSERT(x < mColumns && y < mRows, "[Heightmap] Failed to get height value. Invalid coordiante (%u, %u).", x, y);
	return mpHeightValues[x + (mColumns * y)];
}