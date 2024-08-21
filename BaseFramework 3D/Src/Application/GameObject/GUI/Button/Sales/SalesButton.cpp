#include "SalesButton.h"
#include"../../../../main.h"
#include"../../../../GameObject/Camera/CameraBase.h"
#include"../../../../Scene/SceneManager.h"

void SalesButton::Init()
{
	ButtonBase::Init();
	m_Spos = { -200,0 };
	m_scale = { 0.7f,0.7f };
	m_tex.Load("Asset/Textures/UI/boad.png");
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
	m_rotFlg = false;
}

void SalesButton::DrawSprite()
{
	if (SceneManager::Instance().GetModeType() == SceneManager::ModeType::GameWork)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_Spos.x, m_Spos.y,
			384 * m_scale.x, 128 * m_scale.y, nullptr, &m_color);
	}
}

void SalesButton::Update()
{
	//if (SceneManager::Instance().GetModeType() == SceneManager::ModeType::GameDevelop)
	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる


		std::shared_ptr<CameraBase>spCamera = m_wpCamera.lock();
		if (nowLength.y <= -m_Spos.y + 40 && nowLength.y >= -m_Spos.y - 60
			&& nowLength.x >= m_Spos.x - 140 && nowLength.x <= m_Spos.x + 140)
		{
			m_color = { 1,1,1,0.2f };
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				m_rotFlg = true;
				m_drawFlg = false;
			}
		}
		else
		{
			m_color = { 1,1,1,1 };
		}

		if (m_rotFlg)
		{
			//spCamera->SetDegAngY(90);
			//spCamera->SetDegAngX(45);
			//spCamera->SetCamPos({ 0, 8.0f, -4.5f });
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::GameSales);
		}
	}
	/*Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("nowPosY:%d\n", nowPos.y);
	Application::Instance().m_log.AddLog("nowPosX:%d\n", nowPos.x);
	Application::Instance().m_log.AddLog("nowLengthY:%d\n", nowLength.y);
	Application::Instance().m_log.AddLog("nowLengthX:%d\n", nowLength.x);
	Application::Instance().m_log.AddLog("m_SposY:%d\n", m_Spos.y);*/
}
