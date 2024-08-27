#include "ResultDevelop.h"
#include"../../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include"../../../GameObject/Terrains/Tile/Stone/Stone.h"
#include"../../../GameObject/Terrains/Wall/Wall.h"
#include"../../../GameObject/Character/Robot/Full/Full.h"
#include"../../../CSV/RankCalc.h"
#include"../../../GameObject/UI/Text/Enter/Enter.h"
#include"../../../GameObject/Terrains/Light/Light.h"

void ResultDevelop::Event()
{
}

void ResultDevelop::Init()
{

	//地面
	std::shared_ptr<Wall> wall = std::make_shared<Wall>();
	wall->Init();
	AddObject(wall);

	//壁（仮）
	std::shared_ptr<Stone> tile = std::make_shared<Stone>();
	tile->Init();
	AddObject(tile);

	//光
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Light> light = std::make_shared<Light>();
		light->Init();
		light->SetPos({ -5 + (i * 5.0f),15,5 });
		AddObject(light);
	}

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

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ -5.0f,5.0f,-6.0f });
	AddObject(camera);
}
