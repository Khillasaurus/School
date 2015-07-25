//====================================================================================================
// Filename:	InputSystem.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "InputSystem.h"

//====================================================================================================
// Callback Definitions
//====================================================================================================

BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext)
{
	// Obtain an interface to the enumerated joystick
	InputSystem* inputSystem = static_cast<InputSystem*>(pContext);
	IDirectInput8* pDI = inputSystem->mpDirectInput;
	IDirectInputDevice8** pGamePad = &(inputSystem->mpGamePadDevice);
	if (FAILED(pDI->CreateDevice(pDIDeviceInstance->guidInstance, pGamePad, nullptr))) 
	{
		LOG("[InputSystem] Failed to create game pad device.");
	}

	return DIENUM_STOP;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

InputSystem::InputSystem()
	: mpDirectInput(nullptr)
	, mpKeyboardDevice(nullptr)
	, mpMouseDevice(nullptr)
	, mpGamePadDevice(nullptr)
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

InputSystem::~InputSystem()
{
	ASSERT(!mInitialized, "[InputSystem] Terminate() must be called to clean up!");
}

//----------------------------------------------------------------------------------------------------

void InputSystem::Initialize(HWND window)
{
	// Check if we have already initialized the system
	if (mInitialized)
	{
		LOG("[InputSystem] System already initialized.");
		return;
	}

	LOG("[InputSystem] Initializing...");

	// Obtain an interface to DirectInput
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mpDirectInput, nullptr);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to create DirectInput object.");

	//----------------------------------------------------------------------------------------------------
	// Create keyboard device
	hr = mpDirectInput->CreateDevice(GUID_SysKeyboard, &mpKeyboardDevice, nullptr);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to create keyboard device.");

	// Set the keyboard data format
	hr = mpKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set keyboard data format.");

	// Set the keyboard cooperative level
	hr = mpKeyboardDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set keyboard cooperative level.");

	// Acquire the keyboard device
	hr = mpKeyboardDevice->Acquire();
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to acquire keyboard device.");
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Create mouse device
	hr = mpDirectInput->CreateDevice(GUID_SysMouse, &mpMouseDevice, nullptr);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to create mouse device.");

	// Set the mouse data format
	hr = mpMouseDevice->SetDataFormat(&c_dfDIMouse);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set mouse data format.");

	// Set the mouse cooperative level
	hr = mpMouseDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set mouse cooperative level.");

	// Acquire the mouse device
	hr = mpMouseDevice->Acquire();
	ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to acquire mouse device.");

	// Calculate starting mouse position
	RECT clientRect;
	GetClientRect(window, &clientRect);
	GetWindowRect(window, &clientRect);
	mScreenWidth = clientRect.right - clientRect.left;
	mScreenHeight = clientRect.bottom - clientRect.top;
	mMouseX = mScreenWidth >> 1;
	mMouseY = mScreenHeight >> 1;
	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	// Enumerate for game pad device
	if (FAILED(mpDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamePadCallback, this, DIEDFL_ATTACHEDONLY)))
	{
		LOG("[InputSystem] Failed to enumerate for game pad devices.");
	}

	// Check if we have a game pad detected
	if (mpGamePadDevice != nullptr)
	{
		// Set the game pad data format
		hr = mpGamePadDevice->SetDataFormat(&c_dfDIJoystick);
		ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set game pad data format.");

		// Set the game pad cooperative level
		hr = mpGamePadDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to set game pad cooperative level.");

		// Acquire the game pad device
		hr = mpGamePadDevice->Acquire();
		ASSERT(SUCCEEDED(hr), "[InputSystem] Failed to acquire game pad device.");
	}
	else
	{
		LOG("[InputSystem] No game pad attached.");
	}

	// Set flag
	mInitialized = true;

	LOG("[InputSystem] System initialized.");
}

//----------------------------------------------------------------------------------------------------

void InputSystem::Terminate()
{
	// Check if we have already terminated the system
	if (!mInitialized)
	{
		LOG("[InputSystem] System already terminated.");
		return;
	}

	LOG("[InputSystem] Terminating...");

	// Release devices
	if (mpGamePadDevice != nullptr)
	{
		mpGamePadDevice->Unacquire();
		mpGamePadDevice->Release();
		mpGamePadDevice = nullptr;
	}
	if (mpMouseDevice != nullptr)
	{
		mpMouseDevice->Unacquire();
		mpMouseDevice->Release();
		mpMouseDevice = nullptr;
	}
	if (mpKeyboardDevice != nullptr)
	{
		mpKeyboardDevice->Unacquire();
		mpKeyboardDevice->Release();
		mpKeyboardDevice = nullptr;
	}

	SafeRelease(mpDirectInput);

	// Set flag
	mInitialized = false;

	LOG("[InputSystem] System terminated.");
}

//----------------------------------------------------------------------------------------------------

