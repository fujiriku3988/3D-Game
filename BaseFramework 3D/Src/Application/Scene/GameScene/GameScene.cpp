#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/Ground/Ground.h"
#include"../../GameObject/Terrains/Desk/Desk.h"
#include"../../GameObject/Terrains/Chair/Chair.h"
#include"../../GameObject/Terrains/WhiteBoad/WhiteBoad.h"
#include"../../GameObject/GUI/Button/Development/DevelopButton.h"
#include"../../GameObject/GUI/Button/Sales/SalesButton.h"
#include"../../GameObject/GUI/Button/Work/WorkButton.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);
	//地面
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);
	//机
	std::shared_ptr<Desk> desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);
	//椅子
	std::shared_ptr<Chair> chair = std::make_shared<Chair>();
	chair->Init();
	AddObject(chair);
	//ホワイトボード
	std::shared_ptr<WhiteBoad> whiteBoad = std::make_shared<WhiteBoad>();
	whiteBoad->Init();
	AddObject(whiteBoad);

	//多分いらん
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();

	//UI
	std::shared_ptr<WorkButton> work = std::make_shared<WorkButton>();
	work->Init();
	work->SetCamera(camera);//boadにカメラの情報を渡す
	AddObject(work);

	std::shared_ptr<SalesButton> sales = std::make_shared<SalesButton>();
	sales->Init();
	sales->SetCamera(camera);//boadにカメラの情報を渡す
	AddObject(sales);

	std::shared_ptr<DevelopButton> develop = std::make_shared<DevelopButton>();
	develop->Init();
	develop->SetCamera(camera);//boadにカメラの情報を渡す
	AddObject(develop);
}
