#ifndef INCLUDED_ENGINE_HEIGHTMAP_H
#define INCLUDED_ENGINE_HEIGHTMAP_H

//====================================================================================================
// Filename:	Heightmap.h
// Created by:	Peter Chan
// Description:	Class for storing a 2D array of normalized [0, 1] height values.
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

class Heightmap
{
public:
	Heightmap();
	~Heightmap();

	void GenerateFromRAW(const char* pFilename, u32 columns, u32 rows);
	void Purge();

	f32 GetHeight(u32 x, u32 y) const;
	
	u32 GetColumns() const					{ return mColumns; }
	u32 GetRows() const						{ return mRows; }

private:
	NONCOPYABLE(Heightmap);

	f32* mpHeightValues;
	u32 mColumns;
	u32 mRows;
};

#endif // #ifndef INCLUDED_ENGINE_HEIGHTMAP_H