void InputSystem::Update()
{
	ASSERT(mInitialized, "[InputSystem] System not initialized.");

	// Update keyboard
	if (mpKeyboardDevice != nullptr)
	{
		UpdateKeyboard();
	}

	// Update mouse
	if (mpMouseDevice != nullptr)
	{
		UpdateMouse();
	}

	// Update game pad
	if (mpGamePadDevice != nullptr)
	{
		UpdateGamePad();
	}
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsKeyDown(u32 key) const
{
	return (mCurrKeyBuffer[key] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsKeyPressed(u32 key) const
{
	const bool currState = (mCurrKeyBuffer[key] & 0x80) != 0;
	const bool prevState = (mPrevKeyBuffer[key] & 0x80) != 0;
	return !prevState && currState;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMouseDown(u32 button) const
{
	return (mCurrMouseState.rgbButtons[button] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMousePressed(u32 button) const
{
	const bool currState = (mCurrMouseState.rgbButtons[button] & 0x80) != 0;
	const bool prevState = (mPrevMouseState.rgbButtons[button] & 0x80) != 0;
	return !prevState && currState;
}

//----------------------------------------------------------------------------------------------------

s32 InputSystem::GetMouseScreenX() const
{
	return mMouseX;
}

//----------------------------------------------------------------------------------------------------

s32 InputSystem::GetMouseScreenY() const
{
	return mMouseY;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMouseLeftEdge() const
{
	return (mMouseX == 0);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMouseRightEdge() const
{
	return (mMouseX == mScreenWidth - 1);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMouseTopEdge() const
{
	return (mMouseY == 0);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsMouseBottomEdge() const
{
	return (mMouseY == mScreenHeight - 1);
}

//----------------------------------------------------------------------------------------------------

s32 InputSystem::GetMouseMoveX() const
{
	return mCurrMouseState.lX;
}

//----------------------------------------------------------------------------------------------------

s32 InputSystem::GetMouseMoveY() const
{
	return mCurrMouseState.lY;
}

//----------------------------------------------------------------------------------------------------

s32 InputSystem::GetMouseMoveZ() const
{
	return mCurrMouseState.lZ;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsGamePadButtonDown(u32 button) const
{
	return (mCurrGamePadState.rgbButtons[button] & 0x80) != 0;
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsGamePadButtonPressed(u32 button) const
{
	const bool currState = (mCurrGamePadState.rgbButtons[button] & 0x80) != 0;
	const bool prevState = (mPrevGamePadState.rgbButtons[button] & 0x80) != 0;
	return !prevState && currState;
}
//----------------------------------------------------------------------------------------------------

bool InputSystem::IsDPadUp() const
{
	const bool hasGamePad = (mpGamePadDevice != nullptr);
	return hasGamePad && (mCurrGamePadState.rgdwPOV[0] == 0);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsDPadDown() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 18000);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsDPadLeft() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 27000);
}

//----------------------------------------------------------------------------------------------------

bool InputSystem::IsDPadRight() const
{
	return (mCurrGamePadState.rgdwPOV[0] == 9000);
}

//----------------------------------------------------------------------------------------------------

float InputSystem::GetLeftAnalogX() const
{
	return (mCurrGamePadState.lX / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float InputSystem::GetLeftAnalogY() const
{
	return -(mCurrGamePadState.lY / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

float InputSystem::GetRightAnalogX() const
{
	return (mCurrGamePadState.lZ / 32767.5f) - 1.0f;
}

//----------------------------------------------------------------------------------------------------

float InputSystem::GetRightAnalogY() const
{
	return -(mCurrGamePadState.lRz / 32767.5f) + 1.0f;
}

//----------------------------------------------------------------------------------------------------

void InputSystem::UpdateKeyboard()
{
	// Store the previous keyboard state
	memcpy(mPrevKeyBuffer, mCurrKeyBuffer, kKeyBufferSize);

	// Get keyboard state
	static bool sWriteToLog = true;
	HRESULT hr = mpKeyboardDevice->GetDeviceState(kKeyBufferSize, (void*)mCurrKeyBuffer);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				LOG("[InputSystem] Keyboard device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire keyboard device again
			mpKeyboardDevice->Acquire();
		}
		else
		{
			LOG("[InputSystem] Failed to get keyboard state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}
}

//----------------------------------------------------------------------------------------------------

void InputSystem::UpdateMouse()
{
	// Store the previous mouse state
	memcpy(&mPrevMouseState, &mCurrMouseState, sizeof(DIMOUSESTATE));

	// Get mouse state
	static bool sWriteToLog = true;
	HRESULT hr = mpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void*)&mCurrMouseState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				LOG("[InputSystem] Mouse device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire mouse device again
			mpMouseDevice->Acquire();
		}
		else
		{
			LOG("[InputSystem] Failed to get mouse state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;

		// Update mouse position
		mMouseX += mCurrMouseState.lX;
		mMouseY += mCurrMouseState.lY;

		// Check bound
		if (mMouseX < 0)
			mMouseX = 0;
		if (mMouseX>= mScreenWidth)
			mMouseX = mScreenWidth - 1;
		if (mMouseY < 0)
			mMouseY = 0;
		if (mMouseY>= mScreenHeight)
			mMouseY = mScreenHeight - 1;
	}
}

//----------------------------------------------------------------------------------------------------

void InputSystem::UpdateGamePad()
{
	// Store the previous game pad state
	memcpy(&mPrevGamePadState, &mCurrGamePadState, sizeof(DIJOYSTATE));

	// Poll the game pad device
	static bool sWriteToLog = true;
	HRESULT hr = mpGamePadDevice->Poll();
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				LOG("[InputSystem] Game pad device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePadDevice->Acquire();
		}
		else
		{
			LOG("[InputSystem] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}

	// Get game pad state
	hr = mpGamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), (void*)&mCurrGamePadState);
	if (FAILED(hr))
	{   
		// Check if the device is lost
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			if (sWriteToLog)
			{
				LOG("[InputSystem] Game pad device is lost.");
				sWriteToLog = false;
			}

			// Try to acquire game pad device again
			mpGamePadDevice->Acquire();
		}
		else
		{
			LOG("[InputSystem] Failed to get game pad state.");
			return;
		}
	}
	else
	{
		// Reset flag
		sWriteToLog = true;
	}
}