#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"

#include"../../CSV/Rank/RankCalc.h"

#include"../../Scene/SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/Terrains/Light/Light.h"
#include"../../GameObject/Terrains/Stage/Stage.h"
#include"../../GameObject/Terrains/Stage/Tile/Tile.h"
#include"../../GameObject/Terrains/Stage/Wall/Wall.h"
#include"../../GameObject/Terrains/Stage/Ceiling/Ceiling.h"
#include"../../GameObject/Terrains/Stage/WorkBench/WorkBench.h"
#include"../../GameObject/Terrains/Stage/Sphere/Sphere.h"

#include"../../GameObject/Character/Character.h"

#include"../../GameObject/Object/Body/CleanRobot/CleanRobot.h"
#include"../../GameObject/Object/Parts/Missile/Missile.h"
#include"../../GameObject/Object/Conver/Conver.h"
#include"../../GameObject/Object/ProduceParts/ProduceParts.h"
#include"../../GameObject/Object/Container/Container.h"
#include"../../GameObject/Object/CardBoard/CardBoard.h"

void GameDevelop::Event()
{

}

void GameDevelop::Init()
{

	//光
	/*for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Light> light = std::make_shared<Light>();
		light->Init();
		light->SetPos({ -5+(i*5.0f),15,5});
		AddObject(light);
	}*/

	
	//ステージ
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init();
	//AddObject(stage);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
	sphere->Init();
	AddObject(sphere);

	//壁
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);

	//床
	std::shared_ptr<Tile> tile = std::make_shared<Tile>();
	tile->Init();
	AddObject(tile);

	//天井
	std::shared_ptr<Ceiling> ceiling = std::make_shared<Ceiling>();
	ceiling->Init();
	AddObject(ceiling);

	//作業台
	std::shared_ptr<WorkBench> workBench = std::make_shared<WorkBench>();
	workBench->Init();
	AddObject(workBench);

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
		{
			//一つの生産ライン
			//コンベアー
			std::shared_ptr<Conver> conver = std::make_shared<Conver>();
			conver->Init();
			AddObject(conver);
			//パーツ出す箱
			std::shared_ptr<ProduceParts> prodParts = std::make_shared<ProduceParts>();
			prodParts->Init();
			prodParts->SetProdType(KdGameObject::eMissile);
			AddObject(prodParts);
			//パーツを格納する箱
			std::shared_ptr<Container> container = std::make_shared<Container>();
			container->Init();
			AddObject(container);
			prodParts->SetContainer(container);
			prodParts->SetPlayer(player);
			break;
		}
		case 1:
		{
			//一つの生産ライン
			//コンベアー
			std::shared_ptr<Conver> conver = std::make_shared<Conver>();
			conver->Init();
			conver->SetPos({ -5.0f,0,2.0f });
			AddObject(conver);
			//パーツ出す箱
			std::shared_ptr<ProduceParts> prodParts = std::make_shared<ProduceParts>();
			prodParts->Init();
			prodParts->SetPos({ -5.7f,0,2.0f });
			prodParts->SetProdType(KdGameObject::eCleanRobot);
			AddObject(prodParts);
			//パーツを格納する箱
			std::shared_ptr<Container> container = std::make_shared<Container>();
			container->Init();
			container->SetPos({ 1.7f,0.0f,2.0f });
			AddObject(container);
			prodParts->SetContainer(container);
			prodParts->SetPlayer(player);
			break;
		}
		}

	}



	//段ボール
	std::shared_ptr<CardBoard> cardBoard = std::make_shared<CardBoard>();
	cardBoard->Init();
	AddObject(cardBoard);

	//クリーンロボ
	std::shared_ptr<CleanRobot> cRobo = std::make_shared<CleanRobot>();
	cRobo->Init();
	//AddObject(cRobo);

	//ミサイル
	std::shared_ptr<Missile> missile = std::make_shared<Missile>();
	missile->Init();
	//AddObject(missile);


	//宝箱（アニメーションテスト用）
	//std::shared_ptr<Character> cha = std::make_shared<Character>();
	//cha->Init();
	//AddObject(cha);

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ 0,1.7f,0.0 });
	camera->SetTarget(player);
	AddObject(camera);

	//セット
	player->SetCamera(camera);
	cRobo->SetPlayer(player);
	missile->SetPlayer(player);

	//missile->SetProdParts(prodParts);

}
