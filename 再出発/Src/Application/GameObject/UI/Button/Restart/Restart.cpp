#include "Restart.h"
#include"../../../../main.h"

void Restart::Init(const std::string _string)
{
}

void Restart::Init()
{
	UIBase::Init();
	m_pos = { -50,-80 };
	m_scale = { 0.9f };
	m_tex.Load("Asset/Textures/UI/Result/restart.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
	m_drawFlg = true;
	m_texSize = { 45,40 };
}

void Restart::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void Restart::Update()
{
	//α値変更
	//m_alpha += m_speed;
	if (m_alpha < m_alphaMIN)
	{
		//m_speed *= -1;
	}
	if (m_alpha > m_alphaMAX)
	{
		//m_speed *= -1;
	}

	{
		POINT nowPos;
		GetCursorPos(&nowPos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &nowPos);
		POINT nowLength;

		nowLength.x = (nowPos.x - 640);//マウス座標の(0,0)の位置が画面左上の端だから補正
		nowLength.y = (nowPos.y - 360);//マウス座標の(0,0)の位置が画面左上の端だから補正
		//マウス座標のPOINTは右がプラス左がマイナス
		//nowLengthが上に行くとマイナス値が増えるからm_Sposもそれに合わせて考えてやる

		if (nowLength.y <= -m_pos.y + 20 && nowLength.y >= -m_pos.y - 20
			&& nowLength.x >= m_pos.x - 22 && nowLength.x <= m_pos.x + 22)
		{
			m_color = { 1,1,1,0.1f };
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
