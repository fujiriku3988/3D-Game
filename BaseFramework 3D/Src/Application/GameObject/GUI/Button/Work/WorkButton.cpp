#include "WorkButton.h"
#include"../../../../main.h"
#include"../../../../GameObject/Camera/CameraBase.h"
#include"../../../../Scene/SceneManager.h"

void WorkButton::Init()
{
	ButtonBase::Init();
	m_pos = { 0,100 };
	m_scale = { 0.7f};
	m_tex.Load("Asset/Textures/UI/boad.png");
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
	m_rotFlg = false;
}

void WorkButton::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			384 * m_scale.x, 128 * m_scale.y, nullptr, &m_color);
	}
}

void WorkButton::Update()
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
		if (nowLength.y <= -m_pos.y + 40 && nowLength.y >= -m_pos.y - 60
			&& nowLength.x >= m_pos.x - 140 && nowLength.x <= m_pos.x + 140)
		{
			m_color = { 1,1,1,0.5f };
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
			spCamera->SetDegAngX(45);
			spCamera->SetControlPos({ 0, 8.0f, -4.5f });
			if (spCamera->GetDegAngXFlg() && spCamera->GetCamPosFlg())
			{
				SceneManager::Instance().SetNextMode(SceneManager::ModeType::GameWork);
			}

		}
	}
	/*Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("nowPosY:%d\n", nowPos.y);
	Application::Instance().m_log.AddLog("nowPosX:%d\n", nowPos.x);
	Application::Instance().m_log.AddLog("nowLengthY:%d\n", nowLength.y);
	Application::Instance().m_log.AddLog("nowLengthX:%d\n", nowLength.x);
	Application::Instance().m_log.AddLog("m_SposY:%d\n", m_Spos.y);*/
}
