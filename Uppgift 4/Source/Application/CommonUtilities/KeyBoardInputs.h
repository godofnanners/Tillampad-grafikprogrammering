#pragma once
#include <Windows.h>
#include <WinUser.h>
#include <array>
class KeyBoardInputs
{
public:
	void HandlePressedKeyBoardInput(WPARAM wParam, LPARAM lParam);
	void HandleReleasedKeyBoardInput(WPARAM wParam, LPARAM lParam);
	void SetPressedAndHeldKeys(int aKeyCode, LPARAM lParam);
	bool CheckIfKeyIsPressed(int aKeyCode)const;
	bool CheckIfKeyIsHeld(int aKeyCode)const;
	bool CheckIfKeyJustWasReleased(int aKeyCode)const;
	void ResetReleaseKeyBoardKeys();
	void ReleaseAllKeys();
private:
	std::array<bool, 0xFE> myHeldDownKeys;
	std::array<bool, 0xFE> myPressedKeys;
	std::array<bool, 0xFE> myJustReleasedKeys;
};

