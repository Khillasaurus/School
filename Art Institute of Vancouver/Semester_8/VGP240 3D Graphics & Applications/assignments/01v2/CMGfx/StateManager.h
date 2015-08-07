#ifndef STATEMANAGER_H
#define STATEMANAGER_H

//=============================================================================
//Dependencies
//=============================================================================

#include "Common/color.h"

//=============================================================================
//Enumerations
//=============================================================================

enum FillMode
{
	kNone = -1,

	kPoint,
	kLine,
	kFill,

	kFirst = kNone,
	kLast = kFill
}

//=============================================================================
//Class Declarations
//=============================================================================

//Singleton
class CStateManager
{
	//Singleton Duplication Prevention
	//TOIMPROVE: These do not prevent duplication in ALL cases, but the vast majority of them, all of which should fall under the scope of this project. Exeption example: Multithreading may allow for more than one of this class to be constructed.
protected:
	//Default Methods
	// Constructors
	CStateManager()
	:	mFillModeCur(FillMode::kNone)
	{
		pInstance = nullptr;
	}
	// Copy Constructor
	CStateManager(const CStateManager&);
	// Copy-Assignment Operator
	CStateManager& operator= (const CStateManager&);
	// Destructor
	~CStateManager();

public:
	//Accessors
	static CStateManager* GetInstance();
	const CColor& GetColor() const;
	FillMode GetFillMode() const { return mFillModeCur; };


	//Manipulators
	void SetColor(const CColor& color);
	void SetFillMode(FillMode mode);

private:
	//Member Variables
	// Singleton Instance Pointer
	static CStateManager* pInstance;
	// General
	CColor mColorCur;
	FillMode mFillModeCur;
};

#endif //#ifndef STATEMANAGER_H