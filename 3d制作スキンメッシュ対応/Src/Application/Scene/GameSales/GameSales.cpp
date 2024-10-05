#include "GameSales.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"

void GameSales::Event()
{
}

void GameSales::Init()
{
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);
}
