#include "Rank.h"
#include"../../../../../main.h"

void Rank::Init()
{
	m_pos = { -250,100 };
	m_scale = { 1.0f };
	m_tex.Load("Asset/Textures/UI/Text/rank.png");
	m_color = { 1,1,1,1 };
}

void Rank::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		214 * m_scale.x, 71 * m_scale.y, nullptr, &m_color);
}

void Rank::Update()
{
}
