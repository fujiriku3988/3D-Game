#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/Ground/Ground.h"
#include"../../GameObject/Terrains/Desk/Desk.h"
#include"../../GameObject/Terrains/Chair/Chair.h"
#include"../../GameObject/GUI/Boad/Boad.h"

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

	std::shared_ptr<Desk> desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);

	std::shared_ptr<Chair> chair = std::make_shared<Chair>();
	chair->Init();
	AddObject(chair);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();

	//UI
	std::shared_ptr<Boad> boad = std::make_shared<Boad>();
	boad->Init();
	boad->SetCamera(camera);
	AddObject(boad);

	//AddObject(player);

	//CSVLoad::Instance().Load();
}
