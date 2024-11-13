#include "ResultDevelop.h"
#include"../../../GameObject/Camera/FPSCamera/FPSCamera.h"

#include"../../../GameObject/Character/Robot/Full/Full.h"

#include"../../../CSV/Rank/RankCalc.h"

#include"../../../GameObject/Terrains/Light/Light.h"
#include"../../../GameObject/Terrains/Stage/Stage.h"
#include"../../../GameObject/Terrains/Stage/Wall/Wall.h"
#include"../../../GameObject/Terrains/Stage/Tile/Tile.h"
#include"../../../GameObject/Terrains/Stage/Ceiling/Ceiling.h"
#include"../../../Fade/Fade.h"
#include"../../../Scene/SceneManager.h"

#include"../../../GameObject/GUI/Bar/ExpBar/ExpBar.h"

void ResultDevelop::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_key == false)
		{
			Fade::Instance().BootBlackFade(SceneManager::SceneType::Title);
			m_key = true;
		}
	}
	else
	{
		m_key = false;
	}
}

void ResultDevelop::Init()
{
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

	//カメラ
	std::shared_ptr<FPSCamera> camera = std::make_shared<FPSCamera>();
	camera->Init();
	camera->SetCameraPos({ 0.0f,3.0f,0.0f });
	AddObject(camera);

	Math::Viewport viewPort;
	KdDirect3D::Instance().CopyViewportInfo(viewPort);
	const int width = viewPort.width;
	const int height = viewPort.height;
	KdEffekseerManager::GetInstance().Create(width, height);
	KdEffekseerManager::GetInstance().SetCamera(camera->GetCamera());
}
