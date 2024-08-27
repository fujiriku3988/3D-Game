#include "RobotGUIBase.h"

void RobotGUIBase::Init()
{
	m_pos = {};
	m_scale = {};
	m_texSize = {};
	m_color = { 1,1,1,1 };
	m_drawFlg = false;
	m_aliveFlg = true;
	m_alpha = 1.0f;
	m_alphaMin = 0;
	m_alphaSpeed = 0.01f;
}

void RobotGUIBase::DrawSprite()
{
	m_color = { 1,1,1,m_alpha };
	if (!m_drawFlg)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex1, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
	else
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex2, m_pos.x, m_pos.y,
			m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
	}
	
}

void RobotGUIBase::Update()
{
	if (!m_aliveFlg)
	{
		m_alpha -= m_alphaSpeed;

		if (m_alpha <= m_alphaMin) { m_alpha = m_alphaMin; }
	}
}
