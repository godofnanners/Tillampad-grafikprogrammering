#include "CWindowHandler.h"
#include <string>
LRESULT CALLBACK CWindowHandler::WinProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	static CWindowHandler* windowhandler = nullptr;

	if (uMsg == WM_DESTROY || uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* createstruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		windowhandler = reinterpret_cast<CWindowHandler*>(createstruct->lpCreateParams);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

CWindowHandler::CWindowHandler()
{
	myWindowHandle = nullptr;
}

CWindowHandler::~CWindowHandler()
{
	
}

bool CWindowHandler::Init(SWindowData aWindowData)
{
	const auto className = L"TillämpadGrafikprogrammering";
	WNDCLASS windowclass = {};
	windowclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowclass.lpfnWndProc = CWindowHandler::WinProc;
	windowclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowclass.lpszClassName = className;
	RegisterClass(&windowclass);
	
	myWindowData = aWindowData;
	myWindowHandle = CreateWindow(className, L"My Awesome Game", WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE, aWindowData.myX, aWindowData.myY, aWindowData.myWidth, aWindowData.myHeight, nullptr, nullptr, nullptr, this);
	return true;
}

HWND CWindowHandler::GetWindowHandle()
{
	return myWindowHandle;
}

const int CWindowHandler::GetWidth()
{
	return myWindowData.myWidth;
}

const int CWindowHandler::GetHeight()
{
	return myWindowData.myHeight;
}

