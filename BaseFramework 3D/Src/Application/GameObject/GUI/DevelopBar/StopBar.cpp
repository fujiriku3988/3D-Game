#include "StopBar.h"
#include"../../../main.h"
#include"../../../GameObject/Character/Robot/Head/Head.h"
#include"../../../GameObject/Character/Robot/ArmLeft/ArmLeft.h"
#include"../../../GameObject/Character/Robot/ArmRight/ArmRight.h"
#include"../../../GameObject/Character/Robot/LegLeft/LegLeft.h"
#include"../../../GameObject/Character/Robot/LegRight/LegRight.h"
#include"../../../Fade/Fade.h"

void StopBar::Init()
{
	m_pos = { 0,-240 };
	m_stopMove = 1.0f;
	m_speed = { 10.0f,0 };
	m_scale = { 1.0f,1.0f };
	m_time = 0;
	m_step = 0;
	m_tex.Load("Asset/Textures/UI/stopBar.png");
	m_color = { 1,1,1,1 };
	m_stepFlg = false;
	m_resetFlg = false;
	m_keyFlg = false;
}

void StopBar::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		5 * m_scale.x, 240 * m_scale.y, nullptr, &m_color);
}

void StopBar::Update()
{
	m_pos += m_speed * m_stopMove;
	//バーが端に着いたら動き反転
	if (m_pos.x >= 640 || m_pos.x <= -640)
	{
		m_speed.x *= -1;
	}

	std::shared_ptr<Head>spHead = m_wpHead.lock();
	std::shared_ptr<ArmLeft>spArmLeft = m_wpArmLeft.lock();
	std::shared_ptr<ArmRight>spArmRight = m_wpArmRight.lock();
	std::shared_ptr<LegLeft>spLegLeft = m_wpLegLeft.lock();
	std::shared_ptr<LegRight>spLegRight = m_wpLegRight.lock();
	//SPACEで止める
	if (m_time == 0)//今は時間で制御してるけど、ロボのアニメーションが終わったらにしたい
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//VeryGood
			if (m_pos.x >= -30 && m_pos.x <= 30)
			{
				m_qual = ePerfect;
			}
			//Great
			if (m_pos.x >= -120 && m_pos.x <= -31)
			{
				m_qual = eGreat;
			}
			else if (m_pos.x >= 31 && m_pos.x <= 120)
			{
				m_qual = eGreat;
			}
			//Good
			if (m_pos.x >= -385 && m_pos.x <= -121)
			{
				m_qual = eGood;
			}
			else if (m_pos.x >= 121 && m_pos.x <= 385)
			{
				m_qual = eGood;
			}
			//Bad
			if (m_pos.x <= -386)
			{
				m_qual = eBad;
			}
			else if (m_pos.x >= 386)
			{
				m_qual = eBad;
			}
			if (!m_keyFlg)
			{
				m_keyFlg = true;
				m_resetFlg = true;
				m_stepFlg = true;
				m_stopMove = 0;
			}
		}
		else
		{
			m_keyFlg = false;
		}
	}

	//パーツをくっつける処理
	switch (m_step)
	{
	case 1:
		spHead->OnFlg();
		break;
	case 2:
		spArmLeft->OnFlg();
		break;
	case 3:
		spArmRight->OnFlg();
		break;
	case 4:
		spLegLeft->OnFlg();
		break;
	case 5:
		spLegRight->OnFlg();
		break;
	}
	
	

	if (m_step == 5)
	{
		Fade::Instance().BootWhiteFade(SceneManager::SceneType::Game);
	}


	//バー止めたら次動き出すまでの時間
	if (m_resetFlg)
	{
		m_time++;
		if (m_time >= 60)//今は時間で制御してるけど、ロボのアニメーションが終わったらにしたい
		{
			m_resetFlg = false;
			m_stopMove = 1.0f;
		}
	}
	else
	{
		m_time = 0;
	}

	if (m_stepFlg)
	{
		m_stepFlg = false;
		m_step += 1;
	}

	POINT nowPos;
	GetCursorPos(&nowPos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
	POINT nowLength;

	nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
	nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正

	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("nowPosY:%d\n", nowPos.y);
	Application::Instance().m_log.AddLog("nowPosX:%d\n", nowPos.x);
	Application::Instance().m_log.AddLog("nowLengthY:%d\n", nowLength.y);
	Application::Instance().m_log.AddLog("nowLengthX:%d\n", nowLength.x);
	Application::Instance().m_log.AddLog("m_qual:%d\n", m_qual);

	Application::Instance().m_log.AddLog("m_step:%d\n", m_step);
}
