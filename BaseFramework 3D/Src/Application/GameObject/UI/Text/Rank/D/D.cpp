#include "D.h"
#include"../../../../../main.h"

void D::Init()
{
	m_pos = { -250,-100 };
	m_scale = { 2.0f };
	m_tex.Load("Asset/Textures/UI/Rank/d.png");
	m_color = { 1,1,1,1 };
}

void D::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		65 * m_scale.x, 72 * m_scale.y, nullptr, &m_color);
}

void D::Update()
{
}
