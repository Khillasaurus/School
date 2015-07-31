#ifndef PRIMMANAGER_H
#define PRIMMANAGER_H

//=============================================================================
//Dependencies
//=============================================================================

#include "../Common/Vertex2.h"

#include <vector>

//=============================================================================
//Enumerations
//=============================================================================

enum Primitive
{
	kPrimitiveNone = -1,

	kPrimitivePoint,
	kPrimitiveLine,
	kPrimitiveTriangle,

	kPrimitiveFirst = kPrimitiveNone,
	kPrimitiveLast = kPrimitiveTriangle
};

//=============================================================================
//Class Declarations
//=============================================================================

//Singleton
class CPrimManager
{
	//Singleton Duplication Prevention
	//TOIMPROVE: These do not prevent duplication in ALL cases, but the vast majority of them, all of which should fall under the scope of this project. Exeption example: Multithreading may allow for more than one of this class to be constructed.
protected:
	//Default Methods
	// Constructors
	CPrimManager()
	:	mPrimitive(Primitive::kPrimitiveNone)
	,	mDrawBegin(false)
	{
	}
	// Copy Constructor
	CPrimManager(const CPrimManager&);
	// Copy-Assignment Operator
	CPrimManager& operator= (const CPrimManager&);
public:
	// Destructor
	~CPrimManager();

	//State Checking
	bool InDrawMode() { return mDrawBegin; }

	//Vertex Functions
	void BeginDraw(Primitive type);
	void AddVertex(const CVertex2& vertex);
	void EndDraw();

	//Accessors
	static CPrimManager* GetInstance();
	Primitive GetPrimitive() const { return mPrimitive; };

private:
	//Member Variables
	// Singleton Instance Pointer
	static CPrimManager* pInstance;
	// State Definers
	bool mDrawBegin;
	Primitive mPrimitive;
	// Data Holding
	std::vector<CVertex2> mVertexBuffer;
};

#endif //#ifndef PRIMMANAGER_H