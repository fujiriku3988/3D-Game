#include "GameDevelop.h"
#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../GameObject/Terrains/Tile/Stone/Stone.h"
//#include"../../GameObject/Character/Robot/Head/Head.h"
//#include"../../GameObject/Character/Robot/Body/Body.h"
//#include"../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
//#include"../../GameObject/Character/Robot/ArmRight/ArmRight.h"
//#include"../../GameObject/Character/Robot/LegLeft/LegLeft.h"
//#include"../../GameObject/Character/Robot/LegRight/LegRight.h"
#include"../../GameObject/GUI/Bar/DevelopBar/DevelopBar.h"
#include"../../GameObject/GUI/Bar/DevelopBar/StopBar.h"
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

	//開発バー
	std::shared_ptr<DevelopBar> developBar = std::make_shared<DevelopBar>();
	developBar->Init();
	AddObject(developBar);
	//開発ストップバー
	std::shared_ptr<StopBar> stopBar = std::make_shared<StopBar>();
	stopBar->Init();
	
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
