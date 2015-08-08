#ifndef CLIPPER_H
#define CLIPPER_H

//=============================================================================
//Dependencies
//=============================================================================

#include "../Common/Vertex2.h"
#include <vector>

//=============================================================================
//Enumerations
//=============================================================================

enum ClipPlane
{
	CP_LEFT,
	CP_RIGHT,
	CP_BOTTOM,
	CP_TOP
};

//=============================================================================
//Class Declarations
//=============================================================================

class CClipper
{
	//Singleton Duplication Prevention
	//TOIMPROVE: These do not prevent duplication in ALL cases, but the vast majority of them, all of which should fall under the scope of this project. Exeption example: Multithreading may allow for more than one of this class to be constructed.
protected:
	//Default Methods
	// Constructors
	CClipper();
	// Copy Constructor
	CClipper(const CClipper&);
	// Copy-Assignment Operator
	CClipper& operator= (const CClipper&);
public:
	~CClipper();
	
	//Accessors
	static CClipper* GetInstance();
	void GetViewport(CRect& rect) const { rect = mViewport; }
	//Manipulators
	void SetViewport(int l, int t, int r, int b);
	void SetViewportVisible(bool bShowViewport) { mShowViewport = bShowViewport; }
	
	// Clipping Functions
	void DrawViewport();
	void ResetViewport();
	bool ClipPoint(int x, int y);
	bool ClipLine(CVertex2& v0, CVertex2& v1);
	void ClipTriangle(std::vector< CVertex2 >& vBuffer, std::vector< CVertex2 >& newVertices, ClipPlane planeFlag);

private:
	//Private Helper Functions
    bool IsInClipBounds(ClipPlane clipPlane, const CVertex2& v);
    CVertex2 IntersectWithPlane(const CVertex2& v0, const CVertex2& v1, ClipPlane planeFlag);

private:
	//Member Variables
	// Singleton Instance Pointer
	static CClipper* pInstance;
	// General
	CRect mViewport;
	bool mShowViewport;
};

#endif//#ifndef CLIPPER_H