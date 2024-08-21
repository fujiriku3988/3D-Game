#include "ButtonBase.h"

void ButtonBase::Init()
{
	m_Spos = {};
	m_scale = {};
	m_texSize = { 384,128 };
	m_color = { 1,1,1,1 };
	m_drawFlg = true;
	m_rotFlg = false;
}

void ButtonBase::DrawSprite()
{
	if (m_drawFlg == false) { return; }
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_Spos.x, m_Spos.y,
		384 * m_scale.x, 128 * m_scale.y, nullptr, &m_color);
}

void ButtonBase::Update()
{
}
