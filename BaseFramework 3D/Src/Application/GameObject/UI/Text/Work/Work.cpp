﻿#include "Work.h"
#include"../../../../main.h"

void Work::Init()
{
	m_pos = { 0,100 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/work1.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_drawFlg = true;
}

void Work::DrawSprite()
{
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			134 * m_scale.x, 80 * m_scale.y, nullptr, &m_color);
	}
}

void Work::Update()
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
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				m_drawFlg = false;
			}
		}
		else
		{
			m_color = { 1,1,1,1 };
		}
	}
}