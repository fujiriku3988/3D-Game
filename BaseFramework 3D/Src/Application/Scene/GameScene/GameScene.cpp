﻿#include "GameScene.h"
#include"../SceneManager.h"
#include"../../CSV/CSVLoad.h"
#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/Tile/Carpet/Carpet.h"
#include"../../GameObject/Terrains/Desk/Desk.h"
#include"../../GameObject/Terrains/Chair/Chair.h"
#include"../../GameObject/Terrains/WhiteBoad/WhiteBoad.h"
#include"../../GameObject/GUI/Button/Development/DevelopButton.h"
#include"../../GameObject/GUI/Button/Sales/SalesButton.h"
#include"../../GameObject/GUI/Button/Work/WorkButton.h"
#include"../../GameObject/UI/Text/Work/Work.h"
#include"../../GameObject/UI/Text/Develop/Develop.h"
#include"../../GameObject/UI/Text/Sales/Sales.h"
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
	//地面
	std::shared_ptr<Carpet> tile = std::make_shared<Carpet>();
	tile->Init();
	tile->SetPos({ 0,3,3 });
	AddObject(tile);
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

	//UI
	std::shared_ptr<WorkButton> work = std::make_shared<WorkButton>();
	work->Init();
	AddObject(work);

	std::shared_ptr<SalesButton> sales = std::make_shared<SalesButton>();
	sales->Init();
	AddObject(sales);

	std::shared_ptr<DevelopButton> develop = std::make_shared<DevelopButton>();
	develop->Init();
	AddObject(develop);

	std::shared_ptr<Develop> developText = std::make_shared<Develop>();
	developText->Init();
	AddObject(developText);

	std::shared_ptr<Sales> salesText = std::make_shared<Sales>();
	salesText->Init();
	AddObject(salesText);

	std::shared_ptr<Work> workText = std::make_shared<Work>();
	workText->Init();
	AddObject(workText);

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	AddObject(camera);
	work->SetCamera(camera);//boadにカメラの情報を渡す
	sales->SetCamera(camera);//boadにカメラの情報を渡す
	develop->SetCamera(camera);//boadにカメラの情報を渡す
}
