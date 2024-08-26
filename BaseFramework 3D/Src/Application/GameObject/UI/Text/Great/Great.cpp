#include "Great.h"
#include"../../../../main.h"

void Great::Init()
{
	m_pos = { 300,0 };
	m_scale = { 0.3f };
	m_tex.Load("Asset/Textures/UI/Text/great.png");
	m_color = { 1,1,1,1 };
	m_time = 60;
}

void Great::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		180 * m_scale.x, 66 * m_scale.y, nullptr, &m_color);
}

void Great::Update()
{
	m_scale.x += 0.1f;
	m_scale.y += 0.1f;
	if (m_scale.x >= 2.0f && m_scale.y >= 2.0f)
	{
		m_scale = { 2 };
		m_time--;
	}
	if (m_time <= 0)
	{
		m_isExpired = true;
	}
}
