#include "WhiteBack.h"

void WhiteBack::Init(const std::string _string)
{
}

void WhiteBack::Init()
{
	UIBase::Init();
	m_pos = { 0,0 };
	m_scale = { 0.6f,0.6f };
	m_tex.Load("Asset/Textures/UI/Result/back.png");
	m_color = { 1,1,1,0.9 };
	m_time = 60;
	m_drawFlg = true;
	m_texSize = { 500,800 };
}

void WhiteBack::DrawSprite()
{
	//m_color = { 1,1,1,m_alpha };
	if (m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
}

void WhiteBack::Update()
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
}
