#include "DevelopBar.h"
#include"../../../main.h"

void DevelopBar::Init()
{
	m_pos = { 0,-240 };
	m_scale = { 1.0f,1.0f };
	m_tex.Load("Asset/Textures/UI/bar.png");
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
	m_rotFlg = false;
}

void DevelopBar::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		1280 * m_scale.x, 240 * m_scale.y, nullptr, &m_color);
}

void DevelopBar::Update()
{
	
}
