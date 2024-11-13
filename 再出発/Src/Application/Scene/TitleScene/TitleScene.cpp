#include "TitleScene.h"

#include"../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Enter/Enter.h"
#include"../../GameObject/UI/Text/Title/Title.h"

#include"../../GameObject/Terrains/Stage/Tile/Tile.h"
#include"../../GameObject/Terrains/Stage/Wall/Wall.h"
#include"../../GameObject/Terrains/Stage/Ceiling/Ceiling.h"
#include"../../GameObject/Terrains/Stage/WorkBench/WorkBench.h"
#include"../../GameObject/Terrains/Stage/Sphere/Sphere.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_key == false)
		{
			Fade::Instance().BootBlackFade(SceneManager::SceneType::GameDevelop);
			m_key = true;
		}
	}
	else
	{
		m_key = false;
	}
}

void TitleScene::Init()
{
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

	//タイトル
	std::shared_ptr<Title> title = std::make_shared<Title>();
	title->Init();
	AddObject(title);

	//エンター
	std::shared_ptr<Enter> enter = std::make_shared<Enter>();
	enter->Init();
	AddObject(enter);

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ 0,2.0f,0.0 });
	AddObject(camera);
}
