#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/Ground/Ground.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	AddObject(camera);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

	//CSVLoad::Instance().Load();
}
