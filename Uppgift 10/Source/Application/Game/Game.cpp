#include "Game.h"
#include "CScene.h"
#include "CCameraFactory.h"
#include "CModelFactory.h"
#include "Vector3.hpp"
#include "CCamera.h"
#include "CModelInstance.h"
#include "InputHandler.h"
#include "winuser.h"
#include "CLightFactory.h"
#include "CEnvironmentLight.h"
#include "CPointLight.h"
int Game::Init()
{
	CScene& scene = CScene::GetInstance();

	CCameraFactory& cameraFactory = CCameraFactory::GetInstance();
	CLightFactory& lightFactory = CLightFactory::GetInstance();

	CEnvironmentLight* environmentLight = lightFactory.CreateEnvironmentalLight(L"Textures/cube_1024_preblurred_angle3_Skansen3.dds");
	environmentLight->SetDirection({ 0.0f,0.0f,-1.0f });
	environmentLight->SetColor({ .3f,.3f ,0.3f });
	CPointLight* pointLightBlue = lightFactory.CreatePointLight({ 6,6,42.0f }, 5.f, 50.f, { 0,0,1.f });
	CPointLight* pointLightRed = lightFactory.CreatePointLight({ -6,6,42.0f }, 5.f, 50.f, { 1.f,0,0 });
	CPointLight* pointLightGreen = lightFactory.CreatePointLight({ 0,3,42.0f }, 5.f, 50.f, { 0,1.f,0 });
	CPointLight* pointLightPink = lightFactory.CreatePointLight({ -20,3,35.0f }, 5.f, 50.f, { 1.f,0,1.f });
	scene.AddInstance(pointLightBlue);
	scene.AddInstance(pointLightRed);
	scene.AddInstance(pointLightGreen);
	scene.AddInstance(pointLightPink);
	scene.AddInstance(environmentLight);
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

	modelInstance->SetPosition(CommonUtilities::Vector3<float>(0.0f, 0.0f, 50.0f));
	modelInstance->Scale({ 0.1f, 0.1f, 0.1f });
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



