#include "TitleScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

#include"../../GameObject/UI/Text/Title/TitleTXT.h"
#include"../../GameObject/UI/Text/Play/PlayTXT.h"

#include"../../GameObject/UI/Back/TitleBack/TitleBack.h"
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
	KdAudioManager::Instance().Play("Asset/Sounds/BGM.wav", true, 0.1f);

	std::shared_ptr<TitleBack> titleBack = std::make_shared<TitleBack>();
	titleBack->Init("Asset/Data/Json/UI/Back/TitleBack.json");
	AddObject(titleBack);

	std::shared_ptr<TitleTXT> title = std::make_shared<TitleTXT>();
	title->Init("Asset/Data/Json/UI/Text/TitleTXT.json");
	//title->Init();
	AddObject(title);

	std::shared_ptr<TextFrame> txtFrame = std::make_shared<TextFrame>();
	txtFrame->Init("Asset/Data/Json/UI/Frame/TextFrame.json");
	//txtFrame->Init();
	AddObject(txtFrame);

	std::shared_ptr<PlayTXT> play = std::make_shared<PlayTXT>();
	play->Init("Asset/Data/Json/UI/Text/PlayTXT.json");
	//play->Init();
	AddObject(play);
}
