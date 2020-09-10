#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <array>
#include "InputKeys.h"
#include <windowsx.h>
class MouseInput
{
public:
	void HandleMouseButtonInput(WPARAM wParam, LPARAM lParam);
	void HandleReleasedMouseButtonInput(WPARAM wParam, LPARAM lParam);
	void HandleMouseScroll(WPARAM wParam);
	void HandleMouseMovement(LPARAM lParam);
	void HandleSetMousePosition(int aX, int anY);
	const std::array<float, 2> & GetMouseMovement()const;
	int GetMouseWheelDeltaScroll()const;
	const std::array<float, 2> GetMousePos()const;
	bool GetIsMouseButtonPressed(int aKeyCode) const;
	bool GetIsMouseButtonReleased(int aKeyCode) const;
	bool GetIsMouseButtonHeld(int aKeyCode) const;
	void ReleaseAllMouseButtons();
	void ResetReleaseMouseInput();
private:
	std::array<bool, 7> myPressedLastFrameMouseButtons;
	std::array<bool, 7> myPressedMouseButtons;
	std::array<bool, 7> myHeldDownMouseButtons;
	std::array<bool, 7> myJustReleasedMouseButtons;
	int myMouseWheelDelta;
	std::array<float, 2>myMousePositionDeltaXY;
};