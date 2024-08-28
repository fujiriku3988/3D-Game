#include "BodyGUI.h"
#include"../../../../main.h"

void BodyGUI::Init()
{
	RobotGUIBase::Init();
	m_pos = { 500,200 };
	m_scale = { 1.0f };
	m_tex1.Load("Asset/Textures/GUI/Robot/body.png");
	m_color = { 1,1,1,1 };
	m_texSize = { 36,50 };
}

void BodyGUI::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex1, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
}
