#include"MouseInput.h"


void MouseInput::HandleMouseButtonInput(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < static_cast<int>(InputKeys::eMouseButtons::Count); i++)
	{
		if (((InputKeys::myListOfMouseButtons[i]) & wParam))
		{
			if (myHeldDownMouseButtons[i] == false)
			{
				myPressedMouseButtons[i] = true;
			}
			myHeldDownMouseButtons[i] = true;
		}
	}
}

void MouseInput::HandleReleasedMouseButtonInput(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < static_cast<int>(InputKeys::eMouseButtons::Count); i++)
	{
		myPressedMouseButtons[i] = ((InputKeys::myListOfMouseButtons[i]) & wParam);
		myJustReleasedMouseButtons[i] = !((InputKeys::myListOfMouseButtons[i]) & wParam);
		myHeldDownMouseButtons[i] = ((InputKeys::myListOfMouseButtons[i]) & wParam);
		myPressedLastFrameMouseButtons[i] = ((InputKeys::myListOfMouseButtons[i]) & wParam);
	}
}

void MouseInput::HandleMouseScroll(WPARAM wParam)
{
	myMouseWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
}

void MouseInput::HandleMouseMovement(LPARAM lParam)
{

	myMousePositionDeltaXY[0] = GET_X_LPARAM(lParam) - myMousePositionDeltaXY[0];
	myMousePositionDeltaXY[1] = GET_Y_LPARAM(lParam) - myMousePositionDeltaXY[1];
}

void MouseInput::HandleSetMousePosition(int aX, int anY)
{
	SetCursorPos(aX, anY);
}

const std::array<float, 2> & MouseInput::GetMouseMovement()const
{
	return myMousePositionDeltaXY;
}

int MouseInput::GetMouseWheelDeltaScroll()const
{
	return myMouseWheelDelta;
}

const std::array<float, 2> MouseInput::GetMousePos()const
{
	POINT cursor;
	GetCursorPos(&cursor);
	std::array<float, 2> cursorPosXY;
	cursorPosXY[0] = cursor.x;
	cursorPosXY[1] = cursor.y;

	return cursorPosXY;
}

bool MouseInput::GetIsMouseButtonPressed(int aMouseButtonCode)const
{
	return (myPressedMouseButtons[aMouseButtonCode] == true);
}

bool MouseInput::GetIsMouseButtonReleased(int aMouseButtonCode)const
{
	return (myJustReleasedMouseButtons[aMouseButtonCode] == true);
}

bool MouseInput::GetIsMouseButtonHeld(int aMouseButtonCode)const
{
	return (myHeldDownMouseButtons[aMouseButtonCode] == true);
}


void MouseInput::ReleaseAllMouseButtons()
{
	myHeldDownMouseButtons = { false };
}

void MouseInput::ResetReleaseMouseInput()
{
	myPressedMouseButtons = { false };
	myJustReleasedMouseButtons = { false };
	myMouseWheelDelta = 0;

}
