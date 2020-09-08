#include "KeyBoardInputs.h"

void KeyBoardInputs::HandlePressedKeyBoardInput(WPARAM wParam, LPARAM lParam)
{
	SetPressedAndHeldKeys(wParam, lParam);
}

void KeyBoardInputs::HandleReleasedKeyBoardInput(WPARAM wParam, LPARAM lParam)
{
	myPressedKeys[wParam] = false;
	myHeldDownKeys[wParam] = false;
	myJustReleasedKeys[wParam] = true;
}

void KeyBoardInputs::SetPressedAndHeldKeys(int aKeyCode, LPARAM lParam)
{
	if (myHeldDownKeys[aKeyCode] == false)
	{
		myPressedKeys[aKeyCode] = true;
	}
	else
	{
		myPressedKeys[aKeyCode] = false;
	}
	myHeldDownKeys[aKeyCode] = true;
}

bool KeyBoardInputs::CheckIfKeyIsPressed(int aKeyCode) const
{
	return (myPressedKeys[aKeyCode] == true);
}

bool KeyBoardInputs::CheckIfKeyIsHeld(int aKeyCode) const
{
	return (myHeldDownKeys[aKeyCode] == true);
}

bool KeyBoardInputs::CheckIfKeyJustWasReleased(int aKeyCode) const
{
	return (myJustReleasedKeys[aKeyCode] == true);
}

void KeyBoardInputs::ResetReleaseKeyBoardKeys()
{
	myJustReleasedKeys = { false };
	myPressedKeys = { false };
}

void KeyBoardInputs::ReleaseAllKeys()
{
	myPressedKeys = { false };
	myHeldDownKeys = { false };
}
