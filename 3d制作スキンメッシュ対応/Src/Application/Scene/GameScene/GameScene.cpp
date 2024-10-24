#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/GUI/Button/Work/WorkButton.h"
#include"../../GameObject/UI/Text/Work/Work.h"

void GameScene::Event()
{
}

void GameScene::Init()
{	
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);
}
