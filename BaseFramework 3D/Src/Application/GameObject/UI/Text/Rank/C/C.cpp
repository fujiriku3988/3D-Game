#include "C.h"
#include"../../../../../main.h"

void C::Init()
{
	m_pos = { -250,-50 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/c.png");
	m_color = { 1,1,1,1 };
}

void C::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		61 * m_scale.x, 71 * m_scale.y, nullptr, &m_color);
}

void C::Update()
{
}
