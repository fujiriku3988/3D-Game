#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/GUI/Button/Work/WorkButton.h"
#include"../../GameObject/UI/Text/Work/Work.h"
#include"../../GameObject/Terrains/Wall/Wall.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	//壁
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);
	
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);
}
