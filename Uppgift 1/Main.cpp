#include <Windows.h>
#include "CGraphicsEngine.h"
#pragma comment (lib,"d3d11.lib")
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nSHowCmd)
{
	hInstance; hPrevInstance; lpCmdLine; nSHowCmd;
	
	CWindowHandler::SWindowData windowData;
	windowData.myX = 100;
	windowData.myY = 100;
	windowData.myWidth = 1600;
	windowData.myHeight = 900;
	CGraphicsEngine graphicsEngine;
	bool shouldRun = graphicsEngine.Init(windowData);
	MSG windowmessage = { 0 };

	while (shouldRun)
	{
		while (PeekMessage(&windowmessage, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&windowmessage);
			DispatchMessage(&windowmessage);

			if (windowmessage.message == WM_QUIT)
			{
				shouldRun = false;
			}
		}
		graphicsEngine.BeginFrame();
		graphicsEngine.EndFrame();
	}
	return 0;
}