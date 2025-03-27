#include "GuideScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/BackGround/TitleBack/TitleBack.h"
#include"../../GameObject/UI/GuideBoard/GuideBoard.h"
#include"../../GameObject/UI/BackGround/BlackBack/BlackBack.h"
#include"../../GameObject/UI/BackGround/UIBack/UIBack.h"

#include"../../GameObject/UI/Text/Guide/GuideTXT.h"

#include"../../GameObject/UI/Button/Back/BackButton.h"

void GuideScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_key == false)
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
			m_key = true;
		}
	}
	else
	{
		m_key = false;
	}
}

void GuideScene::Init()
{
	std::shared_ptr<TitleBack> titleBack = std::make_shared<TitleBack>();
	titleBack->Init("Asset/Data/Json/UI/Back/TitleBack.json");
	AddObject(titleBack);

	std::shared_ptr<UIBack> uiBack = std::make_shared<UIBack>();
	uiBack->Init("Asset/Data/Json/UI/Back/UIBack.json");
	AddObject(uiBack);
	
	std::shared_ptr<GuideBoard> guideBoard = std::make_shared<GuideBoard>();
	guideBoard->Init("Asset/Data/Json/UI/GuideBoard/GuideBoard.json");
	AddObject(guideBoard);

	std::shared_ptr<GuideTXT> guide = std::make_shared<GuideTXT>();
	guide->Init("Asset/Data/Json/UI/Text/Guide/GuideScene/GuideTXT.json");
	AddObject(guide);

	std::shared_ptr<BackButton> back = std::make_shared<BackButton>();
	back->Init("Asset/Data/Json/UI/Button/Back.json");
	AddObject(back);
}
