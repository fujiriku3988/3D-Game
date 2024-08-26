#include "S.h"
#include"../../../../../main.h"

void S::Init()
{
	m_pos = { -250,-100 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/s.png");
	m_color = { 1,1,1,1 };
}

void S::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		55 * m_scale.x, 74 * m_scale.y, nullptr, &m_color);
}

void S::Update()
{
}
