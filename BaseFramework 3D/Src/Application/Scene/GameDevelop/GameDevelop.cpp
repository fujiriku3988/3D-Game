#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Ground/Ground.h"
#include"../../GameObject/Character/Robot/Head/Head.h"
#include"../../GameObject/Character/Robot/Body/Body.h"
#include"../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
#include"../../GameObject/Character/Robot/ArmRight/ArmRight.h"
#include"../../GameObject/Character/Robot/LegLeft/LegLeft.h"
#include"../../GameObject/Character/Robot/LegRight/LegRight.h"
#include"../../GameObject/Terrains/Desk/Desk.h"
#include"../../GameObject/Terrains/WhiteBoad/WhiteBoad.h"
#include"../../GameObject/GUI/DevelopBar/DevelopBar.h"
#include"../../GameObject/GUI/DevelopBar/StopBar.h"
#include"../../GameObject/UI/Text/Bad/Bad.h"
#include"../../GameObject/Terrains/Wall/Wall.h"
#include"../../CSV/RankCalc.h"

void GameDevelop::Event()
{
}

void GameDevelop::Init()
{
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({0,5.0f,-7.0f});
	AddObject(camera);

	//壁（仮）
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);

	//地面
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);

	//ロボ頭
	std::shared_ptr<Head> head = std::make_shared<Head>();
	head->Init();
	AddObject(head);

	//ロボ体
	std::shared_ptr<Body> body = std::make_shared<Body>();
	body->Init();
	AddObject(body);

	//ロボ腕
	std::shared_ptr<ArmLeft> armLeft = std::make_shared<ArmLeft>();
	armLeft->Init();
	AddObject(armLeft);
	//ロボ腕
	std::shared_ptr<ArmRight> armRight = std::make_shared<ArmRight>();
	armRight->Init();
	AddObject(armRight);

	//ロボ足
	std::shared_ptr<LegLeft> legLeft = std::make_shared<LegLeft>();
	legLeft->Init();
	AddObject(legLeft);
	//ロボ足
	std::shared_ptr<LegRight> legRight = std::make_shared<LegRight>();
	legRight->Init();
	AddObject(legRight);

	//開発バー
	std::shared_ptr<DevelopBar> developBar = std::make_shared<DevelopBar>();
	developBar->Init();
	AddObject(developBar);
	//開発ストップバー
	std::shared_ptr<StopBar> stopBar = std::make_shared<StopBar>();
	stopBar->Init();
	stopBar->SetHead(head);
	stopBar->SetArmLeft(armLeft);
	stopBar->SetArmRight(armRight);
	stopBar->SetLegLeft(legLeft);
	stopBar->SetLegRight(legRight);
	stopBar->SetDevelopBar(developBar);
	stopBar->SetCamera(camera);
	AddObject(stopBar);
}
