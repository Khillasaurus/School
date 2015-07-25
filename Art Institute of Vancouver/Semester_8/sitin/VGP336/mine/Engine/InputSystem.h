#ifndef INCLUDED_ENGINE_INPUTSYSTEM_H
#define INCLUDED_ENGINE_INPUTSYSTEM_H

//====================================================================================================
// Filename:	InputSystem.h
// Created by:	Peter Chan
// Description:	Class for the input system with support for keyboard, mouse, and gamepad devices.
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void Initialize(HWND window);
	void Terminate();

	void Update();

	bool IsKeyDown(u32 key) const;
	bool IsKeyPressed(u32 key) const;

	bool IsMouseDown(u32 button) const;
	bool IsMousePressed(u32 button) const;

	s32 GetMouseScreenX() const;
	s32 GetMouseScreenY() const;

	bool IsMouseLeftEdge() const;
	bool IsMouseRightEdge() const;
	bool IsMouseTopEdge() const;
	bool IsMouseBottomEdge() const;

	s32 GetMouseMoveX() const;
	s32 GetMouseMoveY() const;
	s32 GetMouseMoveZ() const;

	bool IsGamePadButtonDown(u32 button) const;
	bool IsGamePadButtonPressed(u32 button) const;

	bool IsDPadUp() const;
	bool IsDPadDown() const;
	bool IsDPadLeft() const;
	bool IsDPadRight() const;

	f32 GetLeftAnalogX() const;
	f32 GetLeftAnalogY() const;
	f32 GetRightAnalogX() const;
	f32 GetRightAnalogY() const;

private:
	NONCOPYABLE(InputSystem);
	
	friend BOOL CALLBACK EnumGamePadCallback(const DIDEVICEINSTANCE* pDIDeviceInstance, VOID* pContext);

	void UpdateKeyboard();
	void UpdateMouse();
	void UpdateGamePad();

	IDirectInput8* mpDirectInput;
	IDirectInputDevice8* mpKeyboardDevice;
	IDirectInputDevice8* mpMouseDevice;
	IDirectInputDevice8* mpGamePadDevice;

	static const u32 kKeyBufferSize = 256;
	u8 mCurrKeyBuffer[kKeyBufferSize];
	u8 mPrevKeyBuffer[kKeyBufferSize];

	DIMOUSESTATE mCurrMouseState;
	DIMOUSESTATE mPrevMouseState;

	DIJOYSTATE mCurrGamePadState;
	DIJOYSTATE mPrevGamePadState;

	s32 mMouseX;
	s32 mMouseY;

	s32 mScreenWidth;
	s32 mScreenHeight;

	bool mInitialized;
};

#endif // #ifndef INCLUDED_ENGINE_INPUTSYSTEM_H