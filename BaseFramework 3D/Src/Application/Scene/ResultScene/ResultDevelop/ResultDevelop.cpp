#include "ResultDevelop.h"
#include"../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../GameObject/Terrains/Ground/Ground.h"
#include"../../../GameObject/Terrains/Wall/Wall.h"
#include"../../../GameObject/Character/Robot/Full/Full.h"
#include"../../../CSV/RankCalc.h"
#include"../../../GameObject/UI/Text/Enter/Enter.h"

void ResultDevelop::Event()
{
}

void ResultDevelop::Init()
{
	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ -5.0f,5.0f,-6.0f });
	AddObject(camera);

	//地面
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);

	//壁（仮）
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);

	//ロボフル
	std::shared_ptr<Full> full = std::make_shared<Full>();
	full->Init();
	AddObject(full);

	//calc
	std::shared_ptr<RankCalc> calc = std::make_shared<RankCalc>();
	calc->Init();
	AddObject(calc);

	//enter
	std::shared_ptr<Enter> enter = std::make_shared<Enter>();
	enter->Init();
	AddObject(enter);
}
