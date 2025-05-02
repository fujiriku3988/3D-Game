#include "SettingScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Sound/BGM/BgmTXT.h"
#include"../../GameObject/UI/Text/Sound/SE/SeTXT.h"

#include"../../GameObject/UI/BackGround/TitleBack/TitleBack.h"
#include"../../GameObject/UI/BackGround/UIBack/UIBack.h"

#include"../../GameObject/UI/Frame/TextFrame/TextFrame.h"

#include"../../GameObject/UI/Sound/BGM/VolumeSliderBGM.h"
#include"../../GameObject/UI/Sound/SE/VolumeSliderSE.h"

#include"../../GameObject/UI/Button/Back/BackButton.h"

void SettingScene::Event()
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

void SettingScene::Init()
{
	std::shared_ptr<TitleBack> titleBack = std::make_shared<TitleBack>();
	titleBack->Init("Asset/Data/Json/UI/Back/TitleBack.json");
	AddObject(titleBack);

	std::shared_ptr<UIBack> uiBack = std::make_shared<UIBack>();
	uiBack->Init("Asset/Data/Json/UI/Back/UIBack.json");
	AddObject(uiBack);
	
	std::shared_ptr<VolumeSliderBGM> volSliderBGM = std::make_shared<VolumeSliderBGM>();
	volSliderBGM->Init("Asset/Data/Json/UI/Sound/BGM/SliderBGM.json");
	AddObject(volSliderBGM);

	std::shared_ptr<BgmTXT> bgmTXT = std::make_shared<BgmTXT>();
	bgmTXT->Init("Asset/Data/Json/UI/Text/Sound/BGM/bgmTXT.json");
	AddObject(bgmTXT);

	std::shared_ptr<VolumeSliderSE> volSliderSE = std::make_shared<VolumeSliderSE>();
	volSliderSE->Init("Asset/Data/Json/UI/Sound/SE/SliderSE.json");
	AddObject(volSliderSE);

	std::shared_ptr<SeTXT> seTXT = std::make_shared<SeTXT>();
	seTXT->Init("Asset/Data/Json/UI/Text/Sound/SE/seTXT.json");
	AddObject(seTXT);

	std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>();
	backButton->Init("Asset/Data/Json/UI/Button/Back.json");
	AddObject(backButton);
}
