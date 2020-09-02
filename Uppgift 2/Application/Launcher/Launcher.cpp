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

	CModelFactory& modelfactory = CModelFactory::GetInstance();
	CModel* model = CModelFactory::GetInstance().GetModel("");
	if (!model)
	{
		model = modelfactory.LoadModel("");
		if (!model)
		{
			return EXIT_FAILURE;
		}
	}
	CModelInstance* modelInstance = new CModelInstance();
	modelInstance->Init(model);
	CScene& scene = CScene::GetInstance();
	scene.AddInstance(modelInstance);

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
		graphicsEngine.BeginFrame();
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
