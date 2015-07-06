//====================================================================================================
// Filename:	CDXInput.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Input/CDXInput.h"

#include "Core/CLog.h"

//====================================================================================================
// Statics
//====================================================================================================

CDXInput* CDXInput::s_Instance = NULL;

//====================================================================================================
// Callback Function
//====================================================================================================

BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext)
{
	// Obtain an interface to the enumerated joystick.
	IDirectInput8*		  pDI = CDXInput::Get()->mpDI;
	IDirectInputDevice8**   pGamePad = &(CDXInput::Get()->mpGamePad);
	if (FAILED(pDI->CreateDevice(pDIDeviceInstance->guidInstance, pGamePad, NULL))) 
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Failed to create game pad device.");
	}

	return DIENUM_STOP;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

CDXInput* CDXInput::Get(void)
{
	// If we do not yet have an instance created
	if (NULL == s_Instance)
	{
		// Create a new instance
		s_Instance = new CDXInput;
	}

	return s_Instance;
}

//----------------------------------------------------------------------------------------------------

CDXInput::CDXInput(void)
	: mpDI(NULL)
	, mpKeyboard(NULL)
	, mpMouse(NULL)
	, mpGamePad(NULL)
	, mMouseX(0)
	, mMouseY(0)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mInitialized(false)
{
	ZeroMemory(mCurrKeyBuffer, kKeyBufferSize);
	ZeroMemory(mPrevKeyBuffer, kKeyBufferSize);
	ZeroMemory(&mCurrMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&mPrevMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&mCurrGamePadState, sizeof(DIJOYSTATE));
	ZeroMemory(&mPrevGamePadState, sizeof(DIJOYSTATE));
}

//----------------------------------------------------------------------------------------------------

void CDXInput::Initialize(HWND hWindow)
{
	// Check if we have already initialized the system
	if (mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Input] System already initialized.");
		return;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Input] Initializing...");

	// Obtain an interface to DirectInput
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDI, NULL)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to create DirectInput object.");
		return;
	}

	//----------------------------------------------------------------------------------------------------
	// Create keyboard device
	if (FAILED(mpDI->CreateDevice(GUID_SysKeyboard, &mpKeyboard, NULL)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to create keyboard device.");
		return;
	}

	// Set the keyboard data format
	if (FAILED(mpKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set keyboard data format.");
		return;
	}

	// Set the keyboard cooperative level
	if (FAILED(mpKeyboard->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set keyboard cooperative level.");
		return;
	}

	// Acquire the keyboard device
	if (FAILED(mpKeyboard->Acquire()))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to acquire keyboard device.");
	}
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Create mouse device
	if (FAILED(mpDI->CreateDevice(GUID_SysMouse, &mpMouse, NULL)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to create mouse device.");
		return;
	}

	// Set the mouse data format
	if (FAILED(mpMouse->SetDataFormat(&c_dfDIMouse)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set mouse data format.");
		return;
	}

	// Set the mouse cooperative level
	if (FAILED(mpMouse->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set mouse cooperative level.");
		return;
	}

	// Acquire the mouse device
	if (FAILED(mpMouse->Acquire()))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to acquire mouse device.");
	}

	// Calculate starting mouse position
	RECT clientRect;
	GetClientRect(hWindow, &clientRect);
	mScreenWidth = clientRect.right - clientRect.left;
	mScreenHeight = clientRect.bottom - clientRect.top;
	mMouseX = mScreenWidth>> 1;
	mMouseY = mScreenHeight>> 1;
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Enumerate for game pad device
	if (FAILED(mpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamePadCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Failed to enumerate for game pad devices.");
	}

	// Check if we have a game pad detected
	if (NULL != mpGamePad)
	{
		// Set the game pad data format
		if (FAILED(mpGamePad->SetDataFormat(&c_dfDIJoystick)))
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set game pad data format.");
			return;
		}

		// Set the game pad cooperative level
		if (FAILED(mpGamePad->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to set game pad cooperative level.");
			return;
		}

		// Acquire the game pad device
		if (FAILED(mpGamePad->Acquire()))
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to acquire game pad device.");
		}
	}
	else
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Input] No game pad attached.");
	}

	// Set flag
	mInitialized = true;

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Input] System initialized.");
}

