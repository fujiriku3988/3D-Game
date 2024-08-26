#include "E.h"
#include"../../../../../main.h"

void E::Init()
{
	m_pos = { -250,-100 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/e.png");
	m_color = { 1,1,1,1 };
}

void E::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		62 * m_scale.x, 70 * m_scale.y, nullptr, &m_color);
}

void E::Update()
{
}
