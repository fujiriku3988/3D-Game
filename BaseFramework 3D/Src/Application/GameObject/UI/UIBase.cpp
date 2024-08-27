#include "UIBase.h"

void UIBase::Init()
{
	m_pos = {};
	m_scale = {};
	m_texSize = {};
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
}

void UIBase::DrawSprite()
{
	if (m_drawFlg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y, nullptr, &m_color);
}

void UIBase::Update()
{
}
