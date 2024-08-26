#include "A.h"
#include"../../../../../main.h"

void A::Init()
{
	m_pos = { -250,-100 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/a.png");
	m_color = { 1,1,1,1 };
}

void A::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		65 * m_scale.x, 71 * m_scale.y, nullptr, &m_color);
}

void A::Update()
{
}
