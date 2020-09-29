#include "Game.h"
#include "CScene.h"
#include "CCameraFactory.h"
#include "CModelFactory.h"
#include "Vector3.hpp"
#include "CCamera.h"
#include "CModelInstance.h"
#include "InputHandler.h"
#include "winuser.h"

int Game::Init()
{
	CScene& scene = CScene::GetInstance();

	CCameraFactory& cameraFactory = CCameraFactory::GetInstance();
	CCamera* camera = cameraFactory.CreateCamera(90.0f);
	camera->SetTransform(CommonUtilities::Vector3<float>(0.0f, 0.0f, 0.0f), CommonUtilities::Vector3<float>(0.0f, 0.0f, -5.0f));
	scene.AddInstance(camera);
	scene.SetMainCamera(camera);

	CModelFactory& modelfactory = CModelFactory::GetInstance();
	CModel* model = modelfactory.LoadModel("Models/Chest_PBR_Test/Particle_Chest.fbx");
	if (!model)
	{
		model = modelfactory.GetCube();
		if (!model)
		{
			return EXIT_FAILURE;
		}
	}
	CModelInstance* modelInstance = new CModelInstance();
	modelInstance->Init(model);
	scene.AddInstance(modelInstance);

	CModelInstance* modelInstance2 = new CModelInstance();
	modelInstance2->Init(model);
	scene.AddInstance(modelInstance2);


	CModelInstance* modelInstance3 = new CModelInstance();
	modelInstance3->Init(model);
	scene.AddInstance(modelInstance3);


	modelInstance->Scale(CommonUtilities::Vector3<float>(.05f, .05f, .05f));
	modelInstance2->Scale(CommonUtilities::Vector3<float>(.05f, .05f, .05f));
	modelInstance3->Scale(CommonUtilities::Vector3<float>(.05f, .05f, .05f));
	modelInstance->Rotate(CommonUtilities::Vector3<float>(.0f, 90.f, .0f));
	modelInstance2->Rotate(CommonUtilities::Vector3<float>(.0f, 180.f, .0f));
	modelInstance->SetPosition(CommonUtilities::Vector3<float>(-50.0f, 0.0f, 50.0f));
	modelInstance2->SetPosition(CommonUtilities::Vector3<float>(0.0f, 0.0f, 50.0f));
	modelInstance3->SetPosition(CommonUtilities::Vector3<float>(50.0f, 0.0f, 50.0f));
	return 0;
}

void Game::Update()
{
	CCamera* mainCamera = CScene::GetInstance().GetMainCamera();
	CommonUtilities::Vector3<float> movementVector = { 0,0,0 };
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown('W'))
	{
		
		movementVector += mainCamera->GetTransform().GetForward();
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown('A'))
	{
		movementVector -= mainCamera->GetTransform().GetRight();
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown('S'))
	{
		movementVector -= mainCamera->GetTransform().GetForward();
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown('D'))
	{
		movementVector += mainCamera->GetTransform().GetRight();
	}

	CommonUtilities::Vector3<float> rotationVector = { 0,0,0 };

	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown(VK_UP))
	{
		rotationVector.x -= 1;
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown(VK_LEFT))
	{
		rotationVector.y -= 1;
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown(VK_DOWN))
	{
		rotationVector.x += 1;
	}
	if (CommonUtilities::InputHandler::GetInstance().CheckKeyDown(VK_RIGHT))
	{
		rotationVector.y += 1;
	}

	mainCamera->Move(movementVector);
	mainCamera->Rotate(rotationVector);
}



