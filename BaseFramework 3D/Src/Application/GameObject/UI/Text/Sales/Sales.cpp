#include "Sales.h"
#include"../../../../main.h"
#include"../../../../Scene/SceneManager.h"

void Sales::Init()
{
	m_pos = { -200,0 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/sales1.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_texSize = { 134,80 };
}

void Sales::DrawSprite()
{
	if (SceneManager::Instance().GetModeType() == SceneManager::ModeType::GameWork)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void Sales::Update()
{
	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる

		if (nowLength.y <= -m_pos.y + 40 && nowLength.y >= -m_pos.y - 60
			&& nowLength.x >= m_pos.x - 140 && nowLength.x <= m_pos.x + 140)
		{
			m_color = { 1,1,1,0.5f };
		}
		else
		{
			m_color = { 1,1,1,1 };
		}
	}
}
