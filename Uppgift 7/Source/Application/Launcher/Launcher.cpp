// Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <Windows.h>
#include "Engine.h"
#include "Game.h"
#include "CModelFactory.h"
#include "CModel.h"
#include "CModelInstance.h"
#include "CScene.h"
#include "CCameraFactory.h"
#include "CCamera.h"
#include "Vector3.hpp"
#include "CScene.h"
#include "CLightFactory.h"
#include "CEnvironmentLight.h"
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nSHowCmd)
{
	hInstance; hPrevInstance; lpCmdLine; nSHowCmd;

	CWindowHandler::SWindowData windowData;
	windowData.myX = 100;
	windowData.myY = 100;
	windowData.myWidth = 1600;
	windowData.myHeight = 900;
	
	Engine graphicsEngine;
	bool shouldRun = graphicsEngine.Init(windowData);
	Game game;
	game.Init();
	if (!shouldRun)
	{
		return 0;
	}

	

	MSG windowmessage = { 0 };

	while (shouldRun)
	{
		while (PeekMessage(&windowmessage, 0, 0, 0, PM_REMOVE))
		{
			game.Update();
			TranslateMessage(&windowmessage);
			DispatchMessage(&windowmessage);

			if (windowmessage.message == WM_QUIT)
			{
				shouldRun = false;
			}
		}
		modelInstance->Rotate(CommonUtilities::Vector3<float>(0.3f, 0.0f, 0.0f));

		graphicsEngine.BeginFrame();
		graphicsEngine.RenderFrame();
		graphicsEngine.EndFrame();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
