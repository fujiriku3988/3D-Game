#include "B.h"
#include"../../../../../main.h"

void B::Init()
{
	m_pos = { -250,-100 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/b.png");
	m_color = { 1,1,1,1 };
}

void B::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		62 * m_scale.x, 70 * m_scale.y, nullptr, &m_color);
}

void B::Update()
{
}
