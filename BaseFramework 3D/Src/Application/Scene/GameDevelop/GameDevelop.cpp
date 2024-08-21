#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Ground/Ground.h"

void GameDevelop::Event()
{
}

void GameDevelop::Init()
{
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCamPos({0,0,0});
	AddObject(camera);

	//地面
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);
}
