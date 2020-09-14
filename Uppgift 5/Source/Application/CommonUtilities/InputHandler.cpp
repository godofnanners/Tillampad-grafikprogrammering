#include "InputHandler.h"
#include <WinUser.h>
namespace CommonUtilities
{
	bool InputHandler::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			//Keyboard Input
		case(WM_KEYDOWN):
		{
			myKeyboardInputs.HandlePressedKeyBoardInput(wParam, lParam);
			break;
		}
		case (WM_KEYUP):
		{
			myKeyboardInputs.HandleReleasedKeyBoardInput(wParam, lParam);
			break;
		}
		//Mouse Input
		case (WM_MOUSEMOVE):
		{
			myMouseInput.HandleMouseMovement(lParam);
			break;
		}
		case (WM_MOUSEWHEEL):
		{
			myMouseInput.HandleMouseScroll(wParam);
			break;
		}

		case (WM_LBUTTONDOWN):
		case (WM_RBUTTONDOWN):
		case (WM_MBUTTONDOWN):
		case(WM_XBUTTONDOWN):
		{
			myMouseInput.HandleMouseButtonInput(wParam, lParam);
			break;
		}

		case (WM_LBUTTONUP):
		case (WM_RBUTTONUP):
		case (WM_MBUTTONUP):
		case(WM_XBUTTONUP):
		{
			myMouseInput.HandleReleasedMouseButtonInput(wParam, lParam);
			break;
		}

		/*if window comes out of focus release all buttons/keys*/
		case(WM_SETFOCUS):
		{
			myKeyboardInputs.ReleaseAllKeys();
			myMouseInput.ReleaseAllMouseButtons();
		}

		default:
			break;
		}
		return false;
	}


	void InputHandler::ResetEvents()
	{
		myKeyboardInputs.ResetReleaseKeyBoardKeys();
		myMouseInput.ResetReleaseMouseInput();
	}


	bool InputHandler::CheckIfKeyIsPressed(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyIsPressed(aKeyCode);
	}

	bool InputHandler::CheckIfKeyIsHeld(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyIsHeld(aKeyCode);
	}

	bool InputHandler::CheckIfKeyJustWasReleased(int aKeyCode) const
	{
		return myKeyboardInputs.CheckIfKeyJustWasReleased(aKeyCode);
	}

	const std::array<float, 2> & InputHandler::CheckMouseMovement() const
	{
		return myMouseInput.GetMouseMovement();
	}

	int InputHandler::CheckScrollWheelDelta() const
	{
		return myMouseInput.GetMouseWheelDeltaScroll();
	}

	bool InputHandler::CheckIfMouseButtonIsPressed(int aKeyCode) const
	{
		return myMouseInput.GetIsMouseButtonPressed(aKeyCode);
	}

	bool InputHandler::CheckIfMouseButtonWasJustReleased(int aKeyCode) const
	{
		return myMouseInput.GetIsMouseButtonReleased(aKeyCode);
	}

	bool InputHandler::CheckIfMouseButtonIsHeldDown(int aKeyCode) const
	{
		return myMouseInput.GetIsMouseButtonHeld(aKeyCode);
	}

	std::array<float, 2> InputHandler::CheckMousePos() const
	{
		return myMouseInput.GetMousePos();
	}

	void InputHandler::SetMousePosition(int aX, int anY)
	{
		myMouseInput.HandleSetMousePosition(aX, anY);
	}
}
