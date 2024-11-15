#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../GameObject/Character/Player/Player.h"

#include"../../GameObject/Terrains/Stage/Stage.h"
#include"../../GameObject/Terrains/PressurePlate/PressurePlate.h"
#include"../../GameObject/Terrains/Fence/Fence.h"

void GameScene::Event()
{
}

void GameScene::Init()
{	
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init();
	AddObject(stage);

	std::shared_ptr<Fence> fence = std::make_shared<Fence>();
	fence->Init();
	AddObject(fence);

	std::shared_ptr<PressurePlate> plate  = std::make_shared<PressurePlate>();
	plate->Init();
	plate->SetFence(fence);
	AddObject(plate);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

	//カメラ
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	camera->SetTarget(player);
	AddObject(camera);

	player->SetCamera(camera);

	Math::Viewport viewPort;
	KdDirect3D::Instance().CopyViewportInfo(viewPort);
	const int width = viewPort.width;
	const int height = viewPort.height;
	KdEffekseerManager::GetInstance().Create(width, height);
	KdEffekseerManager::GetInstance().SetCamera(camera->GetCamera());
}