//----------------------------------------------------------------------------------------------------

void CDXInput::Terminate(void)
{
	// Check if we have already terminated the system
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Input] System already terminated.");
		return;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Input] Terminating...");

	// Release devices
	if (NULL != mpGamePad)
	{
		mpGamePad->Unacquire();
		mpGamePad->Release();
		mpGamePad = NULL;
	}
	if (NULL != mpMouse)
	{
		mpMouse->Unacquire();
		mpMouse->Release();
		mpMouse = NULL;
	}
	if (NULL != mpKeyboard)
	{
		mpKeyboard->Unacquire();
		mpKeyboard->Release();
		mpKeyboard = NULL;
	}

	// Release DirectInput interface
	if (NULL != mpDI)
	{
		mpDI->Release();
		mpDI = NULL;
	}

	// Set flag
	mInitialized = false;

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Input] System terminated");
}

//----------------------------------------------------------------------------------------------------

void CDXInput::Update(void)
{
	// Check if the system is initialized
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to update input devices. System not initialized.");
		return;
	}

	// Update keyboard
	if (NULL != mpKeyboard)
	{
		UpdateKeyboard();
	}

	// Update mouse
	if (NULL != mpMouse)
	{
		UpdateMouse();
	}

	// Update game pad
	if (NULL != mpGamePad)
	{
		UpdateGamePad();
	}
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsKeyDown(int iKey) const
{
	return (mCurrKeyBuffer[iKey] & 0x80) ? true : false;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsKeyPressed(int iKey) const
{
	bool bCurrState = (mCurrKeyBuffer[iKey] & 0x80) ? true : false;
	bool bPrevState = (mPrevKeyBuffer[iKey] & 0x80) ? true : false;

	return !bPrevState && bCurrState;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMouseDown(int iMouse) const
{
	return (mCurrMouseState.rgbButtons[iMouse] & 0x80) ? true : false;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMousePressed(int iMouse) const
{
	bool bCurrState = (mCurrMouseState.rgbButtons[iMouse] & 0x80) ? true : false;
	bool bPrevState = (mPrevMouseState.rgbButtons[iMouse] & 0x80) ? true : false;

	return !bPrevState && bCurrState;
}

//----------------------------------------------------------------------------------------------------

int CDXInput::GetMouseScreenX(void) const
{
	return mMouseX;
}

//----------------------------------------------------------------------------------------------------

int CDXInput::GetMouseScreenY(void) const
{
	return mMouseY;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMouseLeftEdge(void) const
{
	return (mMouseX == 0);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMouseRightEdge(void) const
{
	return (mMouseX == mScreenWidth - 1);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMouseTopEdge(void) const
{
	return (mMouseY == 0);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsMouseBottomEdge(void) const
{
	return (mMouseY == mScreenHeight - 1);
}

//----------------------------------------------------------------------------------------------------

int CDXInput::GetMouseMoveX(void) const
{
	return mCurrMouseState.lX;
}

//----------------------------------------------------------------------------------------------------

int CDXInput::GetMouseMoveY(void) const
{
	return mCurrMouseState.lY;
}

//----------------------------------------------------------------------------------------------------

int CDXInput::GetMouseMoveZ(void) const
{
	return mCurrMouseState.lZ;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsGamePadButtonDown(int iButton) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	return (mCurrGamePadState.rgbButtons[iButton] & 0x80) ? true : false;
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsGamePadButtonPressed(int iButton) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	bool bCurrState = (mCurrGamePadState.rgbButtons[iButton] & 0x80) ? true : false;
	bool bPrevState = (mPrevGamePadState.rgbButtons[iButton] & 0x80) ? true : false;

	return !bPrevState && bCurrState;
}
//----------------------------------------------------------------------------------------------------

bool CDXInput::IsDPadUp(void) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	return (mCurrGamePadState.rgdwPOV[0] == 0);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsDPadDown(void) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	return (mCurrGamePadState.rgdwPOV[0] == 18000);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsDPadLeft(void) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	return (mCurrGamePadState.rgdwPOV[0] == 27000);
}

//----------------------------------------------------------------------------------------------------

bool CDXInput::IsDPadRight(void) const
{
	if (NULL == mpGamePad)
	{
		return false;
	}

	return (mCurrGamePadState.rgdwPOV[0] == 9000);
}

//----------------------------------------------------------------------------------------------------

float CDXInput::GetLeftAnalogX(void) const
{
	if (NULL == mpGamePad)
	{
		return 0.0f;
	}

	return (mCurrGamePadState.lX / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float CDXInput::GetLeftAnalogY(void) const
{
	if (NULL == mpGamePad)
	{
		return 0.0f;
	}

	return -(mCurrGamePadState.lY / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

float CDXInput::GetRightAnalogX(void) const
{
	if (NULL == mpGamePad)
	{
		return 0.0f;
	}

	return (mCurrGamePadState.lZ / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float CDXInput::GetRightAnalogY(void) const
{
	if (NULL == mpGamePad)
	{
		return 0.0f;
	}

	return -(mCurrGamePadState.lRz / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

void CDXInput::UpdateKeyboard(void)
{
	// Store the previous keyboard state
	memcpy(mPrevKeyBuffer, mCurrKeyBuffer, kKeyBufferSize);

	// Get keyboard state
	static bool s_WriteToLog = true;
	HRESULT hr = mpKeyboard->GetDeviceState(kKeyBufferSize, (void*)mCurrKeyBuffer);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			// Write to log
			if (s_WriteToLog)
			{
				CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Keyboard device is lost.");
				s_WriteToLog = false;
			}

			// Try to acquire keyboard device again
			mpKeyboard->Acquire();
		}
		else
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to get keyboard state.");
			return;
		}
	}
	else
	{
		// Reset flag
		s_WriteToLog = true;
	}
}

//----------------------------------------------------------------------------------------------------

void CDXInput::UpdateMouse(void)
{
	// Store the previous mouse state
	memcpy(&mPrevMouseState, &mCurrMouseState, sizeof(DIMOUSESTATE));

	// Get mouse state
	static bool s_WriteToLog = true;
	HRESULT hr = mpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (void*)&mCurrMouseState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			// Write to log
			if (s_WriteToLog)
			{
				CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Mouse device is lost.");
				s_WriteToLog = false;
			}

			// Try to acquire mouse device again
			mpMouse->Acquire();
		}
		else
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to get mouse state.");
			return;
		}
	}
	else
	{
		// Reset flag
		s_WriteToLog = true;

		// Update mouse position
		mMouseX += mCurrMouseState.lX;
		mMouseY += mCurrMouseState.lY;

		// Check bound
		if (mMouseX <0)
			mMouseX = 0;
		if (mMouseX>= mScreenWidth)
			mMouseX = mScreenWidth - 1;
		if (mMouseY <0)
			mMouseY = 0;
		if (mMouseY>= mScreenHeight)
			mMouseY = mScreenHeight - 1;
	}
}

//----------------------------------------------------------------------------------------------------

void CDXInput::UpdateGamePad(void)
{
	// Store the previous game pad state
	memcpy(&mPrevGamePadState, &mCurrGamePadState, sizeof(DIJOYSTATE));

	// Poll the game pad device
	static bool s_WriteToLog = true;
	HRESULT hr = mpGamePad->Poll();
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			// Write to log
			if (s_WriteToLog)
			{
				CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Game pad device is lost.");
				s_WriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePad->Acquire();
		}
		else
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		s_WriteToLog = true;
	}

	// Get game pad state
	hr = mpGamePad->GetDeviceState(sizeof(DIJOYSTATE), (void*)&mCurrGamePadState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			// Write to log
			if (s_WriteToLog)
			{
				CLog::Get()->Write(ELogMessageType_WARNING, "[Input] Game pad device is lost.");
				s_WriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePad->Acquire();
		}
		else
		{
			// Write to log
			CLog::Get()->Write(ELogMessageType_ERROR, "[Input] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		s_WriteToLog = true;
	}
}