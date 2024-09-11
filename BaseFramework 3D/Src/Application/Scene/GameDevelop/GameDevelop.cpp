#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Character/Player/Player.h"
#include"../../GameObject/Terrains/Tile/Stone/Stone.h"
//#include"../../GameObject/Character/Robot/Head/Head.h"
//#include"../../GameObject/Character/Robot/Body/Body.h"
//#include"../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
//#include"../../GameObject/Character/Robot/ArmRight/ArmRight.h"
//#include"../../GameObject/Character/Robot/LegLeft/LegLeft.h"
//#include"../../GameObject/Character/Robot/LegRight/LegRight.h"
//#include"../../GameObject/GUI/Bar/DevelopBar/DevelopBar.h"
//#include"../../GameObject/GUI/Bar/DevelopBar/StopBar.h"
#include"../../GameObject/UI/Text/Bad/Bad.h"
#include"../../GameObject/Terrains/Wall/Wall.h"
#include"../../GameObject/Terrains/Light/Light.h"
//#include"../../GameObject/GUI/Robot/Body/BodyGUI.h"
//#include"../../GameObject/GUI/Robot/Head/HeadGUI.h"
//#include"../../GameObject/GUI/Robot/ArmLeft/ArmLeftGUI.h"
//#include"../../GameObject/GUI/Robot/ArmRight/ArmRightGUI.h"
//#include"../../GameObject/GUI/Robot/LegLeft/LegLeftGUI.h"
//#include"../../GameObject/GUI/Robot/LegRight/LegRightGUI.h"
#include"../../CSV/Rank/RankCalc.h"
#include"../../GameObject/Character/CleanRobot/CleanRobot.h"
#include"../../GameObject/Terrains/Stage/Stage.h"

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
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Light> light = std::make_shared<Light>();
		light->Init();
		light->SetPos({ -5+(i*5.0f),15,5});
		AddObject(light);
	}

	//地面
	std::shared_ptr<Stone> tile = std::make_shared<Stone>();
	tile->Init();
	//AddObject(tile);

	//stage
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();
	stage->Init();
	AddObject(stage);

	//プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	AddObject(player);

	//cleanRobot
	std::shared_ptr<CleanRobot> cRobo = std::make_shared<CleanRobot>();
	cRobo->Init();
	cRobo->SetPlayer(player);
	AddObject(cRobo);

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ 0,1.7f,0.0 });
	camera->SetTarget(player);
	AddObject(camera);

	//カメラセット
	player->SetCamera(camera);
}
