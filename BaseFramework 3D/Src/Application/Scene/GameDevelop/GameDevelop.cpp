#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Tile/Stone/Stone.h"
#include"../../GameObject/Character/Robot/Head/Head.h"
#include"../../GameObject/Character/Robot/Body/Body.h"
#include"../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
#include"../../GameObject/Character/Robot/ArmRight/ArmRight.h"
#include"../../GameObject/Character/Robot/LegLeft/LegLeft.h"
#include"../../GameObject/Character/Robot/LegRight/LegRight.h"
#include"../../GameObject/Terrains/Desk/Desk.h"
#include"../../GameObject/Terrains/WhiteBoad/WhiteBoad.h"
#include"../../GameObject/GUI/Bar/DevelopBar/DevelopBar.h"
#include"../../GameObject/GUI/Bar/DevelopBar/StopBar.h"
#include"../../GameObject/UI/Text/Bad/Bad.h"
#include"../../GameObject/Terrains/Wall/Wall.h"
#include"../../GameObject/Terrains/Light/Light.h"
#include"../../GameObject/GUI/Robot/Body/BodyGUI.h"
#include"../../GameObject/GUI/Robot/Head/HeadGUI.h"
#include"../../GameObject/GUI/Robot/ArmLeft/ArmLeftGUI.h"
#include"../../GameObject/GUI/Robot/ArmRight/ArmRightGUI.h"
#include"../../GameObject/GUI/Robot/LegLeft/LegLeftGUI.h"
#include"../../GameObject/GUI/Robot/LegRight/LegRightGUI.h"
#include"../../CSV/Rank/RankCalc.h"

void GameDevelop::Event()
{
}

void GameDevelop::Init()
{
	//壁（仮）
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);

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
	AddObject(tile);

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

	//ロボGUI体
	std::shared_ptr<BodyGUI> bodyGUI = std::make_shared<BodyGUI>();
	bodyGUI->Init();
	AddObject(bodyGUI);
	//ロボGUI頭
	std::shared_ptr<HeadGUI> headGUI = std::make_shared<HeadGUI>();
	headGUI->Init();
	AddObject(headGUI);
	//ロボGUI腕
	std::shared_ptr<ArmLeftGUI> armLeftGUI = std::make_shared<ArmLeftGUI>();
	armLeftGUI->Init();
	AddObject(armLeftGUI);
	//ロボGUI腕
	std::shared_ptr<ArmRightGUI> armRightGUI = std::make_shared<ArmRightGUI>();
	armRightGUI->Init();
	AddObject(armRightGUI);
	//ロボGUI足
	std::shared_ptr<LegLeftGUI> legLeftGUI = std::make_shared<LegLeftGUI>();
	legLeftGUI->Init();
	AddObject(legLeftGUI);
	//ロボGUI足
	std::shared_ptr<LegRightGUI> legRightGUI = std::make_shared<LegRightGUI>();
	legRightGUI->Init();
	AddObject(legRightGUI);

	//開発バー
	std::shared_ptr<DevelopBar> developBar = std::make_shared<DevelopBar>();
	developBar->Init();
	AddObject(developBar);
	//開発ストップバー
	std::shared_ptr<StopBar> stopBar = std::make_shared<StopBar>();
	stopBar->Init();
	//ロボモデル
	stopBar->SetHead(head);
	stopBar->SetArmLeft(armLeft);
	stopBar->SetArmRight(armRight);
	stopBar->SetLegLeft(legLeft);
	stopBar->SetLegRight(legRight);
	//ロボGUI
	stopBar->SetHeadGUI(headGUI);
	stopBar->SetBodyGUI(bodyGUI);
	stopBar->SetArmLeftGUI(armLeftGUI);
	stopBar->SetArmRightGUI(armRightGUI);
	stopBar->SetLegLeftGUI(legLeftGUI);
	stopBar->SetLegRightGUI(legRightGUI);
	//開発バー
	stopBar->SetDevelopBar(developBar);
	AddObject(stopBar);

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ 0,5.0f,-7.0f });
	AddObject(camera);
	//カメラセット
	stopBar->SetCamera(camera);
}
