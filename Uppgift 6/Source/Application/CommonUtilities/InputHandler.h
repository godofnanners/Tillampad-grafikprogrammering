#pragma once
#include <Windows.h>
#include "KeyBoardInputs.h"
#include "MouseInput.h"
#include <WinUser.h>
namespace CommonUtilities
{
	class InputHandler
	{
	public:
		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);
		void ResetEvents();
		const std::array<float, 2>& CheckMouseMovement() const;
		int CheckScrollWheelDelta() const;
		bool CheckKeyDown(int aKeyCode) const;
		bool CheckIfKeyIsPressed(int aKeyCode) const;
		bool CheckIfKeyIsHeld(int aKeyCode) const;
		bool CheckIfKeyJustWasReleased(int aKeyCode) const;
		bool CheckIfMouseButtonIsPressed(int aKeyCode) const;
		bool CheckIfMouseButtonWasJustReleased(int aKeyCode) const;
		bool CheckIfMouseButtonIsHeldDown(int aKeyCode)const;
		std::array<float, 2> CheckMousePos() const;
		void SetMousePosition(int aX, int anY);
		static InputHandler& GetInstance();
	private:
		InputHandler() = default;
		static InputHandler myInstance;
		KeyBoardInputs myKeyboardInputs;
		MouseInput myMouseInput;

	};
}
