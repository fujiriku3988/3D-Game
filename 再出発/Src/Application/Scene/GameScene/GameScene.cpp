#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../GameObject/Character/Player/Player.h"

#include"../../GameObject/Terrains/Stage/Stage.h"
#include"../../GameObject/Terrains/Sphere/Sphere.h"

#include"../../GameObject/UI/Button/Play/Play.h"
#include"../../GameObject/UI/Button/Restart/Restart.h"
#include"../../GameObject/UI/Frame/ButtonFrame.h"
#include"../../GameObject/UI/Back/WhiteBack/WhiteBack.h"
#include"../../GameObject/UI/Back/Star/Star.h"

#include"../../GameObject/Object/PressurePlate/PressurePlate.h"
#include"../../GameObject/Object/Fence/Fence.h"
#include"../../GameObject/Object/GoalPoint/GoalPoint.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	//環境光（アンビエントライト）
	//デフォルトは0.3
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.4,0.4,0.4,1 });

	//フォグ（霧）													距離	高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(true, true);
	//距離フォグ														↓霧の色	↓密度
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.8,0.6,0.8 }, 0.008);
	//高さフォグ														↓色	↓上↓下↓カメラとの距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.8,0.5,0.8 }, 10, -2, 40);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->Init();
	AddObject(sphere);

	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init();
	AddObject(stage);

	std::shared_ptr<Fence> fence1 = std::make_shared<Fence>();
	fence1->Init("Asset/Data/Json/Stage1/Fence/Fence1.json");
	AddObject(fence1);
	std::shared_ptr<Fence> fence2 = std::make_shared<Fence>();
	fence2->Init("Asset/Data/Json/Stage1/Fence/Fence2.json");
	AddObject(fence2);

	std::shared_ptr<PressurePlate> plate = std::make_shared<PressurePlate>();
	plate->Init("Asset/Data/Json/Stage1/PressurePlate/Plate.json");
	plate->AddFence(fence1);
	plate->AddFence(fence2);
	AddObject(plate);

	std::shared_ptr<GoalPoint> goalpoint = std::make_shared<GoalPoint>();
	goalpoint->Init("Asset/Data/Json/Stage1/GoalPoint/GoalPoint.json");
	//goalpoint->Init();
	AddObject(goalpoint);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	//player->Init();
	player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(player);

	std::shared_ptr<WhiteBack> wBack = std::make_shared<WhiteBack>();
	wBack->Init();
	//player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(wBack);

	std::shared_ptr<Star> star = std::make_shared<Star>();
	star->Init();
	//player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(star);

	std::shared_ptr<ButtonFrame> bFrame = std::make_shared<ButtonFrame>();
	bFrame->Init();
	bFrame->Init("Asset/Data/Json/UI/Frame/ButtonFrame1.json");
	AddObject(bFrame);

	std::shared_ptr<Play> play = std::make_shared<Play>();
	play->Init();
	//player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(play);

	std::shared_ptr<Restart> restart = std::make_shared<Restart>();
	restart->Init();
	//player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(restart);

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
