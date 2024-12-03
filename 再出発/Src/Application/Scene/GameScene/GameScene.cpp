#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"

#include"../../GameObject/Character/Player/Player.h"

#include"../../GameObject/Terrains/Stage/Stage.h"
#include"../../GameObject/Terrains/Sphere/Sphere.h"

#include"../../GameObject/UI/Button/Play/Play.h"
#include"../../GameObject/UI/Button/Restart/Restart.h"
#include"../../GameObject/UI/Button/Return/Return.h"
#include"../../GameObject/UI/Button/KeyB/KeyB.h"
#include"../../GameObject/UI/Button/KeyR/KeyR.h"
#include"../../GameObject/UI/Button/KeyEnter/KeyEnter.h"
#include"../../GameObject/UI/Frame/ButtonFrame.h"
#include"../../GameObject/UI/Back/BlackBack/BlackBack.h"
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
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.3f,0.3f,0.3f,1.0f });

	//フォグ（霧）													距離	高さ
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	//距離フォグ														↓霧の色	↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1.0f,1.0f,1.0f }, 0.001f);
	//高さフォグ														↓色	↓上↓下↓カメラとの距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1.0f,1.0f,1.0f }, 10, -10, 20);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->Init("Asset/Data/Json/Sphere/Sphere.json");
	AddObject(sphere);

	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init("Asset/Data/Json/Stage1/Stage1.json");
	AddObject(stage);

	std::shared_ptr<Fence> fence1 = std::make_shared<Fence>();
	fence1->Init("Asset/Data/Json/Stage1/Fence/Fence1.json");
	AddObject(fence1);
	std::shared_ptr<Fence> fence2 = std::make_shared<Fence>();
	fence2->Init("Asset/Data/Json/Stage1/Fence/Fence2.json");
	AddObject(fence2);

	std::shared_ptr<PressurePlate> plate = std::make_shared<PressurePlate>();
	plate->Init("Asset/Data/Json/Stage1/PressurePlate/PressurePlate.json");
	plate->AddFence(fence1);
	plate->AddFence(fence2);
	AddObject(plate);

	std::shared_ptr<GoalPoint> goalpoint = std::make_shared<GoalPoint>();
	goalpoint->Init("Asset/Data/Json/Stage1/GoalPoint/GoalPoint.json");
	AddObject(goalpoint);
	
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init("Asset/Data/Json/Player/Player.json");
	AddObject(player);

	std::shared_ptr<BlackBack> bBack = std::make_shared<BlackBack>();
	bBack->Init("Asset/Data/Json/UI/Back/BlackBack.json");
	AddObject(bBack);

	//==================================================//
	std::shared_ptr<Star> star = std::make_shared<Star>();
	star->Init();
	//star->Init("Asset/Data/Json/Player/Player.json");
	AddObject(star);
	//==================================================//

	std::shared_ptr<ButtonFrame> bFrame = std::make_shared<ButtonFrame>();
	bFrame->Init("Asset/Data/Json/UI/Frame/ButtonFrame.json");
	AddObject(bFrame);

	std::shared_ptr<Play> bPlay = std::make_shared<Play>();
	bPlay->Init("Asset/Data/Json/UI/Button/Play.json");
	AddObject(bPlay);

	std::shared_ptr<Restart> bRestart = std::make_shared<Restart>();
	bRestart->Init("Asset/Data/Json/UI/Button/Restart.json");
	AddObject(bRestart);

	std::shared_ptr<Return> bReturn = std::make_shared<Return>();
	bReturn->Init("Asset/Data/Json/UI/Button/Return.json");
	AddObject(bReturn);

	std::shared_ptr<KeyR> keyR = std::make_shared<KeyR>();
	keyR->Init("Asset/Data/Json/UI/Button/KeyR.json");
	AddObject(keyR);

	std::shared_ptr<KeyB> keyB = std::make_shared<KeyB>();
	keyB->Init("Asset/Data/Json/UI/Button/KeyB.json");
	AddObject(keyB);

	std::shared_ptr<KeyEnter> keyEnter = std::make_shared<KeyEnter>();
	keyEnter->Init("Asset/Data/Json/UI/Button/KeyEnter.json");
	AddObject(keyEnter);

	//カメラ
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	camera->SetTarget(player);
	AddObject(camera);

	//セットする系
	player->SetCamera(camera);
	goalpoint->AddUI(bFrame);
	goalpoint->AddUI(bPlay);
	goalpoint->AddUI(bRestart);
	goalpoint->AddUI(bReturn);
	goalpoint->AddUI(keyR);
	goalpoint->AddUI(keyB);
	goalpoint->AddUI(keyEnter);
	goalpoint->AddUI(star);
	goalpoint->AddUI(bBack);

	Math::Viewport viewPort;
	KdDirect3D::Instance().CopyViewportInfo(viewPort);
	float width = viewPort.width;
	float height = viewPort.height;
	KdEffekseerManager::GetInstance().Create((float)width, (float)height);
	KdEffekseerManager::GetInstance().SetCamera(camera->GetCamera());
}
