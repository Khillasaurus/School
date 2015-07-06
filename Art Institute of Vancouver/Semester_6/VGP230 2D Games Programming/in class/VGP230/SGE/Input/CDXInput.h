#ifndef INCLUDED_DXINPUT_H
#define INCLUDED_DXINPUT_H

//====================================================================================================
// Filename:	CDXInput.h
// Created by:	Peter Chan
// Description:	Singleton class for the input system. It provides support for keyboard, mouse, and
//			  gamepad control. Internally it uses DirectInput devices to handle all input
//			  detections. The singleton can be accessed via a call to CDXInput::Get().
//====================================================================================================

//====================================================================================================
// Defines
//====================================================================================================

#define DIRECTINPUT_VERSION 0x0800

//====================================================================================================
// Includes
//====================================================================================================

#include <dinput.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

class CDXInput
{
	// Declare the game pad enumeration function as a friend
	friend BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext);

public:
	// Accessor function for singleton instance
	static CDXInput* Get(void);

protected:
	// Protected constructor for singleton
	CDXInput(void);

public:
	// Functions to startup/shutdown the input system
	void Initialize(HWND hWindow);
	void Terminate(void);

	// Function to update the input device states
	void Update(void);

	// Functions to query for a key state
	bool IsKeyDown(int iKey) const;
	bool IsKeyPressed(int iKey) const;

	// Functions to query for a mouse state
	bool IsMouseDown(int iMouse) const;
	bool IsMousePressed(int iMouse) const;

	// Functions to get the mouse position
	int GetMouseScreenX(void) const;
	int GetMouseScreenY(void) const;

	// Functions to check screen boundary
	bool IsMouseLeftEdge(void) const;
	bool IsMouseRightEdge(void) const;
	bool IsMouseTopEdge(void) const;
	bool IsMouseBottomEdge(void) const;

	// Functions to get the mouse movement
	int GetMouseMoveX(void) const;
	int GetMouseMoveY(void) const;
	int GetMouseMoveZ(void) const;

	// Functions to query for game pad button state
	bool IsGamePadButtonDown(int iButton) const;
	bool IsGamePadButtonPressed(int iButton) const;

	// Functions to get the game pad directional pad
	bool IsDPadUp(void) const;
	bool IsDPadDown(void) const;
	bool IsDPadLeft(void) const;
	bool IsDPadRight(void) const;

	// Functions to get the game pad analog stick
	float GetLeftAnalogX(void) const;
	float GetLeftAnalogY(void) const;
	float GetRightAnalogX(void) const;
	float GetRightAnalogY(void) const;

private:
	// Function to update the different input devices
	void UpdateKeyboard(void);
	void UpdateMouse(void);
	void UpdateGamePad(void);

	// Members
	static CDXInput* s_Instance;			// Static instance for singleton

	IDirectInput8* mpDI;				   // Interface to DirectInput
	IDirectInputDevice8* mpKeyboard;	   // Keyboard device
	IDirectInputDevice8* mpMouse;		  // Mouse device
	IDirectInputDevice8* mpGamePad;		// Game pad device

	static const int kKeyBufferSize = 256;
	char mCurrKeyBuffer[kKeyBufferSize]; // Buffer for current key states
	char mPrevKeyBuffer[kKeyBufferSize]; // Buffer for previous key states

	DIMOUSESTATE mCurrMouseState;		  // Current mouse state
	DIMOUSESTATE mPrevMouseState;		  // Previous mouse state

	DIJOYSTATE mCurrGamePadState;		  // Current game pad state
	DIJOYSTATE mPrevGamePadState;		  // Previous game pad state

	int mMouseX;						   // Current mouse position X
	int mMouseY;						   // Current mouse position Y

	int mScreenWidth;					  // Screen width
	int mScreenHeight;					 // Screen height

	bool mInitialized;					 // Init flag
};

#endif // #ifndef INCLUDED_DXINPUT_H