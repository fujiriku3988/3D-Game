#include "TitleScene.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"
#include"../../Fade/Fade.h"

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
	
}
