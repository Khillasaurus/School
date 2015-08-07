#ifndef STATEMANAGER_H
#define STATEMANAGER_H

//=============================================================================
//Dependencies
//=============================================================================

#include "../Common/Color.h"

//=============================================================================
//Enumerations
//=============================================================================

enum FillMode
{
	kFillModeNone = -1,

	kFillModePoint,
	kFillModeLine,
	kFillModeFill,

	kFillModeFirst = kFillModeNone,
	kFillModeLast = kFillModeFill
};

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
	:	mFillMode(FillMode::kFillModeNone)
	{
	}
	// Copy Constructor
	CStateManager(const CStateManager&);
	// Copy-Assignment Operator
	CStateManager& operator= (const CStateManager&);
public:
	// Destructor
	~CStateManager();

	//Accessors
	static CStateManager* GetInstance();
	const CColor& GetColor() const;
	FillMode GetFillMode() const;


	//Manipulators
	void SetColor(const CColor& color);
	void SetFillMode(FillMode mode);

private:
	//Member Variables
	// Singleton Instance Pointer
	static CStateManager* pInstance;
	// State Definers
	CColor mColor;
	FillMode mFillMode;
};

#endif //#ifndef STATEMANAGER_H