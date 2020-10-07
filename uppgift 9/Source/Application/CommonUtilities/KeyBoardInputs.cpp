#include "KeyBoardInputs.h"

void KeyBoardInputs::HandlePressedKeyBoardInput(WPARAM wParam)
{
	SetPressedAndHeldKeys((int)wParam);
}

void KeyBoardInputs::HandleReleasedKeyBoardInput(WPARAM wParam)
{
	myPressedKeys[wParam] = false;
	myHeldDownKeys[wParam] = false;
	myJustReleasedKeys[wParam] = true;
}

void KeyBoardInputs::SetPressedAndHeldKeys(int aKeyCode)
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

bool KeyBoardInputs::CheckIfKeyIsDown(int aKeyCode) const
{
	return (myHeldDownKeys[aKeyCode] || myPressedKeys[aKeyCode]);
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
