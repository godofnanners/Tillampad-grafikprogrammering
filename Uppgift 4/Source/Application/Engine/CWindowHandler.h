#pragma once
#include <Windows.h>

class CWindowHandler
{
public:
	struct SWindowData
	{
		int myX;
		int myY;
		int myWidth;
		int myHeight;
	};

	static LRESULT CALLBACK WinProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	CWindowHandler();
	~CWindowHandler();
	bool Init(SWindowData aWindowData);
	HWND GetWindowHandle();
	const int GetWidth();
	const int GetHeight();
private:
	HWND myWindowHandle;
	SWindowData myWindowData;
};