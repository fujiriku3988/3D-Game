#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
//#include"../../GameObject/Character/Robot/Head/Head.h"
//#include"../../GameObject/Character/Robot/Body/Body.h"
//#include"../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
//#include"../../GameObject/Character/Robot/ArmRight/ArmRight.h"
//#include"../../GameObject/Character/Robot/LegLeft/LegLeft.h"
//#include"../../GameObject/Character/Robot/LegRight/LegRight.h"
//#include"../../GameObject/GUI/Bar/DevelopBar/DevelopBar.h"
//#include"../../GameObject/GUI/Bar/DevelopBar/StopBar.h"
#include"../../GameObject/Terrains/Wall/Wall.h"
#include"../../GameObject/Terrains/Light/Light.h"
//#include"../../GameObject/GUI/Robot/Body/BodyGUI.h"
//#include"../../GameObject/GUI/Robot/Head/HeadGUI.h"
//#include"../../GameObject/GUI/Robot/ArmLeft/ArmLeftGUI.h"
//#include"../../GameObject/GUI/Robot/ArmRight/ArmRightGUI.h"
//#include"../../GameObject/GUI/Robot/LegLeft/LegLeftGUI.h"
//#include"../../GameObject/GUI/Robot/LegRight/LegRightGUI.h"
#include"../../CSV/Rank/RankCalc.h"
#include"../../GameObject/Object/Body/CleanRobot/CleanRobot.h"
#include"../../GameObject/Object/Parts/Missile/Missile.h"
#include"../../GameObject/Terrains/Stage/Stage.h"
#include"../../GameObject/Character/Character.h"
#include"../../GameObject/Object/Conver/Conver.h"
#include"../../GameObject/Object/ProduceParts/ProduceParts.h"

void GameDevelop::Event()
{
}

void GameDevelop::Init()
{
	//壁（仮）
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	//AddObject(wall);

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
	AddObject(stage);

	//コンベアー
	std::shared_ptr<Conver> conver = std::make_shared<Conver>();
	conver->Init();
	AddObject(conver);

	//パーツ出す箱
	std::shared_ptr<ProduceParts> prodParts = std::make_shared<ProduceParts>();
	prodParts->Init();
	AddObject(prodParts);


	//クリーンロボ
	std::shared_ptr<CleanRobot> cRobo = std::make_shared<CleanRobot>();
	cRobo->Init();
	AddObject(cRobo);

	//ミサイル
	std::shared_ptr<Missile> missile = std::make_shared<Missile>();
	missile->Init();
	//AddObject(missile);

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

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
	prodParts->SetPlayer(player);
}
