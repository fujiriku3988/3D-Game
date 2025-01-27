#include "TitleScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Title/TitleTXT.h"
#include"../../GameObject/UI/Text/Play/PlayTXT.h"
#include"../../GameObject/UI/Text/Setting/SettingTXT.h"
#include"../../GameObject/UI/Text/Guide/GuideTXT.h"

#include"../../GameObject/UI/BackGround/TitleBack/TitleBack.h"
#include"../../GameObject/UI/Frame/TextFrame/TextFrame.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_key == false)
		{
			Fade::Instance().BootBlackFade(SceneManager::SceneType::StageSelectScene);
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
	KdAudioManager::Instance().StopAllSound();
	m_bgmVolume = KdAudioManager::Instance().GetBGMVolume();
	KdAudioManager::Instance().Play("Asset/Sounds/BGM/BGM.wav", true, m_bgmVolume);

	std::shared_ptr<TitleBack> titleBack = std::make_shared<TitleBack>();
	titleBack->Init("Asset/Data/Json/UI/Back/TitleBack.json");
	AddObject(titleBack);

	std::shared_ptr<TitleTXT> title = std::make_shared<TitleTXT>();
	title->Init("Asset/Data/Json/UI/Text/TitleTXT.json");
	AddObject(title);

	std::shared_ptr<TextFrame> txtFramePlay = std::make_shared<TextFrame>();
	txtFramePlay->Init("Asset/Data/Json/UI/Frame/TextFrame/TextFramePlay.json");
	AddObject(txtFramePlay);

	std::shared_ptr<PlayTXT> play = std::make_shared<PlayTXT>();
	play->Init("Asset/Data/Json/UI/Text/PlayTXT.json");
	AddObject(play);

	std::shared_ptr<TextFrame> txtFrameSetting = std::make_shared<TextFrame>();
	txtFrameSetting->Init("Asset/Data/Json/UI/Frame/TextFrame/TextFrameSetting.json");
	AddObject(txtFrameSetting);

	std::shared_ptr<SettingTXT> setting = std::make_shared<SettingTXT>();
	setting->Init("Asset/Data/Json/UI/Text/SettingTXT.json");
	AddObject(setting);

	std::shared_ptr<TextFrame> txtFrameGuide = std::make_shared<TextFrame>();
	txtFrameGuide->Init("Asset/Data/Json/UI/Frame/TextFrame/TextFrameGuide.json");
	AddObject(txtFrameGuide);

	std::shared_ptr<GuideTXT> guide = std::make_shared<GuideTXT>();
	guide->Init("Asset/Data/Json/UI/Text/Guide/TitleScene/GuideTXT.json");
	AddObject(guide);

}
